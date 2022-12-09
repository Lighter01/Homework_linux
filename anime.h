#ifndef ANIME_H
#define ANIME_H

#include <string>
#include <vector>

typedef unsigned long long ull;

class anime
{
private: // I know, I know      // columns number in source file.csv
    ull _id;                    // 0
    std::string _title_name;   // 1
    std::string _genre;        // 28
    int _number_of_episodes;    // 8
    ull _rank;                  // 17
    std::string _rating;       // 14
    std::string _premiered;    // 22
    std::string _aired;        // 12
    std::string _studio;       // 27
    std::string _producer;     // 25
    std::string _licensor;     // 26
    //ull, std::wstring, std::wstring, int, ull, std::wstring, std::wstring, std::wstring, std::wstring, std::wstring, std::wstring

public:
    ull get_id();
    std::string get_title_name();
    std::string get_genre();
    int          get_number_of_episodes();
    ull          get_rank();
    std::string get_rating();
    std::string get_premiered();
    std::string get_aired();
    std::string get_studio();
    std::string get_producer();
    std::string get_licensor();

    void set_id(const ull&);
    void set_title_name(const std::string&);
    void set_genre(const std::string&);
    void set_number_of_episodes(const int&);
    void set_rank(const ull&);
    void set_rating(const std::string&);
    void set_premiered(const std::string&);
    void set_aired(const std::string&);
    void set_studio(const std::string&);
    void set_producer(const std::string&);
    void set_licensor(const std::string&);

    bool operator== (const anime& );

    anime();
    anime(const ull&, const std::string&, const std::string&, const int&,
          const ull&, const std::string&, const std::string&, const std::string&,
          const std::string&, const std::string&, const std::string&);
    ~anime();
};

#endif // ANIME_H
