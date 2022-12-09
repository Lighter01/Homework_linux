#ifndef USER_H
#define USER_H

#include <map>
#include "anime.h"

static ull global_id = 0;

namespace userspace {

    class users_anime
    {
    private:
        anime        _anime;
        int          _watched_episodes;
        std::string _start_date;
        std::string _end_date;
        int          _user_score;
    public:
        anime        get_anime();
        int          get_watched_episodes();
        std::string get_start_date();
        std::string get_end_date();
        int          get_user_score();

        void set_anime(const anime& );
        void set_watched_episodes(const int& );
        void set_start_date(const std::string& );
        void set_end_date(const std::string& );
        void set_user_score(const int& );

        bool operator== (const users_anime& );

        users_anime();
        ~users_anime();
    };
}

class user
{
private: // yeah, I know, I know
    ull _id;
    std::string _nickname;
    std::vector<std::pair<userspace::users_anime, anime*>> _anime_list;

public:
    user();

    ull get_id();
    std::string get_nickname();
    std::vector<std::pair<userspace::users_anime, anime*>> get_anime_list();

    void set_id(const ull& );
    void set_nickname(const std::string& );
    void set_anime_list(std::vector<anime>& );

    ~user();
};

user createUser();
void createMultipleUsers(const int& , std::map<std::string, user>& , std::vector<anime>& );

userspace::users_anime select_anime(const std::vector<anime>& );
//look at setter

#endif // USER_H
