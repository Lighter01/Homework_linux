#ifndef TIE_H
#define TIE_H

#include <array>
#include <vector>
#include <iostream>

namespace tie {

    template <typename T, std::size_t N> struct array_{
      std::array<T, N> inner_array;
    };

}

#endif // TIE_H
