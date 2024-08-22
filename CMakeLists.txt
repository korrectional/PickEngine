cmake_minimum_required(VERSION 3.0.0)
project(PickEngine)

set(SourceFiles
    main.cpp
    )

set(IMGUI_SOURCES
    
    imgui-master/imconfig.h
    imgui-master/imgui_demo.cpp
    imgui-master/imgui_draw.cpp
    imgui-master/imgui_impl_opengl3_loader.h
    imgui-master/imgui_impl_opengl3.cpp
    imgui-master/imgui_impl_opengl3.h
    imgui-master/imgui_impl_sdl2.cpp
    imgui-master/imgui_impl_sdl2.h
    imgui-master/imgui_internal.h
    imgui-master/imgui_tables.cpp
    imgui-master/imgui_widgets.cpp
    imgui-master/imgui.cpp
    imgui-master/imgui.h
    imgui-master/imstb_rectpack.h
    imgui-master/imstb_textedit.h
    imgui-master/imstb_truetype.h
    imgui-master/LICENSE.txt
)

find_package(SDL2 REQUIRED)
find_package(assimp REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${ASSIMP_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SourceFiles} ${IMGUI_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE imgui)  # Include the IMGUI headers

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${ASSIMP_LIBRARIES})