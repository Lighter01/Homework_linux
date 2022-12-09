cmake_minimum_required(VERSION 3.5)

project(datagen_homework LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(datagen_homework main.cpp nicknamegen.h randomname.cpp randomname.h user.cpp user.h anime.cpp anime.h
    data_preparations.cpp data_preparations.h sha256.h sha256.cpp write_file.h write_file.cpp)

install(TARGETS datagen_homework
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
