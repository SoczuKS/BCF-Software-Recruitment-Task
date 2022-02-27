#pragma once

#include <File.hpp>

#include <string>
#include <vector>

struct Directory {
    Directory(const std::string& name_) : name(name_) {}

    std::string name;
    std::vector<Directory> directories;
    std::vector<File> files;
};
