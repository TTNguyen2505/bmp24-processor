cmake_minimum_required(VERSION 4.0)

project(bmp24-processor VERSION 1.0.0 LANGUAGES CXX)

if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(WARNING "This project is configured for G++. Current compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PROJECT_SOURCES
    src/main.cpp
    src/app/cli_parser.cpp
    src/app/pipeline.cpp
    src/core/color.cpp
    src/core/color_filter.cpp
    src/core/image.cpp
    src/core/transform.cpp
    src/io/bmp24.cpp
    src/io/bmp_io.cpp
    src/io/file_system.cpp
    src/math/geometry.cpp
    src/math/interpolation.cpp
    src/math/matrix.cpp
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
