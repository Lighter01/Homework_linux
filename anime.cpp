#include "anime.h"

anime::anime() :
    _id(ULONG_MAX),    _title_name(""), _genre(""), _number_of_episodes(0), _rank(ULONG_MAX),
    _rating(""), _premiered(""),  _aired(""), _studio(""), _producer(""), _licensor("")
{

}

anime::anime(const ull& id, const std::string& title_name, const std::string& genre, const int& number_of_episodes,
             const ull& rank, const std::string& rating, const std::string& premiered, const std::string& aired,
             const std::string& studio, const std::string& producer, const std::string& licensor) :
    _id(id),    _title_name(title_name), _genre(genre), _number_of_episodes(number_of_episodes), _rank(rank),
    _rating(rating), _premiered(premiered),  _aired(aired), _studio(studio), _producer(producer), _licensor(licensor)
{

}

anime::~anime() {};

// GETTERS

ull anime::get_id() {
    return this->_id;
}
std::string anime::get_title_name() {
    return this->_title_name;
}
std::string anime::get_genre() {
    return this->_genre;
}
int anime::get_number_of_episodes() {
    return this->_number_of_episodes;
}
ull anime::get_rank() {
    return this->_rank;
}
std::string anime::get_rating() {
    return this->_rating;
}
std::string anime::get_premiered() {
    return this->_premiered;
}
std::string anime::get_aired() {
    return this->_aired;
}
std::string anime::get_studio() {
    return this->_studio;
}
std::string anime::get_producer() {
    return this->_producer;
}
std::string anime::get_licensor() {
    return this->_licensor;
}

/////////////////////////////////////////


// SETTERS

void anime::set_id(const ull& id) {
    this->_id = id;
}
void anime::set_title_name(const std::string& title_name) {
    this->_title_name = title_name;
}
void anime::set_genre(const std::string& genre) {
    this->_genre = genre;
}
void anime::set_number_of_episodes(const int& number_of_episodes) {
    this->_number_of_episodes = number_of_episodes;
}
void anime::set_rank(const ull& rank) {
    this->_rank = rank;
}
void anime::set_rating(const std::string& rating) {
    this->_rating = rating;
}
void anime::set_premiered(const std::string& premiered) {
    this->_premiered = premiered;
}
void anime::set_aired(const std::string& aired) {
    this->_aired = aired;
}
void anime::set_studio(const std::string& studio) {
    this->_studio = studio;
}
void anime::set_producer(const std::string& producer) {
    this->_producer = producer;
}
void anime::set_licensor(const std::string& licensor) {
    this->_licensor = licensor;
}

//////////////////////////////////////////

//// Overloads

bool anime::operator== (const anime& obj) {
    return (this->_id                 == obj._id &&
            this->_title_name         == obj._title_name &&
            this->_genre              == obj._genre &&
            this->_number_of_episodes == obj._number_of_episodes &&
            this->_rank               == obj._rank &&
            this->_rating             == obj._rating &&
            this->_premiered          == obj._premiered &&
            this->_aired              == obj._aired &&
            this->_studio             == obj._studio &&
            this->_producer           == obj._producer &&
            this->_licensor           == obj._licensor);
}
