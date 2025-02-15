// Copyright 2023 Nesterov Alexander
#pragma once

#include <boost/mpi/collectives.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/serialization/serialization.hpp>
#include <condition_variable>

#include "core/task/include/task.hpp"

namespace stroganov_m_dining_philosophers {

class DiningPhilosophersMPI : public ppc::core::Task {
 public:
  explicit DiningPhilosophersMPI(ppc::core::TaskDataPtr task_data) : Task(std::move(task_data)) {}
  bool PreProcessingImpl() override;
  bool ValidationImpl() override;
  bool RunImpl() override;
  bool PostProcessingImpl() override;

  void eat();
  void think();
  bool distribution_forks();
  void release_forks();
  bool check_deadlock();
  void resolve_deadlock();
  bool check_all_think();

 private:
  boost::mpi::communicator world;
  int status;
  int l_philosopher;
  int r_philosopher;
  int count_philosophers;
};

}  // namespace stroganov_m_dining_philosophers