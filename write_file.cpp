#include "write_file.h"
#include "sha256.h"
#include <iostream>


void generateSyntheticDataset(std::map<std::string, user>& unique_users, const bool& cipher_flag = false) {
    std::filesystem::path tmp_path = std::filesystem::current_path().string() + "\\generated_data_file.csv";
    std::ofstream generated_data_file(tmp_path);
    for (auto it : unique_users) {
        for (auto jt : it.second.get_anime_list()) {
            if (cipher_flag == false) {
                generated_data_file    << it.second.get_id() << ';' << it.second.get_nickname() << ';' << jt.first.get_anime().get_title_name()
                                       << ';' << jt.first.get_anime().get_genre() << ';' << jt.first.get_anime().get_number_of_episodes()
                                       << ';' << jt.first.get_anime().get_aired() << ';' << jt.first.get_anime().get_rating()
                                       << ';' << jt.first.get_anime().get_rank() << ';' << jt.first.get_anime().get_premiered()
                                       << ';' << jt.first.get_anime().get_studio() << ';' << jt.first.get_anime().get_producer()
                                       << ';' << jt.first.get_anime().get_licensor() << '\n';
            } else {
                generated_data_file     << sha256(std::to_string(it.second.get_id())) << ';' << sha256(it.second.get_nickname()) << ';' << jt.first.get_anime().get_title_name()
                                        << ';' << jt.first.get_anime().get_genre() << ';' << jt.first.get_anime().get_number_of_episodes()
                                        << ';' << jt.first.get_anime().get_aired() << ';' << jt.first.get_anime().get_rating()
                                        << ';' << jt.first.get_anime().get_rank() << ';' << jt.first.get_anime().get_premiered()
                                        << ';' << jt.first.get_anime().get_studio() << ';' << jt.first.get_anime().get_producer() << '\n';
            }
        }
    }
    generated_data_file.close();
}
