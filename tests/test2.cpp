#include <gtest/gtest.h>

#include <iostream>
#include <cstring>
#include <filesystem>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>

#include <DirectoryStatistics.hpp>

class DirectoryStatisticsTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::filesystem::create_directory("test2_directory");
        mkfifo("test2_directory/pipe", 0644);
        sockaddr_un addr;
        addr.sun_family = AF_UNIX;
        std::strcpy(addr.sun_path, "test2_directory/sock");
        int fd = socket(PF_UNIX, SOCK_STREAM, 0);
        bind(fd, reinterpret_cast<sockaddr*>(&addr), sizeof addr);
        std::filesystem::create_symlink("test2", "test2_directory/symlink");

        ds0 = std::make_shared<DirectoryStatistics>("/dev/sda");                // block_file
        ds1 = std::make_shared<DirectoryStatistics>("/dev/null");               // character_file
        ds2 = std::make_shared<DirectoryStatistics>("test2_directory");         // other non regular files
    }

    void TearDown() override {
        std::filesystem::remove_all("test2_directory");
    }

    std::shared_ptr<DirectoryStatistics> ds0;
    std::shared_ptr<DirectoryStatistics> ds1;
    std::shared_ptr<DirectoryStatistics> ds2;
};

TEST_F(DirectoryStatisticsTest, NonRegularFilesAndDirectories) {
    EXPECT_EQ(ds0->getRootDirectory(), nullptr);
    EXPECT_EQ(ds1->getRootDirectory(), nullptr);
    EXPECT_TRUE(ds2->getRootDirectory()->isEmpty());
}

