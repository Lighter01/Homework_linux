#ifndef FORMAT_H
#define FORMAT_H

#include <iostream>
#include <string>
#include <regex>
#include <cstddef>
#include <iomanip>

namespace impl
{
    template <class T>
    std::string to_str(const T &val)
    {
//        std::cout << "1\n";
        return std::to_string(val);
    }

    inline std::string to_str(const char *p)
    {
//        std::cout << "2\n";
        return p;
    }

    inline const std::string& to_str(const std::string &s)
    {
//        std::cout << "3\n";
        return s;
    }

    inline std::string to_str(const char p)
    {
//        std::cout << "4\n";
        std::string tmp{p};
        return tmp;
    }

    inline std::string to_str(const double p)
    {
//        std::cout << "5\n";
        std::string tmp{std::to_string(static_cast<int>(p))};
        return tmp;
    }
}

template <class... Params>
std::string format(std::string model, const Params&... params)
{
    using std::string, std::regex, std::smatch;
    // Конвертировать params в массив строк.
    string param[] { "", impl::to_str(params)... };

    // Выполнить подстановку (конечный автомат через std::regex).
    string result;

    regex preg("%");
    smatch match;
    size_t i = 1;
    while (regex_search(model, match, preg))
    {
        result += match.prefix();

        if (match.size() != 0) {
            if (i < sizeof(param)/sizeof(param[0])) {
                result += param[i++];
            } else {
                result += " ";
            }
        } else {
            result += " ";
        }

        model = match.suffix();
    }

    result += match.suffix();
    return result;
}

template <class... Params>
void message(std::ostream &os, std::string model, const Params&... params) {
    os << format(model, params...);
}

template <class... Params>
void message(std::string model, const Params&... params) {
    std::cout << format(model, params...);
}

#endif // FORMAT_H
