#include <gtest/gtest.h>

#include <filesystem>

#include <DirectoryStatistics.hpp>

class DirectoryStatisticsTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::filesystem::copy("../tests/test_directory_1", "test6_directory", std::filesystem::copy_options::recursive);

        ds = std::make_shared<DirectoryStatistics>("test6_directory");
    }

    void TearDown() override {
        std::filesystem::remove_all("test6_directory");
    }

    std::shared_ptr<DirectoryStatistics> ds;
};

TEST_F(DirectoryStatisticsTest, GetTotalTest2) {
    EXPECT_EQ(ds->getTotalNumberOfDirectories(), 2119);
    EXPECT_EQ(ds->getTotalNumberOfFiles(), 896);
}