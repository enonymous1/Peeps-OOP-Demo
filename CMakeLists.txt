cmake_minimum_required(VERSION 3.27)
project(Peeps_OOP_Demo VERSION 2.0.0 LANGUAGES CXX)

option(PEEPS_BUILD_TESTS "Build the Peeps-OOP-Demo tests" ON)

# Warnings on, but not -Werror in the default build: a warning on some
# other compiler should not block someone just trying the demo.
function(peeps_add_warnings target)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endfunction()

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
peeps_add_warnings(peeps_core)

add_executable(Peeps_OOP_Demo
    src/main.cpp
)
target_link_libraries(Peeps_OOP_Demo PRIVATE peeps_core)
peeps_add_warnings(Peeps_OOP_Demo)

if(PEEPS_BUILD_TESTS)
    include(CTest)
    add_executable(peeps_tests tests/test_peeps.cpp)
    target_link_libraries(peeps_tests PRIVATE peeps_core)
    peeps_add_warnings(peeps_tests)
    add_test(NAME peeps_tests COMMAND peeps_tests)
endif()

install(TARGETS Peeps_OOP_Demo RUNTIME DESTINATION bin)
