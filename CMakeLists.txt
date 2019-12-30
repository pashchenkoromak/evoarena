cmake_minimum_required(VERSION 3.0.0)

project(evoarena)

file(GLOB headers
    "include/*.cpp"
)

file(GLOB sources
    "src/*.cpp"
)

add_library(arena_lib ${headers} ${sources})
target_include_directories(arena_lib PUBLIC include include/Strategy)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} arena_lib)
