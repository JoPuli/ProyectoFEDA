cmake_minimum_required(VERSION 3.10)

project(TwitterPoliticalAnalysis)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB SOURCES
    "src/*.cpp"
    "src/data/*.cpp"
    "src/analysis/*.cpp"
    "src/algorithms/*.cpp"
    "src/structures/*.cpp"
)

add_executable(TwitterPoliticalAnalysis ${SOURCES})