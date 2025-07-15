cmake_minimum_required(VERSION 3.10)

project(TwitterPoliticalAnalysis)

set(CMAKE_CXX_STANDARD 17)

# Recursively find all .cpp files in the project
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp" 
    "${PROJECT_SOURCE_DIR}/src/**/*.cpp")

# Add include directory for header files
include_directories(${PROJECT_SOURCE_DIR}/src/include)

add_executable(TwitterPoliticalAnalysis ${SOURCES})