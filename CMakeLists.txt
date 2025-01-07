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

#-------------------------------------------- Create Libraries-------------------------------

#-----Library UnitTests----------------

#include_directories(
#    "${CMAKE_SOURCE_DIR}/Tests/Declaration"
#)
#
#file(GLOB
#            UnitTestsSources "${CMAKE_SOURCE_DIR}/Tests/Definition/*.cpp")
#add_library(libUnitTests SHARED ${UnitTestsSources})
#
#-----End UnitTests

#-----Library TypesOfData----------------

include_directories(
    "${CMAKE_SOURCE_DIR}/Declaration/TypesOfData"
)

file(GLOB
            TypesOfDataSources "${CMAKE_SOURCE_DIR}/Definition/TypesOfData/*.cpp")
add_library(libTypesOfData SHARED ${TypesOfDataSources})

#-----End TypesOfData

#-----Library GetHashCodes----------------

include_directories(
    "${CMAKE_SOURCE_DIR}/Declaration/GetHashCodes"
)

file(GLOB
            GetHashCodesSources "${CMAKE_SOURCE_DIR}/Definition/GetHashCodes/*.cpp")
add_library(libGetHashCodes SHARED ${GetHashCodesSources})

#-----End GetHashCodes

#-----Library Functions----------------

include_directories(
    "${CMAKE_SOURCE_DIR}/Declaration/Functions"
)

file(GLOB
    FunctionsSources "${CMAKE_SOURCE_DIR}/Definition/Functions/*.cpp")
add_library(libFunctions SHARED ${FunctionsSources})

#-----End GetHashCodes

add_executable( ${PROJECT_NAME}
${SOURCES}
)


#---------------------------------------------- Link Libraries


#target_link_libraries(${PROJECT_NAME} PRIVATE libUnitTests)

target_link_libraries(${PROJECT_NAME} PRIVATE libTypesOfData)

target_link_libraries(${PROJECT_NAME} PRIVATE libGetHashCodes)

target_link_libraries(${PROJECT_NAME} PRIVATE libFunctions)