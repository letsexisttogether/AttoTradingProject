add_subdirectory(Parse)
add_subdirectory(Spawn)
add_subdirectory(Sort)
add_subdirectory(FileProcess)

set(PROJECT_SOURCES 
    ${PARSE_SOURCES}
    ${SPAWN_SOURCES}
    ${SORT_SOURCES}
    ${FILE_PROCESS_SOURCES}
    Main.cpp
)

set(P_NAME ExternalSorting)

add_executable(${P_NAME})

target_sources(${P_NAME}
    PRIVATE ${PROJECT_SOURCES})

target_include_directories(${P_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
