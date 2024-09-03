cmake_minimum_required(VERSION 3.0.0)
project(PickEngine)

#include(FetchContent)
#
#FetchContent_Declare(
#    SDL2
#    URL https://github.com/libsdl-org/SDL/archive/refs/tags/release-2.30.6.tar.gz
#)
#FetchContent_MakeAvailable(SDL2)


set(SourceFiles
    main.cpp
    )

set(IMGUI_SOURCES
    
    third-party/imgui-master/imconfig.h
    third-party/imgui-master/imgui_demo.cpp
    third-party/imgui-master/imgui_draw.cpp
    third-party/imgui-master/imgui_impl_opengl3_loader.h
    third-party/imgui-master/imgui_impl_opengl3.cpp
    third-party/imgui-master/imgui_impl_opengl3.h
    third-party/imgui-master/imgui_impl_sdl2.cpp
    third-party/imgui-master/imgui_impl_sdl2.h
    third-party/imgui-master/imgui_internal.h
    third-party/imgui-master/imgui_tables.cpp
    third-party/imgui-master/imgui_widgets.cpp
    third-party/imgui-master/imgui.cpp
    third-party/imgui-master/imgui.h
    third-party/imgui-master/imstb_rectpack.h
    third-party/imgui-master/imstb_textedit.h
    third-party/imgui-master/imstb_truetype.h
    third-party/imgui-master/LICENSE.txt
)



find_package(SDL2 REQUIRED)
find_package(assimp REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${ASSIMP_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SourceFiles} ${IMGUI_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE imgui)  # Include the IMGUI headers

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${ASSIMP_LIBRARIES})