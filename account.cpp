#include "account.h"
#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <random>
#include <set>
#include <unordered_set>
#include <map>
#include <functional>

acc::Account::Account() : id(UINT_MAX), login(""), name(""), shell(std::make_pair("", "")), home_directory("")
{

}

acc::Account::Account(const unsigned int& _id, const std::string& _login, const std::string& _name, const std::pair<std::string, std::string>& _shell, const std::string& _home_directory) :
    id(_id), login(_login), name(_name), shell(_shell), home_directory(_home_directory)
{

}


//bool acc::Account::operator==(const Account& account) {
//    return (this->name == account.name && this->id == account.id
//         && this->home_directory == account.home_directory && this->login == account.login
//         && this->shell == account.shell);
//}

bool acc::Account::operator()(const Account& account_1, const Account& account_2) const {
    return account_1.id < account_2.id;
}



void acc::generateDatabase() {
    std::ifstream names("data\\names_0.txt");
    std::ifstream shells("data\\list_of_shells.txt");
//    std::cout << names.is_open() << " " << shells.is_open() << "\n";

    std::string tmp_string;
    std::stringstream tmp_stream;
    Account tmp_user;
    std::pair<std::string, std::string> tmp_pair;
    int counter = 0;

    while (std::getline(names, tmp_string)) {
        namesList.push_back(tmp_string);
    }
    while (std::getline(shells, tmp_string)) {
        tmp_stream << tmp_string;
        while (std::getline(tmp_stream, tmp_string, ',')) {
            switch (counter++) {
            case 0: tmp_pair.first = tmp_string; break;
            case 1: tmp_pair.second = tmp_string; break;
            }
        }
        counter = 0;
        shellsList.push_back(tmp_pair);
        tmp_stream.clear();
    }

    std::random_device random_device;
    std::uniform_int_distribution<std::size_t> distribution_0{0, namesList.size() - 1};
    std::uniform_int_distribution<std::size_t> distribution_1{0, shellsList.size() - 1};

    std::multimap<std::string, std::pair<std::string, std::string>> unique_users;
    for (auto it : namesList) {
        unique_users.insert(std::make_pair(namesList.at(distribution_0(random_device)), shellsList.at(distribution_1(random_device))));
    }

    std::unordered_set<int> unique_id; // TASK 4 HERE
    for (auto it : unique_users) {
        for (int i = 0; i < unique_users.count(it.first); ++i) {
            tmp_user.name = it.first;
            tmp_user.login = it.first + std::to_string(i);
            tmp_user.shell = it.second;

            // Give unique id to user
            int id = 0;
            while (id == 0 || unique_id.find(id) != unique_id.end()) { // change to && to check task 4
                id = std::uniform_int_distribution<std::size_t>(1, 10000)(random_device);
//                unique_id.insert(id);
            }
            tmp_user.id = id;

            tmp_user.home_directory = "<root>/home/" + tmp_user.login;
        }
        database.push_back(tmp_user);
    }
    names.close();
    shells.close();
}
