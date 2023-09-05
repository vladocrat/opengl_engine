cmake_minimum_required(VERSION 3.5)

project(opengl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GLFW ${CMAKE_CURRENT_SOURCE_DIR}/glfw)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(GLAD ${CMAKE_CURRENT_SOURCE_DIR}/glad)

#so shaders work
file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/textures DESTINATION ${CMAKE_BINARY_DIR})

include_directories(${GLFW}/include)
include_directories(utils)
include_directories(glm)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(OpenGL REQUIRED)

message(${GLAD}/glad.c)

add_executable(opengl main.cpp
window.h window.cpp
shader.h shader.cpp
engine.h engine.cpp
program.h program.cpp
texture.h texture.cpp
image.h
opengl.h
stb_image.h
utils/pimpl.h
utils/utils.h utils/utils.cpp
${GLAD}/khrplatform.h
${GLAD}/glad.h ${GLAD}/glad.cpp)

target_link_libraries(opengl ${GLFW}/lib/glfw3.lib ${OPENGL_gl_LIBRARY})

install(TARGETS opengl
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
