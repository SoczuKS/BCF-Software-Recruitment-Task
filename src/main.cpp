#include <DirectoryStatistics.hpp>

#include <iostream>

int main(int argc, char *argv[]) {
    auto directoryStatistics = DirectoryStatistics("../sample_directories");

    std::cout << directoryStatistics << std::endl;

    return 0;
}
