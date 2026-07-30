cmake_minimum_required(VERSION 4.0)

project(bmp24-processor VERSION 1.0.0 LANGUAGES CXX)

if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(WARNING "This project is configured for G++. Current compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PROJECT_SOURCES
    src/bmp_io.cpp
    src/bmp24.cpp
    src/cli_parser.cpp
    src/color_filter.cpp
    src/color.cpp
    src/coordinate.cpp
    src/file_system.cpp
    src/geometry.cpp
    src/image.cpp
    src/interpolation.cpp
    src/main.cpp
    src/matrix.cpp
    src/pipeline.cpp
    src/transform.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME}
        PRIVATE
            -Wall
            -Wextra
            -Wpedantic
    )
endif()
