cmake_minimum_required(VERSION 3.18)

# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24:
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif()

project(rtx)
set(CMAKE_CXX_STANDARD 17)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-march=native)
endif()

if(UNIX)
    add_link_options(-rdynamic)
endif()

find_package(OpenGL REQUIRED)
add_subdirectory(third_party/fmt)
add_subdirectory(third_party/glm)
add_subdirectory(third_party/glfw)
add_subdirectory(third_party/glad)

add_executable(${PROJECT_NAME}
    third_party/imgui/backends/imgui_impl_glfw.cpp
    third_party/imgui/backends/imgui_impl_opengl3.cpp
    third_party/imgui/imgui.cpp
    third_party/imgui/imgui_demo.cpp
    third_party/imgui/imgui_draw.cpp
    third_party/imgui/imgui_tables.cpp
    third_party/imgui/imgui_widgets.cpp
    src/main.cpp
    #src/imgui_example.cpp
    src/debug.cpp
    src/Rand.cpp
    src/Pixmap.cpp
    src/Hittable.cpp
    src/Sphere.cpp
    src/rtweekend.cpp
    src/Camera.cpp
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -pedantic)

target_include_directories(
    ${PROJECT_NAME} PRIVATE
    include
    third_party/stb/include
    third_party/imgui/backends
    third_party/imgui
)

target_link_libraries(${PROJECT_NAME} fmt OpenGL::GL glm glfw glad)

