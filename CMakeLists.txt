cmake_minimum_required(VERSION 3.27)
project(Peeps_OOP_Demo VERSION 2.0.0 LANGUAGES CXX)

option(PEEPS_BUILD_TESTS "Build the Peeps-OOP-Demo tests" ON)

# The reusable core: everything except main() lives here, so tests can
# link it without the console program.
add_library(peeps_core
    src/App.cpp
    src/InputUtils.cpp
    src/Student.cpp
    src/Teacher.cpp
)
target_include_directories(peeps_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(peeps_core PUBLIC cxx_std_17)

# Warnings on, but not -Werror in the default build: a warning on some
# other compiler should not block someone just trying the demo.
if(MSVC)
    target_compile_options(peeps_core PRIVATE /W4)
else()
    target_compile_options(peeps_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(Peeps_OOP_Demo
    src/main.cpp
)
target_link_libraries(Peeps_OOP_Demo PRIVATE peeps_core)
if(MSVC)
    target_compile_options(Peeps_OOP_Demo PRIVATE /W4)
else()
    target_compile_options(Peeps_OOP_Demo PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(PEEPS_BUILD_TESTS)
    include(CTest)
    add_executable(peeps_tests tests/test_peeps.cpp)
    target_link_libraries(peeps_tests PRIVATE peeps_core)
    if(MSVC)
        target_compile_options(peeps_tests PRIVATE /W4)
    else()
        target_compile_options(peeps_tests PRIVATE -Wall -Wextra -Wpedantic)
    endif()
    add_test(NAME peeps_tests COMMAND peeps_tests)
endif()

install(TARGETS Peeps_OOP_Demo RUNTIME DESTINATION bin)
