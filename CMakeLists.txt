cmake_minimum_required(VERSION 3.6)
project(GPU)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${GPU_SOURCE_DIR}/cmake")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)


set(SOURCE_FILES main.cpp object.cpp object.h triangle.cpp triangle.h point.cpp point.h matrix.cpp matrix.h screen.h screen.cpp)
add_executable(GPU ${SOURCE_FILES})
include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR})
target_link_libraries(GPU ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES})