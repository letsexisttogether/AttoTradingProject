cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(AttoTradingProject VERSION 1 LANGUAGES CXX)

add_subdirectory(ExternalSorting)
add_subdirectory(DatabaseCaching)
