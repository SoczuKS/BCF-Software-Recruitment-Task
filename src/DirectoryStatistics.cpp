#include <DirectoryStatistics.hpp>

DirectoryStatistics::DirectoryStatistics(const std::string& rootDirectoryPathString) {
    rootDirectoryPath = std::filesystem::path(rootDirectoryPathString);
    gatherStatistics();
}

void DirectoryStatistics::gatherStatistics() {
    if (!std::filesystem::exists(rootDirectoryPath) or !std::filesystem::is_directory(rootDirectoryPath)) {
        return;
    }

    rootDirectory = std::make_shared<Directory>(rootDirectoryPath.filename());
    analyzeDirectory(rootDirectory, rootDirectoryPath);
}

void DirectoryStatistics::print(std::ostream& os) {
    if (!rootDirectory) {
        os << "Given directory doesn't exist\n";
        return;
    }

    rootDirectory->print(os, 0);
}

void DirectoryStatistics::analyzeDirectory(const std::shared_ptr<Directory> directory, const std::filesystem::path& directoryPath) {
    if (std::filesystem::is_empty(directoryPath)) {
        return;
    }

    for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_directory()) {
            auto entryDirectory = std::make_shared<Directory>(entry.path().filename());
            directory->directories.push_back(entryDirectory);
            analyzeDirectory(entryDirectory, entry);
        } else if (entry.is_regular_file()) {
            auto entryFile = std::make_shared<File>(entry.path().filename());
            directory->files.push_back(entryFile);
            analyzeFile(entryFile, entry);
        }
    }
}

void DirectoryStatistics::analyzeFile(const std::shared_ptr<File> file, const std::filesystem::path& filePath) {

}
