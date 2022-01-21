cmake_minimum_required(VERSION 3.20)
project(playOpenGL)

# glfw和glew的头文件目录，这是我的路径，你可以换成你自己的
include_directories(/usr/local/include)
include_directories(include/glad)
aux_source_directory("./" SRCS)


set(CMAKE_CXX_FLAGS "-g -std=c++11 -Wformat")

if (CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "arm64")
    # glew的库目录路径
    include_directories(/opt/homebrew/Cellar/glew/2.2.0_1/include/)
    link_directories(/opt/homebrew/Cellar/glew/2.2.0_1/lib)
    # glfw的库目录路径
    include_directories(/opt/homebrew/Cellar/glfw/3.3.4/include/)
    link_directories(/opt/homebrew/Cellar/glfw/3.3.4/lib)
endif ()

add_executable(playOpenGL main.cpp glad.c)

# 指定glew库
target_link_libraries(playOpenGL GLEW)
# 指定glfw库
target_link_libraries(playOpenGL GLFW)

