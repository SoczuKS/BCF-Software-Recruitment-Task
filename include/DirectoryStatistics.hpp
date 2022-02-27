#pragma once

#include <filesystem>
#include <memory>
#include <ostream>
#include <string>

#include <Directory.hpp>

class DirectoryStatistics {
public:
    DirectoryStatistics(const std::string&);

    friend std::ostream& operator<<(std::ostream& os, DirectoryStatistics& ds) {
        ds.print(os);
        return os;
    }

    const std::shared_ptr<Directory> getRootDirectory() const { return rootDirectory; }

private:
    std::filesystem::path rootDirectoryPath{};
    std::shared_ptr<Directory> rootDirectory{nullptr};

    void gatherStatistics();
    void analyzeDirectory(const std::shared_ptr<Directory>, const std::filesystem::path&);
    void analyzeFile(const std::shared_ptr<File>, const std::filesystem::path&);
    void print(std::ostream&);
};
