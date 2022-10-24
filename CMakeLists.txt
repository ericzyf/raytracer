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

find_package(OpenGL REQUIRED)
add_subdirectory(third_party/fmt)
add_subdirectory(third_party/glm)
add_subdirectory(third_party/glfw)

add_executable(${PROJECT_NAME}
    third_party/imgui/backends/imgui_impl_glfw.cpp
    third_party/imgui/backends/imgui_impl_opengl3.cpp
    third_party/imgui/imgui.cpp
    third_party/imgui/imgui_demo.cpp
    third_party/imgui/imgui_draw.cpp
    third_party/imgui/imgui_tables.cpp
    third_party/imgui/imgui_widgets.cpp
    #src/main.cpp
    src/imgui_example.cpp
    src/debug.cpp
    src/Rand.cpp
    src/Pixmap.cpp
)
target_include_directories(
    ${PROJECT_NAME} PRIVATE
    include
    third_party/stb/include
    third_party/imgui/backends
    third_party/imgui
)
target_link_libraries(${PROJECT_NAME} fmt OpenGL::GL glm glfw)

