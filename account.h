#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include <iostream>

namespace acc {
    struct Account {
        unsigned int id;                                    // идентификатор
        std::string login;                                  // логин
        std::string name;                                   // имя
        std::pair<std::string, std::string> shell;          // оболочка
        std::string home_directory;                         // домашняя директория

        Account();
        Account(const unsigned int&, const std::string& ,const std::string& ,const std::pair<std::string, std::string>& ,const std::string& );

        bool operator==(const Account& );
        bool operator()(const Account& , const Account& ) const;
    };

    inline std::vector<Account> database;
    inline std::vector<std::string> namesList;
    inline std::vector<std::pair<std::string, std::string>> shellsList; // full name , short name

    void generateDatabase();

}

//namespace std {
//    template <>
//      struct hash<acc::Account>
//      {
//        std::size_t operator()(const acc::Account& k) const
//        {
//          using std::size_t;
//          using std::hash;
//          using std::string;

//          // Compute individual hash values for first,
//          // second and third and combine them using XOR
//          // and bit shifting:

//          return ((hash<string>()(k.name)
//                   ^ (hash<string>()(k.shell.first) << 1)) >> 1)
//                   ^ (hash<int>()(k.id) << 1);
//        }
//      };
//}



template <class T>
inline void hash_combine(std::size_t & seed, const T & v)
{
    std::hash<T> hasher;
//    std::cout << hasher(v) << " -- ";
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
};

template<typename S, typename T>
struct pair_hash
{
    inline std::size_t operator()(const std::pair<S, T> & v) const
    {
         std::size_t seed = 0;
         hash_combine(seed, v.first);
//         hash_combine(seed, v.second);

//         std::cout << seed << "\n";
         return seed;
    }
};

template<typename S, typename T>
struct pair_equal
{
    inline bool operator()(const std::pair<S,T> & v, const std::pair<S,T> & w) const
    {
        return v.first == w.first;
    }
};


#endif // ACCOUNT_H
