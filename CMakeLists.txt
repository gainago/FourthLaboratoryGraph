cmake_minimum_required(VERSION 3.5)

project(Graph VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB
            SOURCES "${PROJECT_SOURCE_DIR}/Definition/*.cpp")
include_directories(
    "${CMAKE_SOURCE_DIR}/Declaration/Dictionary"
    "${CMAKE_SOURCE_DIR}/Declaration/Functions"
    "${CMAKE_SOURCE_DIR}/Declaration/GetHashCodes"
    "${CMAKE_SOURCE_DIR}/Declaration/Graph"
    "${CMAKE_SOURCE_DIR}/Declaration/Sequence"
    "${CMAKE_SOURCE_DIR}/Declaration/SmartPointers"
    "${CMAKE_SOURCE_DIR}/Declaration/TypesOfData"
)

add_executable( ${PROJECT_NAME}
${SOURCES}
)