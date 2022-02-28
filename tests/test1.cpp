#include <gtest/gtest.h>

#include <filesystem>

#include <DirectoryStatistics.hpp>

class DirectoryStatisticsTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::filesystem::create_directory("test1_directory");
        ds = std::make_shared<DirectoryStatistics>("test1_directory");
    }

    void TearDown() override {
        std::filesystem::remove("test1_directory");
    }

    std::shared_ptr<DirectoryStatistics> ds;
};

TEST_F(DirectoryStatisticsTest, EmptyDirectory) {
    EXPECT_TRUE(ds->getRootDirectory()->isEmpty());
}

