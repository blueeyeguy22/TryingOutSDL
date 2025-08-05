cmake_minimum_required(VERSION 3.31)
project(TryingOutSDL)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_ttf REQUIRED CONFIG)

add_executable(TryingOutSDL
        main.cpp
        Window.cpp
        Window.h
        GUI.h
        CharacterTable.h
)

add_custom_command(TARGET TryingOutSDL POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/LucidaSansRegular.ttf
        $<TARGET_FILE_DIR:TryingOutSDL>/LucidaSansRegular.ttf
)

target_link_libraries(TryingOutSDL PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf)