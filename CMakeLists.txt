cmake_minimum_required(VERSION 3.10)

# set the project name
project(sandbox)

# custom cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
link_directories(${CMAKE_SOURCE_DIR}/lib)
list(APPEND CMAKE_CXX_FLAGS "-std=c++11")

# find the required packages
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
find_package(ASSIMP REQUIRED)
message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIR}")
# find_package(SOIL REQUIRED)
# message(STATUS "Found SOIL in ${SOIL_INCLUDE_DIR}")
# find_package(GLEW REQUIRED)
# message(STATUS "Found GLEW in ${GLEW_INCLUDE_DIR}")


if(UNIX)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
    if(POLICY CMP0072)
        cmake_policy(SET CMP0072 NEW)
    endif()
    find_package(OpenGL REQUIRED)
    add_definitions(${OPENGL_DEFINITIONS})
    find_package(X11 REQUIRED)
    # note that the order is important for setting the libs
    # use pkg-config --libs $(pkg-config --print-requires --print-requires-private glfw3) in a terminal to confirm
    set(LIBS ${GLFW3_LIBRARY} X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL dl pthread ${ASSIMP_LIBRARY})
    set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
endif(UNIX)

# create relevant static libraries requried for other projects
add_library(STB_IMAGE ${CMAKE_SOURCE_DIR}/src/stb_image.cpp)
set(LIBS ${LIBS} STB_IMAGE)

add_library(GLAD ${CMAKE_SOURCE_DIR}/src/glad.cpp)
set(LIBS ${LIBS} GLAD)

# main executable
file(GLOB SOURCE 
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/shaders/*.vs
    ${CMAKE_SOURCE_DIR}/src/shaders/*.fs
    ${CMAKE_SOURCE_DIR}/src/shaders/*.gs
)
add_executable(sandbox ${SOURCE})
#target_link_libraries(sandbox OpenGL::GL)
target_link_libraries(sandbox ${LIBS})
set_target_properties(sandbox PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
# copy shader files to build directory
file(GLOB SHADERS
    ${CMAKE_SOURCE_DIR}/src/shaders/*.vs
    ${CMAKE_SOURCE_DIR}/src/shaders/*.fs
    ${CMAKE_SOURCE_DIR}/src/shaders/*.gs
)
foreach(SHADER ${SHADERS})
    file(COPY ${SHADER} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)
endforeach(SHADER)









# include directories 
include_directories(sandbox ${CMAKE_SOURCE_DIR}/include)