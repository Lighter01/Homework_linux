cmake_minimum_required(VERSION 3.5)

project(homework_7 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

add_executable(homework_7 main.cpp account.h account.cpp)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/list_of_shells.txt
#      DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

install(TARGETS homework_7
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
