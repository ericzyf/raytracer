message("Fetching glm...")

include(FetchContent)

FetchContent_Declare(
    glm
    URL      https://github.com/g-truc/glm/archive/refs/tags/0.9.9.8.zip
    URL_HASH MD5=a421a37d1896ab74765c3f94431ca0f6
)

FetchContent_MakeAvailable(glm)

