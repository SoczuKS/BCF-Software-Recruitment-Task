#pragma once

#include <filesystem>
#include <memory>
#include <ostream>
#include <string>

#include <Directory.hpp>
#include <ThreadPool.hpp>

class DirectoryStatistics {
public:
    DirectoryStatistics(const std::string&, const unsigned int=64);

    friend std::ostream& operator<<(std::ostream& os, DirectoryStatistics& ds) {
        ds.print(os);
        return os;
    }

    const std::shared_ptr<Directory> getRootDirectory() const { return rootDirectory; }

private:
    std::filesystem::path rootDirectoryPath{};
    std::shared_ptr<Directory> rootDirectory{nullptr};
    std::shared_ptr<ThreadPool> threadPool;

    void gatherStatistics();
    void analyzeDirectory(const std::shared_ptr<Directory>, const std::filesystem::path&);
    void analyzeFile(const std::shared_ptr<File>, const std::filesystem::path&);
    void print(std::ostream&);
};
