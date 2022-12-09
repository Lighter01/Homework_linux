#ifndef RANDOMNAME_H
#define RANDOMNAME_H

#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <filesystem>

namespace dataspace {
    static std::vector<std::string> names_dataset;

    void read_names_file();
    std::string get_rand_name();
}

#endif // RANDOMNAME_H
