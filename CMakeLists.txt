cmake_minimum_required(VERSION 3.16)
project(COLONNIE_DE_FOURMIS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)   # noms avec majuscules en SFML 3

add_executable(${PROJECT_NAME}
    main.cpp
    system/display/display.cpp
    system/display/display.hpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/system
    ${CMAKE_CURRENT_SOURCE_DIR}/system/display
)


target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)
