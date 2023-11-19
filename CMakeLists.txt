cmake_minimum_required(VERSION 3.25)
project(TextInvaders)

set(CMAKE_CXX_STANDARD 17)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})



add_executable(TextInvaders
        TextInvaders.cpp
        TextInvaders.h
        CursesUtils.cpp
        CursesUtils.h
        )

target_link_libraries(TextInvaders ${CURSES_LIBRARIES})
