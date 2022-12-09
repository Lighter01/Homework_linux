#include <iostream>
#include <sstream>

#include "format.h"
#include "concatenate.h"
#include "tie.h"

int main()
{
    // Task 1
//    std::cout << format("% + % = %", 'a', 2, 3.0);
    std::stringstream tmp_s;
    message(tmp_s, "% + % = %", 'a', 2, 3.0);
    std::string tmp;
    while (std::getline(tmp_s, tmp)) {
        std::cout << tmp;
    }
    std::cout << '\n';

    // Task 2

    std::array<float,3> vec1{1.0f,2.0f,3.0f};
    std::array<float,3> vec2{4.0f,5.0f,6.0f};
    std::array<float,6> r = cat(vec1, vec2);

    for (auto it : r) {
        std::cout << it << ", ";
    }
    std::cout << '\n';

    // Task 3

//    std::array<float, 6> r_1{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
//    std::array<float, 3> vec_1, vec_2;
//    tie::tie(vec1, vec2);

    return 0;
}
