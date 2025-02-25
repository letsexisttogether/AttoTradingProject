set(PROJECT_SOURCES
    Standartize/FileStandartizer.cpp
    Main.cpp)

target_sources(${PROJECT_NAME}
    PRIVATE ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} 
    PRIVATE ${CMAKE_CURRENT_DIR})
