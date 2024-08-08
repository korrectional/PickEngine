cmake_minimum_required(VERSION 3.0.0)
project(PickEngine)

set(SourceFiles
    main.cpp
    )

find_package(SDL2 REQUIRED)
find_package(assimp REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${ASSIMP_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SourceFiles})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${ASSIMP_LIBRARIES})