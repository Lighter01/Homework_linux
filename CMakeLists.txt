cmake_minimum_required(VERSION 3.5)

project(SFML_Game_of_life LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SFML_Game_of_life main.cpp display_grid.h defines.h preparation_parameters.h Events.h)

set(SFML_DIR "F:\\C++_libs\\SFML\\SFML-2.5.1\\lib\\cmake\\SFML")

target_link_libraries(SFML_Game_of_life sfml-graphics)
target_link_libraries(SFML_Game_of_life sfml-window)
target_link_libraries(SFML_Game_of_life sfml-system)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5.1 REQUIRED graphics network audio window system)

install(TARGETS SFML_Game_of_life
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
