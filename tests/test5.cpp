#include <gtest/gtest.h>

#include <filesystem>

#include <DirectoryStatistics.hpp>

class DirectoryStatisticsTest : public ::testing::Test {
protected:
    void SetUp() override {
        ds = std::make_shared<DirectoryStatistics>("../tests/test_directory_0");
    }

    std::shared_ptr<DirectoryStatistics> ds;
};

TEST_F(DirectoryStatisticsTest, GetTotalTest) {
    EXPECT_EQ(ds->getTotalNumberOfDirectories(), 2);
    EXPECT_EQ(ds->getTotalNumberOfFiles(), 5);
    EXPECT_EQ(ds->getTotalNumberOfEmptyLines(), 5);
    EXPECT_EQ(ds->getTotalNumberOfNonemptyLines(), 9);
}


