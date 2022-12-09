#include "data_preparations.h"
#include <iostream>

void preparations::readAnimeList(std::vector<anime>& anime_list) {
    std::filesystem::path tmp_path = std::filesystem::current_path().string() + "\\start_data\\anime_cleaned.csv";
    std::ifstream anime_list_file(tmp_path);
//    std::cout << anime_list_file.is_open();

    std::string tmp_line;
    std::stringstream tmp_line_stream;
    std::vector<std::string> list_buffer;
    anime tmp_instance;
    int current_column_number;

    std::getline(anime_list_file, tmp_line); // read first line with names of columns;

    while (std::getline(anime_list_file, tmp_line)) {
        current_column_number = 0;
        tmp_line_stream.clear();
        tmp_line_stream << tmp_line;
        while (std::getline(tmp_line_stream, tmp_line, ';')) {
            if (tmp_line.size() > 0) {
                switch (current_column_number) {
                    case 0 : {
                        tmp_instance.set_id(std::stoi(tmp_line));
                        break;
                    }
                    case 1 : {
                        tmp_instance.set_title_name(tmp_line);
                        break;
                    }
                    case 8 : {
                        tmp_instance.set_number_of_episodes(std::stoi(tmp_line));
                        break;
                    }
                    case 11 : {
                        tmp_instance.set_aired(tmp_line);
                        break;
                    }
                    case 14 : {
                        tmp_instance.set_rating(tmp_line);
                        break;
                    }
                    case 17 : {
                        tmp_instance.set_rank(std::stoull(tmp_line));
                        break;
                    }
                    case 22 : {
                        tmp_instance.set_premiered(tmp_line);
                        break;
                    }
                    case 25 : {
                        tmp_instance.set_producer(tmp_line);
                        break;
                    }
                    case 26 : {
                        tmp_instance.set_licensor(tmp_line);
                        break;
                    }
                    case 27 : {
                        tmp_instance.set_studio(tmp_line);
                        break;
                    }
                    case 28 : {
                        tmp_instance.set_genre(tmp_line);
                        break;
                    }
                    default : break;
                }
            }
            current_column_number++;
        }
        anime_list.push_back(tmp_instance);
    }
    anime_list_file.close();
    return;
}
