# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set project name and version
project(main VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set compiler
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

# Define build types (if not set by user)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Debug flags
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb -O0 -Wall -Wextra -Wpedantic -Werror -Wno-unused-variable")

# Release flags
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -flto")
# set(CMAKE_CXX_FLAGS_RELEASE "-O3 -flto -march=native -mtune=native -DNDEBUG -Wall -Wextra -Wpedantic -fopenmp")

# Include header files
include_directories(${CMAKE_SOURCE_DIR}/include)

# Gather all source files from ./src
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*/*.cpp")

# Add the main.cpp file to the list of sources
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/main.cpp")

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

#pthread
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)

# Print current build mode
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
