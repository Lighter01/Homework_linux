#include "randomname.h"

void dataspace::read_names_file() {
    std::filesystem::path tmp_path = std::filesystem::current_path().wstring() + L"\\names\\names.csv";
    std::ifstream file(tmp_path);
    std::string name_instance;
    while (std::getline(file, name_instance)) {
        dataspace::names_dataset.push_back(name_instance);
    }
    file.close();
}

std::string dataspace::get_rand_name() {
    if (!dataspace::names_dataset.size()) { //bad
        read_names_file();
    }
    std::random_device random_device;
    std::uniform_int_distribution<std::size_t> distribution{0, dataspace::names_dataset.size() - 1};
    std::string random_name = dataspace::names_dataset.at(distribution(random_device));
    return random_name;
}
