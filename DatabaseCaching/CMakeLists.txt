set(PROJECT_SOURCES 
    Main.cpp
)

set(P_NAME DatabaseCaching)

add_executable(${P_NAME})

target_sources(${P_NAME}
    PRIVATE ${PROJECT_SOURCES})

target_include_directories(${P_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
