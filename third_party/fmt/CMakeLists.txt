message("Fetching fmt...")

include(FetchContent)

FetchContent_Declare(
    fmt
    URL      https://github.com/fmtlib/fmt/archive/refs/tags/9.1.0.zip
    URL_HASH MD5=e6754011ff56bfc37631fcc90961e377
)

FetchContent_MakeAvailable(fmt)

