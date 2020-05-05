cmake_minimum_required(VERSION 3.10)

# set the project name
project(sandbox)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# main executable
add_executable(sandbox src/sandbox.cpp src/glad.cpp)

# include directories 
include_directories(sandbox include)

# glfw and opengl
find_package(glfw3 3.3 REQUIRED)
target_link_libraries(sandbox glfw)

if(POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif()

find_package(OpenGL QUIET REQUIRED)
target_link_libraries(sandbox OpenGL::GL)

