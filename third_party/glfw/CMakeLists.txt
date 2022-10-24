message("Fetching glfw...")

include(FetchContent)

set(GLFW_BUILD_EXAMPLES FALSE)
set(GLFW_BUILD_TESTS FALSE)
set(GLFW_BUILD_DOCS FALSE)
set(GLFW_INSTALL FALSE)

FetchContent_Declare(
    glfw
    URL      https://github.com/glfw/glfw/archive/refs/tags/3.3.8.zip
    URL_HASH MD5=b06789a44e82a8a3ebd2e0301fb0484a
)

FetchContent_MakeAvailable(glfw)

