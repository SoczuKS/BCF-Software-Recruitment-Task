#include <gtest/gtest.h>

#include <filesystem>

#include <DirectoryStatistics.hpp>

class DirectoryStatisticsTest : public ::testing::Test {
protected:
    void SetUp() override {
        ds = std::make_shared<DirectoryStatistics>("../tests/test_directory_1");
    }

    std::shared_ptr<DirectoryStatistics> ds;
};

TEST_F(DirectoryStatisticsTest, GetTotalTest2) {
    EXPECT_EQ(ds->getTotalNumberOfDirectories(), 2119);
    EXPECT_EQ(ds->getTotalNumberOfFiles(), 896);
}