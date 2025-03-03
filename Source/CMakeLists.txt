add_subdirectory(Parse)
add_subdirectory(Transform)
add_subdirectory(Data)
add_subdirectory(Sort)

set(PROJECT_SOURCES 
    ${TRANSFORM_SOURCES}
    ${PARSE_SOURCES}
    ${DATA_SOURCES}
    ${SORT_SOURCES}
    Main.cpp)

target_sources(${PROJECT_NAME}
    PRIVATE ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
