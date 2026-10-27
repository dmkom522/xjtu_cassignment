cmake_minimum_required(VERSION 3.20)
project(finals_survival LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(game_core STATIC
    src/game.cpp
    src/state.cpp
    src/actions_basic.cpp
    src/actions_extra.cpp
    src/shop.cpp
    src/events.cpp
    src/endings.cpp
    src/ui.cpp
)
target_include_directories(game_core PUBLIC include)

if(MSVC)
    target_compile_options(game_core PUBLIC /W4 /utf-8)
else()
    target_compile_options(game_core PUBLIC -Wall -Wextra -Wpedantic)
endif()

add_executable(finals_survival src/main.cpp)
target_link_libraries(finals_survival PRIVATE game_core)

include(CTest)
if(BUILD_TESTING)
    # Keep the test main separate from src/main.cpp.
    add_executable(skeleton_tests tests/smoke_tests.cpp)
    target_link_libraries(skeleton_tests PRIVATE game_core)
    add_test(NAME skeleton_input_smoke COMMAND skeleton_tests)
    set_tests_properties(skeleton_input_smoke PROPERTIES TIMEOUT 10)
endif()
