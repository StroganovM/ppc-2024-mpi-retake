// Copyright 2023 Nesterov Alexander
#include <gtest/gtest.h>

#include <boost/mpi/communicator.hpp>
#include <memory>
#include <vector>

#include "core/task/include/task.hpp"
#include "mpi/stroganov_m_dining_philosophers/include/ops_mpi.hpp"
/*
TEST(stroganov_m_dining_philosophers_mpi, Valid_Number_Of_Philosophers) {
  boost::mpi::communicator world;
  int count_philosophers = 5;
  auto task_data = std::make_shared<ppc::core::TaskData>();

  if (world.rank() == 0) {
    task_data->inputs_count.push_back(count_philosophers);
  }

  stroganov_m_dining_philosophers_mpi::DiningPhilosophersMPI dining_philosophers_mpi(task_data);
  if (world.size() < 2) {
    GTEST_SKIP();
  }
  ASSERT_TRUE(dining_philosophers_mpi.ValidationImpl());
  ASSERT_TRUE(dining_philosophers_mpi.PreProcessingImpl());
  ASSERT_TRUE(dining_philosophers_mpi.RunImpl());
  ASSERT_TRUE(dining_philosophers_mpi.PostProcessingImpl());
}

TEST(stroganov_m_dining_philosophers_mpi, Deadlock_Free_Execution) {
  boost::mpi::communicator world;
  auto task_data = std::make_shared<ppc::core::TaskData>();
  int count_philosophers = world.size();

  if (world.rank() == 0) {
    task_data->inputs_count.push_back(count_philosophers);
  }

  stroganov_m_dining_philosophers_mpi::DiningPhilosophersMPI dining_philosophers_mpi(task_data);
  if (world.size() < 2) {
    GTEST_SKIP();
  }
  ASSERT_TRUE(dining_philosophers_mpi.ValidationImpl());
  ASSERT_TRUE(dining_philosophers_mpi.PreProcessingImpl());
  ASSERT_TRUE(dining_philosophers_mpi.RunImpl());
  ASSERT_TRUE(dining_philosophers_mpi.PostProcessingImpl());
}

TEST(stroganov_m_dining_philosophers_mpi, Custom_Logic_Execution) {
  boost::mpi::communicator world;
  int count_philosophers = 4;
  auto task_data = std::make_shared<ppc::core::TaskData>();

  if (world.rank() == 0) {
    task_data->inputs_count.push_back(count_philosophers);
  }

  stroganov_m_dining_philosophers_mpi::DiningPhilosophersMPI dining_philosophers_mpi(task_data);
  if (world.size() < 2) {
    GTEST_SKIP();
  }

  ASSERT_TRUE(dining_philosophers_mpi.ValidationImpl());
  ASSERT_TRUE(dining_philosophers_mpi.PreProcessingImpl());
  ASSERT_TRUE(dining_philosophers_mpi.RunImpl());
  ASSERT_TRUE(dining_philosophers_mpi.PostProcessingImpl());
}

TEST(stroganov_m_dining_philosophers_mpi, Test_default_num_philosophers) {
  boost::mpi::communicator world;

  int count_philosophers = world.size();

  auto task_data = std::make_shared<ppc::core::TaskData>();
  task_data->inputs_count.push_back(count_philosophers);

  stroganov_m_dining_philosophers_mpi::DiningPhilosophersMPI dining_philosophers_mpi(task_data);

  if (dining_philosophers_mpi.ValidationImpl()) {
    ASSERT_TRUE(dining_philosophers_mpi.PreProcessingImpl());
    ASSERT_TRUE(dining_philosophers_mpi.RunImpl());
    ASSERT_TRUE(dining_philosophers_mpi.PostProcessingImpl());

    bool deadlock_detected = dining_philosophers_mpi.CheckDeadlock();
    if (world.rank() == 0) {
      ASSERT_FALSE(deadlock_detected);
    }
  } else {
    GTEST_SKIP() << "Skipping test due to failed validation";
  }
}

TEST(stroganov_m_dining_philosophers_mpi, Test_with_5_philosophers) {
  boost::mpi::communicator world;

  int count_philosophers = 5;

  auto task_data = std::make_shared<ppc::core::TaskData>();
  task_data->inputs_count.push_back(count_philosophers);

  stroganov_m_dining_philosophers_mpi::DiningPhilosophersMPI dining_philosophers_mpi(task_data);

  if (world.size() < 2) {
    GTEST_SKIP();
  }
  ASSERT_TRUE(dining_philosophers_mpi.ValidationImpl());
  ASSERT_TRUE(dining_philosophers_mpi.PreProcessingImpl());
  ASSERT_TRUE(dining_philosophers_mpi.RunImpl());
  ASSERT_TRUE(dining_philosophers_mpi.PostProcessingImpl());

  bool deadlock_detected = dining_philosophers_mpi.CheckDeadlock();
  if (world.rank() == 0) {
    ASSERT_FALSE(deadlock_detected);
  }
}

TEST(stroganov_m_dining_philosophers_mpi, Test_with_15_philosophers) {
  boost::mpi::communicator world;

  int count_philosophers = 15;

  auto task_data = std::make_shared<ppc::core::TaskData>();
  task_data->inputs_count.push_back(count_philosophers);

  stroganov_m_dining_philosophers_mpi::DiningPhilosophersMPI dining_philosophers_mpi(task_data);

  if (world.size() < 2) {
    GTEST_SKIP();
  }
  ASSERT_TRUE(dining_philosophers_mpi.ValidationImpl());
  ASSERT_TRUE(dining_philosophers_mpi.PreProcessingImpl());
  ASSERT_TRUE(dining_philosophers_mpi.RunImpl());
  ASSERT_TRUE(dining_philosophers_mpi.PostProcessingImpl());

  bool deadlock_detected = dining_philosophers_mpi.CheckDeadlock();
  if (world.rank() == 0) {
    ASSERT_FALSE(deadlock_detected);
  }
}

TEST(stroganov_m_dining_philosophers_mpi, Test_with_25_philosophers) {
  boost::mpi::communicator world;

  int count_philosophers = 25;

  auto task_data = std::make_shared<ppc::core::TaskData>();
  task_data->inputs_count.push_back(count_philosophers);

  stroganov_m_dining_philosophers_mpi::DiningPhilosophersMPI dining_philosophers_mpi(task_data);

  if (world.size() < 2) {
    GTEST_SKIP();
  }
  ASSERT_TRUE(dining_philosophers_mpi.ValidationImpl());
  ASSERT_TRUE(dining_philosophers_mpi.PreProcessingImpl());
  ASSERT_TRUE(dining_philosophers_mpi.RunImpl());
  ASSERT_TRUE(dining_philosophers_mpi.PostProcessingImpl());

  bool deadlock_detected = dining_philosophers_mpi.CheckDeadlock();
  if (world.rank() == 0) {
    ASSERT_FALSE(deadlock_detected);
  }
}

TEST(stroganov_m_dining_philosophers_mpi, Deadlock_Handling) {
  boost::mpi::communicator world;
  int count_philosophers = world.size();
  auto task_data = std::make_shared<ppc::core::TaskData>();

  if (world.rank() == 0) {
    task_data->inputs_count.push_back(count_philosophers);
  }

  stroganov_m_dining_philosophers_mpi::DiningPhilosophersMPI dining_philosophers_mpi(task_data);

  if (world.size() < 2) {
    GTEST_SKIP();
  }

  ASSERT_TRUE(dining_philosophers_mpi.ValidationImpl());
  ASSERT_TRUE(dining_philosophers_mpi.PreProcessingImpl());
  ASSERT_TRUE(dining_philosophers_mpi.RunImpl());
  bool local_deadlock = dining_philosophers_mpi.CheckDeadlock();
  bool global_deadlock = boost::mpi::all_reduce(world, local_deadlock, std::logical_or<>());
  ASSERT_FALSE(global_deadlock);
  bool local_all_think = dining_philosophers_mpi.CheckAllThink();
  bool global_all_think = boost::mpi::all_reduce(world, local_all_think, std::logical_and<>());
  ASSERT_TRUE(global_all_think);
  ASSERT_TRUE(dining_philosophers_mpi.PostProcessingImpl());
}

TEST(stroganov_m_dining_philosophers_mpi, Single_Philosopher) {
  boost::mpi::communicator world;

  if (world.rank() == 0) {
    int count_philosophers = 1;
    auto task_data = std::make_shared<ppc::core::TaskData>();
    task_data->inputs_count.push_back(count_philosophers);

    stroganov_m_dining_philosophers_mpi::DiningPhilosophersMPI dining_philosophers_mpi(task_data);

    ASSERT_FALSE(dining_philosophers_mpi.ValidationImpl());
  }
}
*/
TEST(stroganov_m_dining_philosophers_mpi, Invalid_Philosopher_Count) {
  boost::mpi::communicator world;

  if (world.rank() == 0) {
    int count_philosophers = -5;
    auto task_data = std::make_shared<ppc::core::TaskData>();
    task_data->inputs_count.push_back(count_philosophers);

    stroganov_m_dining_philosophers_mpi::DiningPhilosophersMPI dining_philosophers_mpi(task_data);

    ASSERT_FALSE(dining_philosophers_mpi.ValidationImpl());
  }
}
