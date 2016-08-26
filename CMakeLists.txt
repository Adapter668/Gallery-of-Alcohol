cmake_minimum_required(VERSION 3.6)
project(Gallery_of_Alcohol)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(PkgConfig REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)
pkg_search_module(GLEW REQUIRED glew)

include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})

set(SOURCE_FILES
        src/camera.cpp
        src/camera.h
        src/constants.h
        src/lodepng.cpp
        src/lodepng.h
        src/main_file.cpp
        src/MeshLoader.cpp
        src/MeshLoader.h
        src/model.cpp
        src/model.h
        src/SceneBuilder.cpp
        src/SceneBuilder.h src/special_effects.cpp src/special_effects.h)

add_executable(Gallery_of_Alcohol ${SOURCE_FILES})

target_link_libraries(Gallery_of_Alcohol ${GLFW_LIBRARIES})
target_link_libraries(Gallery_of_Alcohol ${GLEW_LIBRARIES})