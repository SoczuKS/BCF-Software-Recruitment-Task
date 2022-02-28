#include <gtest/gtest.h>

#include <filesystem>

#include <DirectoryStatistics.hpp>

class DirectoryStatisticsTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::filesystem::copy("../tests/test_directory_0", "test3_directory", std::filesystem::copy_options::recursive);

        ds = std::make_shared<DirectoryStatistics>("test3_directory");
    }

    void TearDown() override {
        std::filesystem::remove_all("test3_directory");
    }

    std::shared_ptr<DirectoryStatistics> ds;
};

TEST_F(DirectoryStatisticsTest, GetByNameTest) {
    EXPECT_NE(ds->getRootDirectory(), nullptr);
    EXPECT_EQ(ds->getRootDirectory()->getFileByName("text.txt"), nullptr);
    EXPECT_EQ(ds->getRootDirectory()->getDirectoryByName("dir2"), nullptr);
    EXPECT_NE(ds->getRootDirectory()->getFileByName("65_words_253_letters_6_lines_3_empty.txt"), nullptr);
    EXPECT_NE(ds->getRootDirectory()->getDirectoryByName("dir0"), nullptr);
    EXPECT_NE(ds->getRootDirectory()->getDirectoryByName("dir0")->getFileByName("empty.txt"), nullptr);
    EXPECT_NE(ds->getRootDirectory()->getDirectoryByName("dir1"), nullptr);
    EXPECT_NE(ds->getRootDirectory()->getDirectoryByName("dir1")->getFileByName("1_word_2_lines.txt"), nullptr);
}
