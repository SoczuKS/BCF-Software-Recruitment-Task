#include <gtest/gtest.h>

#include <memory>

#include <DirectoryStatistics.hpp>

TEST(DirectoryStatisticsTest, NonExistingDirectory) {
    auto ds = std::make_shared<DirectoryStatistics>("non_existing_directory");
    EXPECT_EQ(ds->getRootDirectory(), nullptr);
}