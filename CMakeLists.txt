cmake_minimum_required(VERSION 3.20.0)
project(handmade_ray_tracing VERSION 0.1.0 LANGUAGES CXX)

add_executable(handmade_ray_tracing  src/main.cpp)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


if(MSVC)
    target_compile_options(handmade_ray_tracing PRIVATE /W4 /permissive- /utf-8)
endif()