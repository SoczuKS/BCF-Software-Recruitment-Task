#include <DirectoryStatistics.hpp>

#include <iostream>

int main() {
    auto directoryStatistics = DirectoryStatistics(".");

    std::cout << directoryStatistics << std::endl;

    return 0;
}
