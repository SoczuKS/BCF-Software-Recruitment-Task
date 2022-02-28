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

TEST_F(DirectoryStatisticsTest, FileAnalyzerTest) {
    auto& rootDir = ds->getRootDirectory();
    // Empty file
    EXPECT_TRUE(rootDir->getDirectoryByName("dir0")->getFileByName("empty.txt")->isEmpty());

    auto file = rootDir->getDirectoryByName("dir0")->getFileByName("1_word_1_line.txt");
    EXPECT_EQ(file->letters, 4);
    EXPECT_EQ(file->words, 1);
    EXPECT_EQ(file->nonemptyLines, 1);
    EXPECT_EQ(file->emptyLines, 0);

    file = rootDir->getDirectoryByName("dir1")->getFileByName("1_word_2_lines.txt");
    EXPECT_EQ(file->letters, 4);
    EXPECT_EQ(file->words, 1);
    EXPECT_EQ(file->nonemptyLines, 1);
    EXPECT_EQ(file->emptyLines, 1);

    file = rootDir->getDirectoryByName("dir1")->getFileByName("91_words_467_letters_6_lines_1_empty.txt");
    EXPECT_EQ(file->letters, 467);
    EXPECT_EQ(file->words, 91);
    EXPECT_EQ(file->nonemptyLines, 4);
    EXPECT_EQ(file->emptyLines, 1);

    file = rootDir->getFileByName("65_words_253_letters_6_lines_3_empty.txt");
    EXPECT_EQ(file->letters, 253);
    EXPECT_EQ(file->words, 65);
    EXPECT_EQ(file->nonemptyLines, 3);
    EXPECT_EQ(file->emptyLines, 3);
}
