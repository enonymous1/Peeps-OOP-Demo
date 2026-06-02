cmake_minimum_required(VERSION 3.27)
project(Peeps_OOP_Demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Peeps_OOP_Demo
    src/main.cpp
    src/App.cpp
    src/InputUtils.cpp
    src/Base.cpp
    src/Teacher.cpp
    src/Student.cpp
)

target_include_directories(Peeps_OOP_Demo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
