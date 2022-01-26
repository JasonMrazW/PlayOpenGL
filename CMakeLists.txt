cmake_minimum_required(VERSION 3.20)
project(playOpenGL)

# glfw和glew的头文件目录，这是我的路径，你可以换成你自己的
include_directories(/usr/local/include)
include_directories(include/)
aux_source_directory("./" SRCS)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "-g -std=c++11 -Wformat")

if (CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "arm64")
    # glew的库目录路径
    include_directories(/opt/homebrew/Cellar/glew/2.2.0_1/include/)
    link_directories(/opt/homebrew/Cellar/glew/2.2.0_1/lib)
    # glfw的库目录路径
    include_directories(/opt/homebrew/Cellar/glfw/3.3.4/include/)
    link_directories(/opt/homebrew/Cellar/glfw/3.3.4/lib)
endif ()

if (CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64")
    # glew的库目录路径
    include_directories(/usr/local/Cellar/glew/2.2.0_1/include/)
    link_directories(/usr/local/Cellar/glew/2.2.0_1/lib)
    # glfw的库目录路径
    include_directories(/usr/local/Cellar/glfw/3.3.6/include/)
    link_directories(/usr/local/Cellar/glfw/3.3.6/lib)
endif ()

add_executable(playOpenGL main.cpp glad.c shader_render.cpp triangle.cpp headers/triangle.h headers/GLUtils.h headers/shader_render.h headers/IRender.h headers/shader.h shader.cpp texture_render.cpp headers/texture_render.h matrix_render.cpp headers/matrix_render.h)

# 指定glew库
target_link_libraries(playOpenGL GLEW)
# 指定glfw库
target_link_libraries(playOpenGL GLFW)
#
file(COPY resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
message("===========CMAKE_cur_ver: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")