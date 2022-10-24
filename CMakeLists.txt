cmake_minimum_required(VERSION 3.18)

project(rtx)
set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -pedantic)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-march=native)
endif()

if(UNIX)
    add_link_options(-rdynamic)
endif()

add_subdirectory(third_party/fmt)
add_subdirectory(third_party/glm)
add_subdirectory(third_party/glfw)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/debug.cpp
    src/Rand.cpp
    src/Pixmap.cpp
)
target_include_directories(
    ${PROJECT_NAME} PRIVATE
    include
    third_party/stb/include
)
target_link_libraries(${PROJECT_NAME} fmt glm glfw)

