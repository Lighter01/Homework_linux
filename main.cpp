#include <iostream>
#include <map>
#include <chrono>
#include "nicknamegen.h"
#include "user.h"
#include "write_file.h"
#include "data_preparations.h"

int main()
{
    auto t1 = std::chrono::high_resolution_clock::now();

    std::vector<anime> anime_list;
    preparations::readAnimeList(anime_list);

    nng::instance().load(".\\resources");

    std::map<std::string, user> unique_users;
    createMultipleUsers(1000, unique_users, anime_list); // I don't lile that I'm pushing "anime_list" inside function

    generateSyntheticDataset(unique_users, false);

    auto t2 = std::chrono::high_resolution_clock::now();

    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1);
    std::chrono::duration<double> seconds_double = t2 - t1;
    std::cout << "overall time: " << seconds.count() << " seconds\n";
    std::cout << "overall time: " << seconds_double.count() << " seconds double\n";

    //debugger can't read anime using pointer
}
