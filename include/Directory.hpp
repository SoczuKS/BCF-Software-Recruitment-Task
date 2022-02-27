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

        os << name << '\n';

        for (auto& dir : directories) {
            dir->print(os, level + 1);
        }
    }

    bool isEmpty() const { return directories.empty() && files.empty(); }

    std::string name;
    std::vector<std::shared_ptr<Directory>> directories;
    std::vector<std::shared_ptr<File>> files;
};
