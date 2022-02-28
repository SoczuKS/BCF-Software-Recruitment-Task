#pragma once

#include <string>

struct File {
    File(const std::string& name_) : name(name_) {}

    void print(std::ostream& os, unsigned int level) {
        for (unsigned int i = 0; i < level; ++i) {
            os << ' ' << ' ';
        }
        os << ' ';

        os << name << " [el:" << emptyLines << ", nel:" << nonemptyLines << ", w:" << words << ", l:" << letters << ']' << '\n';
    }

    bool isEmpty() const { return emptyLines == 0 && nonemptyLines == 0; }

    std::string name;
    unsigned int emptyLines{0U};
    unsigned int nonemptyLines{0U};
    unsigned int words{0U};
    unsigned int letters{0U};
};
