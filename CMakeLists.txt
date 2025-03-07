cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(DEFINED PROJECT_NAME)
    message(STATUS "Selected project: ${PROJECT_NAME}")
else()
    message(FATAL_ERROR "PROJECT_NAME argument must be provided!")
endif()

project(${PROJECT_NAME} VERSION 1 LANGUAGES CXX)

if(${PROJECT_NAME} STREQUAL "ExternalSorting")
    add_subdirectory(ExternalSorting)
elseif(${PROJECT_NAME} STREQUAL "DatabaseCache")
    # add_subdirectory(DatabaseCache)
else()
    message(FATAL_ERROR "Invalid PROJECT_NAME specified: ${PROJECT_NAME}")
endif()
