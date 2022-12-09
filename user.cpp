#include "user.h"
#include <random>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include "nicknamegen.h"


static std::random_device random_device;


// Users_anime class

userspace::users_anime::users_anime()
{

}

userspace::users_anime::~users_anime()
{

}

// Getters

anime userspace::users_anime::get_anime() {
    return this->_anime;
}
int userspace::users_anime::get_watched_episodes() {
    return this->_watched_episodes;
}
std::string userspace::users_anime::get_start_date() {
    return this->_start_date;
}
std::string userspace::users_anime::get_end_date() {
    return this->_end_date;
}
int userspace::users_anime::get_user_score() {
    return this->_user_score;
}
////////////////////////

//Setters

void userspace::users_anime::set_anime(const anime& anime) {
    this->_anime = anime;
}
void userspace::users_anime::set_watched_episodes(const int& watched_episodes) {
    this->_watched_episodes = watched_episodes;
}
void userspace::users_anime::set_start_date(const std::string& start_date) {
    this->_start_date = start_date;
}
void userspace::users_anime::set_end_date(const std::string& end_date) {
    this->_end_date = end_date;
}
void userspace::users_anime::set_user_score(const int& score) {
    this->_user_score = score;
}
////////////////////////

/// Overloads
bool userspace::users_anime::operator== (const userspace::users_anime& obj) {
    return (this->_anime == obj._anime &&
            this->_start_date == obj._start_date &&
            this->_end_date == obj._end_date &&
            this->_watched_episodes == obj._watched_episodes &&
            this->_user_score == obj._user_score);
}

///////////////////////////////////////// END of "userspace::users_anime" class


//// user class

user::user() : _id(ULONG_MAX), _nickname("")
{
    _anime_list.clear();
}

// Getters
ull user::get_id() {
    return this->_id;
}
std::string user::get_nickname() {
    return this->_nickname;
}
std::vector<std::pair<userspace::users_anime, anime*>> user::get_anime_list() {
    return this->_anime_list;
}
////////////////////////

// Setters
void user::set_id(const ull& id) {
    this->_id = id;
}
void user::set_nickname(const std::string& nickname) {
    this->_nickname = nickname;
}

void user::set_anime_list(std::vector<anime>& list_of_anime) { // return const later

    std::uniform_int_distribution<std::size_t> number_of_titles (1, 10);
    int tmp_bound = number_of_titles(random_device);

    userspace::users_anime tmp_user_anime;
    for (int i = 0; i < tmp_bound; ++i) {
        tmp_user_anime = select_anime(list_of_anime);
        int j = 0;
        //check if the new title is new and unique
        while (j < this->_anime_list.size() && tmp_user_anime.get_anime().get_title_name() != this->_anime_list.at(j).first.get_anime().get_title_name()) {
            ++j;
        }
        if (j == this->_anime_list.size() || this->_anime_list.size() == 0) {
            std::vector<anime>::iterator iter = std::find(list_of_anime.begin(), list_of_anime.end(), tmp_user_anime.get_anime());
            this->_anime_list.push_back(std::make_pair(tmp_user_anime, &(*iter)));
        }
    }

}
///////////////////////

user::~user()
{

}

///////////////////////////////////////// END of "user" class

/// Help functions for "createMultipleUsers" function

user createUser() {
    user tmp_user;
    tmp_user.set_id(global_id++);
    tmp_user.set_nickname( nng::instance().get_nickname() );
    return tmp_user;
}

void createMultipleUsers(const int& number_of_users, std::map<std::string, user>& unique_users, std::vector<anime>& anime_list) { //set start values here, now it's hard for me
    user tmp_user;
    for (int i = 0; i < number_of_users; ++i) {

        // Logicaly first I prepare list of users, and then they are watching and adding their data to profiles, so that's why I don't insert "set_anime_list" inside "createUser"
        tmp_user = createUser();
        tmp_user.set_anime_list(anime_list);
        unique_users[tmp_user.get_nickname()] = tmp_user;

    }
}

// help functions

std::string generateDate(const int& _year_lower_bound = 1970) {
    std::string date;
    int day, month, year;
    month = std::uniform_int_distribution<std::size_t> (1, 12)(random_device);
    switch (month) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12: day = std::uniform_int_distribution<std::size_t> (1, 31)(random_device); break;
    default : day = std::uniform_int_distribution<std::size_t> (1, 30)(random_device);
    }
    year = std::uniform_int_distribution<std::size_t> (_year_lower_bound, _year_lower_bound + 10)(random_device);
    std::stringstream tmp_stream;
    tmp_stream << std::setw(2) << std::setfill('0') << day << "/" << std::setw(2) << std::setfill('0') << month << "/" << std::setw(4) << year;
    std::getline(tmp_stream, date);
    return date;
}

int getStartYear(const std::string& _year) {
    std::stringstream tmp_stream(_year);
    std::string tmp_string;
    while (std::getline(tmp_stream, tmp_string, ' '));
    return std::stoi(tmp_string);
}

int getFinishYear(const std::string& _year) {
    std::stringstream tmp_stream(_year);
    std::string tmp_string;
    while (std::getline(tmp_stream, tmp_string, '/'));
    return std::stoi(tmp_string);
}

userspace::users_anime select_anime(const std::vector<anime>& list_of_anime) {
    std::uniform_int_distribution<std::size_t> number_of_titles{0, list_of_anime.size() - 1};
    anime selected_anime = list_of_anime.at(number_of_titles(random_device));
    userspace::users_anime tmp_user_title;

    tmp_user_title.set_anime(selected_anime);

    tmp_user_title.set_watched_episodes(std::uniform_int_distribution<std::size_t> (1, selected_anime.get_number_of_episodes())(random_device));

    int premierYear = getStartYear(selected_anime.get_premiered());
    tmp_user_title.set_start_date(generateDate(premierYear));

    int finishYear = getFinishYear(tmp_user_title.get_start_date());
    tmp_user_title.set_end_date(generateDate(finishYear));

    tmp_user_title.set_user_score(std::uniform_int_distribution<std::size_t> (1, 10)(random_device));

    return tmp_user_title;
}

