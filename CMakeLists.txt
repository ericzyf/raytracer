cmake_minimum_required(VERSION 3.18)

project(rtx)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -pedantic)
add_subdirectory(third_party/fmt)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} fmt)

