cmake_minimum_required(VERSION 3.10)

project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 11.1.3
)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(
    sdl
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.2.20
)
FetchContent_MakeAvailable(sdl)

set(SDLTTF_VENDORED ON CACHE BOOL "Use vendored libraries" FORCE)

FetchContent_Declare(
        sdl_ttf
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
        GIT_TAG release-3.2.2
)
FetchContent_MakeAvailable(sdl_ttf)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES include/*.hpp)

add_executable(SnakeGame ${SRC_FILES} ${HEADER_FILES})

target_include_directories(SnakeGame PRIVATE include)

target_link_libraries(SnakeGame PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf fmt::fmt)

add_custom_command(TARGET SnakeGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/assets" "$<TARGET_FILE_DIR:SnakeGame>/assets"
)

if (MSVC)
    target_compile_options(SnakeGame PRIVATE /W4)
endif()
