// Copyright 2023 Nesterov Alexander
#include <gtest/gtest.h>

#include <boost/mpi/timer.hpp>
#include <vector>

#include "core/perf/include/perf.hpp"
#include "mpi/stroganov_m_dining_philosophers/include/ops_mpi.hpp"

TEST(stroganov_m_dining_philosophers, test_PipelineRun) {
  boost::mpi::communicator world;

  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();
  int count_philosophers = world.size();
  if (world.rank() == 0) {
    taskData->inputs_count.push_back(count_philosophers);
  }

  auto DiningPhilosophersMPI = std::make_shared<stroganov_m_dining_philosophers::DiningPhilosophersMPI>(taskData);

  if (world.size() < 2) {
    GTEST_SKIP() << "Skipping test due to failed validation";
  }

  DiningPhilosophersMPI->ValidationImpl();
  DiningPhilosophersMPI->PreProcessingImpl();
  DiningPhilosophersMPI->RunImpl();
  DiningPhilosophersMPI->PostProcessingImpl();

  auto perfAttr = std::make_shared<ppc::core::PerfAttr>();
  perfAttr->num_running = 10;
  const boost::mpi::timer current_timer;
  perfAttr->current_timer = [&] { return current_timer.elapsed(); };

  auto perfResults = std::make_shared<ppc::core::PerfResults>();

  auto perfAnalyzer = std::make_shared<ppc::core::Perf>(DiningPhilosophersMPI);
  perfAnalyzer->PipelineRun(perfAttr, perfResults);

  if (world.rank() == 0) {
    ppc::core::Perf::PrintPerfStatistic(perfResults);
    int expected_philosophers_finished = world.size();
    ASSERT_EQ(expected_philosophers_finished, world.size());
  }
}

TEST(stroganov_m_dining_philosophers, test_task_Run) {
  boost::mpi::communicator world;

  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();
  int count_philosophers = world.size();
  if (world.rank() == 0) {
    taskData->inputs_count.push_back(count_philosophers);
  }

  auto DiningPhilosophersMPI = std::make_shared<stroganov_m_dining_philosophers::DiningPhilosophersMPI>(taskData);

  if (world.size() < 2) {
    GTEST_SKIP() << "Skipping test due to failed validation";
  }

  DiningPhilosophersMPI->ValidationImpl();
  DiningPhilosophersMPI->PreProcessingImpl();
  DiningPhilosophersMPI->RunImpl();
  DiningPhilosophersMPI->PostProcessingImpl();

  auto perfAttr = std::make_shared<ppc::core::PerfAttr>();
  perfAttr->num_running = 10;
  const boost::mpi::timer current_timer;
  perfAttr->current_timer = [&] { return current_timer.elapsed(); };

  auto perfResults = std::make_shared<ppc::core::PerfResults>();

  auto perfAnalyzer = std::make_shared<ppc::core::Perf>(DiningPhilosophersMPI);
  perfAnalyzer->TaskRun(perfAttr, perfResults);

  if (world.rank() == 0) {
    ppc::core::Perf::PrintPerfStatistic(perfResults);
    int expected_philosophers_finished = world.size();
    ASSERT_EQ(expected_philosophers_finished, world.size());
  }
}
