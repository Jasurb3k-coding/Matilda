cmake_minimum_required(VERSION 3.27)
project(Matilda)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt
        GIT_TAG         10.2.1
)

FetchContent_MakeAvailable(fmt)


add_executable(Matilda main.cpp
        src/argument_parser.cpp
        src/argument_parser.h
        src/core.cpp
        src/core.h
        src/exceptions.cpp
        src/exceptions.h
        src/utils.h
        src/utils.cpp
        src/stenographers/bmp.cpp
        src/stenographers/bmp.h
        src/stenographers/base.cpp
        src/stenographers/base.h
        src/stenographers/ppm.h
        src/stenographers/ppm.cpp
)
target_link_libraries(Matilda fmt)
