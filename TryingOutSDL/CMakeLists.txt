cmake_minimum_required(VERSION 3.31)
project(TryingOutSDL)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_ttf REQUIRED CONFIG)

add_executable(TryingOutSDL
        main.cpp)

target_link_libraries(TryingOutSDL PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf)