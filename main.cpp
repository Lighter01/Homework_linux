#include <iostream>
#include "account.h"
#include <algorithm>
#include <ranges>
#include <map>
#include <unordered_map>
#include <unordered_set>

int main()
{
    acc::generateDatabase();
    for (const auto& it : acc::database) {
        std::cout << "--> " << it.id << "\n";
    }

    // Task 1 - выбрать всех, кто использует bash, с помощью std::ranges::find_if
    std::cout << "------------TASK 1------------\n";
    auto it = std::ranges::find_if(acc::database, [](acc::Account x) { return x.shell.second == "bash";});
    while (it != acc::database.end()) {
        std::cout << it->name << " " << it->shell.first << "\n";
        it = std::ranges::find_if(it + 1, acc::database.end(), [](acc::Account x) { return x.shell.second == "bash";}); // why std::ranges so?
    }

    // Task 2 - записать базу данных юзеров в std::map, найти всех, у кого id в диапазоне [1,999]
    // ? В чем смысл этого задания, если предполагалось, что id могут повторяться? Причем тут std::map?
    std::cout << "------------TASK 2------------\n";
    std::map<int, acc::Account> users_map;
    for (auto& it : acc::database) {
        users_map[it.id] = it;
    }
    auto it_map_left  = users_map.upper_bound(0);
    auto it_map_right = users_map.lower_bound(1000);
    for (; it_map_left != it_map_right; it_map_left = std::next(it_map_left, 1)) { // might use ++it_map_left, but it's syntax sugar
        std::cout << it_map_left->second.name << " " << it_map_left->second.id << "\n";
    }

    // Task 3 - определить кол-во пользователей каждой из доступных оболочек с помощью std::unordered_map
    std::cout << "------------TASK 3------------\n";
    std::unordered_map<std::string, std::vector<acc::Account>> shellUsers;
    for (auto it : acc::database) {
        shellUsers[it.shell.first].push_back(it);
    }
    for (auto it : shellUsers) {
        std::cout << it.first << " --- "<< it.second.size() << "\n";
    }

    // Task 4 - выбрать всех пользователей с одинаковыми идентификаторами, применив std::unordered_set
    // То же самое, что и во 2 задании
        std::cout << "------------TASK 4------------\n";
        std::cout << "Look inside implementation\n";

        std::unordered_set<std::pair<int, int>, pair_hash<int, int>, pair_equal<int, int>> unique_id_users; // std::pair< id , index in database array>
        int prev_unique_id_users_size = 0;

        for (int i = 0; i < acc::database.size(); ++i) {
            unique_id_users.insert(std::make_pair(acc::database.at(i).id, i));
            if (unique_id_users.size() == prev_unique_id_users_size) {

                auto tmp_index = unique_id_users.find(std::pair<int, int>(acc::database.at(i).id, i));

                std::cout << acc::database.at(i).name << " " << acc::database.at(i).id << " --- "
                          << acc::database.at(tmp_index->second).name << " "
                          << acc::database.at(tmp_index->second).id << "\n";
            }
            prev_unique_id_users_size = unique_id_users.size();
        }
}

