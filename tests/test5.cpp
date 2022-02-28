#include <gtest/gtest.h>

#include <filesystem>

#include <DirectoryStatistics.hpp>

class DirectoryStatisticsTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::filesystem::copy("../tests/test_directory_0", "test5_directory", std::filesystem::copy_options::recursive);

        ds = std::make_shared<DirectoryStatistics>("test5_directory");
    }

    void TearDown() override {
        std::filesystem::remove_all("test5_directory");
    }

    std::shared_ptr<DirectoryStatistics> ds;
};

TEST_F(DirectoryStatisticsTest, GetTotalTest) {
    EXPECT_EQ(ds->getTotalNumberOfDirectories(), 2);
    EXPECT_EQ(ds->getTotalNumberOfFiles(), 5);
    EXPECT_EQ(ds->getTotalNumberOfEmptyLines(), 5);
    EXPECT_EQ(ds->getTotalNumberOfNonemptyLines(), 9);
}


