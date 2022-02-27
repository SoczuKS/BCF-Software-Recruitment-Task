#pragma once

#include <string>

struct File {
    File(const std::string& name_) : name(name_) {}

    std::string name;
    unsigned int emptyLines;
    unsigned int nonemptyLines;
    unsigned int words;
    unsigned int letters;
};
