// Copyright 2023 Nesterov Alexander
#include <gtest/gtest.h>
#include <mpi.h>

#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>
#include <thread>
#include <vector>

#include "mpi/stroganov_m_dining_philosophers/include/ops_mpi.hpp"
/*
TEST(stroganov_m_dining_philosophers, Valid_Number_Of_Philosophers) {
  boost::mpi::communicator world;
  int count_philosophers = 5;
  auto taskData = std::make_shared<ppc::core::TaskData>();

  if (world.rank() == 0) {
    taskData->inputs_count.push_back(count_philosophers);
  }

  stroganov_m_dining_philosophers::DiningPhilosophersMPI DiningPhilosophersMPI(taskData);
  if (world.size() < 2) {
    GTEST_SKIP();
  }
  ASSERT_TRUE(DiningPhilosophersMPI.ValidationImpl());
  ASSERT_TRUE(DiningPhilosophersMPI.PreProcessingImpl());
  ASSERT_TRUE(DiningPhilosophersMPI.RunImpl());
  ASSERT_TRUE(DiningPhilosophersMPI.PostProcessingImpl());
}

TEST(stroganov_m_dining_philosophers, Deadlock_Free_Execution) {
  boost::mpi::communicator world;
  auto taskData = std::make_shared<ppc::core::TaskData>();
  int count_philosophers = world.size();

  if (world.rank() == 0) {
    taskData->inputs_count.push_back(count_philosophers);
  }

  stroganov_m_dining_philosophers::DiningPhilosophersMPI DiningPhilosophersMPI(taskData);
  if (world.size() < 2) {
    GTEST_SKIP();
  }
  ASSERT_TRUE(DiningPhilosophersMPI.ValidationImpl());
  ASSERT_TRUE(DiningPhilosophersMPI.PreProcessingImpl());
  ASSERT_TRUE(DiningPhilosophersMPI.RunImpl());
  ASSERT_TRUE(DiningPhilosophersMPI.PostProcessingImpl());
}

TEST(stroganov_m_dining_philosophers, Custom_Logic_Execution) {
  boost::mpi::communicator world;
  int count_philosophers = 4;
  auto taskData = std::make_shared<ppc::core::TaskData>();

  if (world.rank() == 0) {
    taskData->inputs_count.push_back(count_philosophers);
  }

  stroganov_m_dining_philosophers::DiningPhilosophersMPI DiningPhilosophersMPI(taskData);
  if (world.size() < 2) {
    GTEST_SKIP();
  }

  ASSERT_TRUE(DiningPhilosophersMPI.ValidationImpl());
  ASSERT_TRUE(DiningPhilosophersMPI.PreProcessingImpl());
  ASSERT_TRUE(DiningPhilosophersMPI.RunImpl());
  ASSERT_TRUE(DiningPhilosophersMPI.PostProcessingImpl());
}

TEST(stroganov_m_dining_philosophers, Test_default_num_philosophers) {
  boost::mpi::communicator world;

  int count_philosophers = world.size();

  auto taskData = std::make_shared<ppc::core::TaskData>();
  taskData->inputs_count.push_back(count_philosophers);

  stroganov_m_dining_philosophers::DiningPhilosophersMPI DiningPhilosophersMPI(taskData);

  if (DiningPhilosophersMPI.ValidationImpl()) {
    ASSERT_TRUE(DiningPhilosophersMPI.PreProcessingImpl());
    ASSERT_TRUE(DiningPhilosophersMPI.RunImpl());
    ASSERT_TRUE(DiningPhilosophersMPI.PostProcessingImpl());

    bool deadlock_detected = DiningPhilosophersMPI.check_deadlock();
    if (world.rank() == 0) {
      ASSERT_FALSE(deadlock_detected);
    }
  } else {
    GTEST_SKIP() << "Skipping test due to failed validation";
  }
}

TEST(stroganov_m_dining_philosophers, Test_with_5_philosophers) {
  boost::mpi::communicator world;

  int count_philosophers = 5;

  auto taskData = std::make_shared<ppc::core::TaskData>();
  taskData->inputs_count.push_back(count_philosophers);

  stroganov_m_dining_philosophers::DiningPhilosophersMPI DiningPhilosophersMPI(taskData);

  if (world.size() < 2) {
    GTEST_SKIP();
  }
  ASSERT_TRUE(DiningPhilosophersMPI.ValidationImpl());
  ASSERT_TRUE(DiningPhilosophersMPI.PreProcessingImpl());
  ASSERT_TRUE(DiningPhilosophersMPI.RunImpl());
  ASSERT_TRUE(DiningPhilosophersMPI.PostProcessingImpl());

  bool deadlock_detected = DiningPhilosophersMPI.check_deadlock();
  if (world.rank() == 0) {
    ASSERT_FALSE(deadlock_detected);
  }
}

TEST(stroganov_m_dining_philosophers, Test_with_15_philosophers) {
  boost::mpi::communicator world;

  int count_philosophers = 15;

  auto taskData = std::make_shared<ppc::core::TaskData>();
  taskData->inputs_count.push_back(count_philosophers);

  stroganov_m_dining_philosophers::DiningPhilosophersMPI DiningPhilosophersMPI(taskData);

  if (world.size() < 2) {
    GTEST_SKIP();
  }
  ASSERT_TRUE(DiningPhilosophersMPI.ValidationImpl());
  ASSERT_TRUE(DiningPhilosophersMPI.PreProcessingImpl());
  ASSERT_TRUE(DiningPhilosophersMPI.RunImpl());
  ASSERT_TRUE(DiningPhilosophersMPI.PostProcessingImpl());

  bool deadlock_detected = DiningPhilosophersMPI.check_deadlock();
  if (world.rank() == 0) {
    ASSERT_FALSE(deadlock_detected);
  }
}

TEST(stroganov_m_dining_philosophers, Test_with_25_philosophers) {
  boost::mpi::communicator world;

  int count_philosophers = 25;

  auto taskData = std::make_shared<ppc::core::TaskData>();
  taskData->inputs_count.push_back(count_philosophers);

  stroganov_m_dining_philosophers::DiningPhilosophersMPI DiningPhilosophersMPI(taskData);

  if (world.size() < 2) {
    GTEST_SKIP();
  }
  ASSERT_TRUE(DiningPhilosophersMPI.ValidationImpl());
  ASSERT_TRUE(DiningPhilosophersMPI.PreProcessingImpl());
  ASSERT_TRUE(DiningPhilosophersMPI.RunImpl());
  ASSERT_TRUE(DiningPhilosophersMPI.PostProcessingImpl());

  bool deadlock_detected = DiningPhilosophersMPI.check_deadlock();
  if (world.rank() == 0) {
    ASSERT_FALSE(deadlock_detected);
  }
}

TEST(stroganov_m_dining_philosophers, Deadlock_Handling) {
  boost::mpi::communicator world;
  int count_philosophers = world.size();
  auto taskData = std::make_shared<ppc::core::TaskData>();

  if (world.rank() == 0) {
    taskData->inputs_count.push_back(count_philosophers);
  }

  stroganov_m_dining_philosophers::DiningPhilosophersMPI DiningPhilosophersMPI(taskData);

  if (world.size() < 2) {
    GTEST_SKIP();
  }

  ASSERT_TRUE(DiningPhilosophersMPI.ValidationImpl());
  ASSERT_TRUE(DiningPhilosophersMPI.PreProcessingImpl());
  ASSERT_TRUE(DiningPhilosophersMPI.RunImpl());
  bool local_deadlock = DiningPhilosophersMPI.check_deadlock();
  bool global_deadlock = boost::mpi::all_reduce(world, local_deadlock, std::logical_or<>());
  ASSERT_FALSE(global_deadlock);
  bool local_all_think = DiningPhilosophersMPI.check_all_think();
  bool global_all_think = boost::mpi::all_reduce(world, local_all_think, std::logical_and<>());
  ASSERT_TRUE(global_all_think);
  ASSERT_TRUE(DiningPhilosophersMPI.PostProcessingImpl());
}

TEST(stroganov_m_dining_philosophers, Single_Philosopher) {
  boost::mpi::communicator world;

  if (world.rank() == 0) {
    int count_philosophers = 1;
    auto taskData = std::make_shared<ppc::core::TaskData>();
    taskData->inputs_count.push_back(count_philosophers);

    stroganov_m_dining_philosophers::DiningPhilosophersMPI DiningPhilosophersMPI(taskData);

    ASSERT_FALSE(DiningPhilosophersMPI.ValidationImpl());
  }
}

TEST(stroganov_m_dining_philosophers, Invalid_Philosopher_Count) {
  boost::mpi::communicator world;

  if (world.rank() == 0) {
    int count_philosophers = -5;
    auto taskData = std::make_shared<ppc::core::TaskData>();
    taskData->inputs_count.push_back(count_philosophers);

    stroganov_m_dining_philosophers::DiningPhilosophersMPI DiningPhilosophersMPI(taskData);

    ASSERT_FALSE(DiningPhilosophersMPI.ValidationImpl());
  }
}

 */