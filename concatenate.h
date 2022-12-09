#ifndef CONCATENATE_H
#define CONCATENATE_H

#include <array>
#include <algorithm>

template <typename T, std::size_t... N>
std::array<T, (N + ...)> cat(const std::array<T, N>&... arrays) {
    std::array<T, (N + ...)> result;
    std::size_t index{};

    ((std::copy_n(arrays.begin(), N, result.begin() + index), index += N), ...);

    return result;
}

//template<typename T, std::size_t N, std::size_t M>
//auto cat(std::array<T, N>& arr1, std::array<T,M>& arr2)
//{
//    std::array<T, N+M> arr;
//    for (int i = 0; i < N + M; ++i) {
//        if (i < arr1.size()) {
//            arr.at(i) = arr1.at(i);
//        }
//        else {
//            arr.at(i) = arr2.at(i - arr1.size());
//        }
//    }
//    return arr;
//}


//template<typename T, std::size_t N, typename... Args>
//auto cat(std::array<T, N>& arr1, Args&... args)
//{
//    auto arr2 = cat(args...);
//    auto arr  = cat(arr1, arr2);
//    return arr;
//}


#endif // CONCATENATE_H
