cmake_minimum_required(VERSION 3.17)
project(breakout_clone)

# CMake standard
set(CMAKE_CXX_STANDARD 20)

# GLM
include_directories(libs/glm)
#add_subdirectory(libs/glm)

# Create executable file
add_executable(breakout_clone main.cpp game.cpp game.h shader.cpp shader.h texture.cpp texture.h)

