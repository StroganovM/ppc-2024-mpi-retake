// Copyright 2024 Stroganov Mikhail
#include "mpi/stroganov_m_dining_philosophers/include/ops_mpi.hpp"
#include <boost/mpi/collectives.hpp>
#include <boost/mpi/communicator.hpp>

#include <algorithm>
#include <chrono>
#include <mpi.h>
#include <random>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

bool stroganov_m_dining_philosophers_mpi::DiningPhilosophersMPI::PreProcessingImpl() {
  l_philosopher_ = (world_.rank() + world_.size() - 1) % world_.size();
  r_philosopher_ = (world_.rank() + 1) % world_.size();
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(0, 2);
  status_ = distrib(gen);  // 0-размышляет, 1 - ест, 2 - голоден
  return true;
}

bool stroganov_m_dining_philosophers_mpi::DiningPhilosophersMPI::ValidationImpl() {
  if (world_.rank() == 0) {
    count_philosophers_ = static_cast<int>(task_data->inputs_count[0]);
  } else {
    count_philosophers_ = world_.size();
  }

  return count_philosophers_ >= 2;
}

void stroganov_m_dining_philosophers_mpi::DiningPhilosophersMPI::Think() {
  status_ = 0;
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void stroganov_m_dining_philosophers_mpi::DiningPhilosophersMPI::Eat() {
  status_ = 1;
  std::this_thread::sleep_for(std::chrono::milliseconds(80));
}

void stroganov_m_dining_philosophers_mpi::DiningPhilosophersMPI::ReleaseForks() {
  status_ = 0;
  /*
  if (world.iprobe(l_philosopher, 0)) {
    world.send(l_philosopher, 0, status);
  }

  if (world.iprobe(r_philosopher, 0)) {
    world.send(r_philosopher, 0, status);
  }
*/
  MPI_Status status;
  if (world_.iprobe(l_philosopher_, 0)) {
    world_.send(l_philosopher_, 0, status_);
    int recv_status = -2;
    world_.recv(l_philosopher_, 0, recv_status);
  }
  if (world_.iprobe(r_philosopher_, 0)) {
    world_.send(r_philosopher_, 0, status_);
    int recv_status = -2;
    world_.recv(r_philosopher_, 0, recv_status);
  }
}

bool stroganov_m_dining_philosophers_mpi::DiningPhilosophersMPI::DistributionForks() {
  status_ = 2;
  int l_status = -1;
  int r_status = -1;

  bool is_even = (world_.rank() % 2 == 0); // NOLINT Assuming the condition is true

  auto request_fork = [&](int neighbor, int& status) {
    world_.send(neighbor, 0, status_);
    if (world_.iprobe(neighbor, 0)) {
      world_.recv(neighbor, 0, status);
      return (status == 0);
    }
    return false;
  };

  if (is_even) {
    if (request_fork(l_philosopher_, l_status) && request_fork(r_philosopher_, r_status)) {
      status_ = 1;
      world_.isend(l_philosopher_, 0, status_);
      world_.isend(r_philosopher_, 0, status_);
      boost::mpi::wait_all(&req1, &req2);
    }
  } else {
    if (request_fork(r_philosopher_, r_status) && request_fork(l_philosopher_, l_status)) {
      status_ = 1;
      world_.send(l_philosopher_, 0, status_);
      world_.send(r_philosopher_, 0, status_);
    }
  }
  return true;
}

bool stroganov_m_dining_philosophers_mpi::DiningPhilosophersMPI::RunImpl() {
  do {
    Think();
    this->DistributionForks();
    Eat();
    ReleaseForks();
    if (CheckDeadlock()) {
      return false;
    }
  } while (!CheckAllThink());
  return true;
}

bool stroganov_m_dining_philosophers_mpi::DiningPhilosophersMPI::CheckAllThink() {
  std::vector<int> all_states;
  boost::mpi::all_gather(world_, status_, all_states);
  world_.barrier();
  return std::ranges::all_of(all_states, [](int state) { return state == 0; });
}

bool stroganov_m_dining_philosophers_mpi::DiningPhilosophersMPI::CheckDeadlock() {
  std::vector<int> all_states(world_.size(), 0);
  boost::mpi::all_gather(world_, status_, all_states);
  // return std::ranges::all_of(all_states, [](const int& state) { return state == 2; });
  return std::ranges::all_of(all_states, [](int state) { return state == 2; });
}

bool stroganov_m_dining_philosophers_mpi::DiningPhilosophersMPI::PostProcessingImpl() {
  world_.barrier();
  while (world_.iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG)) {
    int lastes_message = 0;
    world_.recv(MPI_ANY_SOURCE, MPI_ANY_TAG, lastes_message);
  }
  world_.barrier();
  return true;
}