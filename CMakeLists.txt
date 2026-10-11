cmake_minimum_required(VERSION 3.20)
project(Desafio2 LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(Desafio2
    src/main.cpp
    src/udeaBook.cpp
    src/dataManager.cpp
    src/validators.cpp

    src/Album.cpp
    src/Chat.cpp
    src/Date.cpp
    src/Msg.cpp
    src/Photo.cpp
    src/Usr.cpp

    include/udeaBook.hpp
    include/dataManager.hpp
    include/validators.hpp
    include/Album.hpp
    include/Chat.hpp
    include/Date.hpp
    include/Msg.hpp
    include/Photo.hpp
    include/Usr.hpp
)

target_include_directories(Desafio2 PRIVATE include)

if(MSVC)
    target_compile_options(Desafio2 PRIVATE /W4 /permissive-)
else()
    target_compile_options(Desafio2 PRIVATE 
        -Wall 
        -Wextra 
        -Wpedantic 
        -Wconversion
        -Wshadow
    )
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND NOT MSVC)
    target_compile_options(Desafio2 PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(Desafio2 PRIVATE -fsanitize=address,undefined)
endif()
