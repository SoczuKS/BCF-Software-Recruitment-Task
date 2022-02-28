#pragma once

#include <File.hpp>

#include <memory>
#include <ostream>
#include <string>
#include <vector>

struct Directory {
    Directory(const std::string& name_) : name(name_) {}

    void print(std::ostream& os, unsigned int level) {
        for (unsigned int i = 0; i < level; ++i) {
            os << ' ' << ' ';
        }

        os << name << " [d:" << directories.size() << ", f:" << files.size() << ']' << '\n';

        for (auto& dir : directories) {
            dir->print(os, level + 1);
        }

        for (auto& file : files) {
            file->print(os, level);
        }
    }

    bool isEmpty() const { return directories.empty() && files.empty(); }

    const std::shared_ptr<Directory> getDirectoryByName(const std::string& dirName) {
        for (auto& directory : directories) {
            if (directory->name == dirName) {
                return directory;
            }
        }

        return nullptr;
    }

    const std::shared_ptr<File> getFileByName(const std::string& fileName) {
        for (auto& file : files) {
            if (file->name == fileName) {
                return file;
            }
        }

        return nullptr;
    }

    unsigned long long getTotalNumberOfDirectories() const {
        unsigned long long total{0LLU};
        total += directories.size();

        for (auto& directory : directories) {
            total += directory->getTotalNumberOfDirectories();
        }

        return total;
    }

    unsigned long long getTotalNumberOfFiles() const {
        unsigned long long total{0LLU};
        total += files.size();

        for (auto& directory : directories) {
            total += directory->getTotalNumberOfFiles();
        }

        return total;
    }

    unsigned long long getTotalNumberOfEmptyLines() const {
        unsigned long long total{0LLU};

        for (auto& file : files) {
            total += file->emptyLines;
        }

        for (auto& directory : directories) {
            total += directory->getTotalNumberOfEmptyLines();
        }

        return total;
    }

    unsigned long long getTotalNumberOfNonemptyLines() const {
        unsigned long long total{0LLU};

        for (auto& file : files) {
            total += file->nonemptyLines;
        }

        for (auto& directory : directories) {
            total += directory->getTotalNumberOfNonemptyLines();
        }

        return total;
    }

    std::string name;
    std::vector<std::shared_ptr<Directory>> directories;
    std::vector<std::shared_ptr<File>> files;
};
