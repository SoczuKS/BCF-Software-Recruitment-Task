#include <DirectoryStatistics.hpp>

#include <iostream>

int main() {
    auto directoryStatistics = DirectoryStatistics("../sample_directories");

    std::cout << directoryStatistics << std::endl;

    return 0;
}
