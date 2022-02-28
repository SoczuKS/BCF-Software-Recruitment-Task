#include <DirectoryStatistics.hpp>

#include <fstream>

DirectoryStatistics::DirectoryStatistics(const std::string& rootDirectoryPathString,
                                         const unsigned int maxNumberOfThreads) :
        rootDirectoryPath(std::filesystem::path(rootDirectoryPathString)),
        threadPool(std::make_shared<ThreadPool>(maxNumberOfThreads)) {
    gatherStatistics();
}

void DirectoryStatistics::gatherStatistics() {
    if (!std::filesystem::exists(rootDirectoryPath) or !std::filesystem::is_directory(rootDirectoryPath)) {
        return;
    }

    rootDirectory = std::make_shared<Directory>(rootDirectoryPath.filename());
    analyzeDirectory(rootDirectory, rootDirectoryPath);

    threadPool->terminate();
}

void DirectoryStatistics::print(std::ostream& os) {
    if (!rootDirectory) {
        os << "Given directory doesn't exist\n";
        return;
    }

    rootDirectory->print(os, 0);

    os << "Total: [d: " << getTotalNumberOfDirectories();
    os << ", f:" << getTotalNumberOfFiles();
    os << ", nel:" << getTotalNumberOfNonemptyLines();
    os << ", el:" << getTotalNumberOfEmptyLines() << "]\n";
}

void DirectoryStatistics::analyzeDirectory(const std::shared_ptr<Directory> directory, const std::filesystem::path& directoryPath) {
    if (std::filesystem::is_empty(directoryPath)) {
        return;
    }

    for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_directory()) {
            auto entryDirectory = std::make_shared<Directory>(entry.path().filename());
            directory->directories.push_back(entryDirectory);

            std::function<void()> directoryJob{[this, entryDirectory, entry](){
                this->analyzeDirectory(entryDirectory, entry);
            }};

            threadPool->addJob(directoryJob);
        } else if (entry.is_regular_file()) {
            auto entryFile = std::make_shared<File>(entry.path().filename());
            directory->files.push_back(entryFile);

            std::function<void()> fileJob{[this, entryFile, entry]() {
                this->analyzeFile(entryFile, entry);
            }};
            threadPool->addJob(fileJob);
        }
    }
}

void DirectoryStatistics::analyzeFile(const std::shared_ptr<File> file, const std::filesystem::path& filePath) {
    if (std::filesystem::is_empty(filePath)) {
        return;
    }

    // Letters counter
    std::ifstream fileStream(filePath);
    char letter;
    while(fileStream >> letter) {
        if (std::isalpha(letter)) {
            file->letters++;
        }
    }
    fileStream.clear();
    fileStream.seekg(0);

    // Words counter
    std::string word;
    while(fileStream >> word) {
        file->words++;
    }
    fileStream.clear();
    fileStream.seekg(0);

    // Lines counter
    std::string line;
    while (std::getline(fileStream, line)) {
        bool emptyLine = true;
        for (auto& c : line) {
            if (!isspace(c)) {
                emptyLine = false;
                break;
            }
        }

        if (emptyLine) {
            file->emptyLines++;
        } else {
            file->nonemptyLines++;
        }
    }

    fileStream.close();
}
