add_subdirectory(Parse)
add_subdirectory(Spawn)
add_subdirectory(FileProcess)

set(PROJECT_SOURCES 
    ${PARSE_SOURCES}
    ${SPAWN_SOURCES}
    ${FILE_PROCESS_SOURCES}
    Main.cpp
)

target_sources(${PROJECT_NAME}
    PRIVATE ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
