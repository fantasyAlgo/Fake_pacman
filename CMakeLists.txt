# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Project name
project(PacmanGame)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Glob all the source files in the "src" folder
file(GLOB SOURCES "src/*.cpp")

# Create an executable from those source files
add_executable(pacman_game ${SOURCES})
#add_executable(pacman_game src/main.cpp)

# Include the SFML library (assuming you are using SFML)
# Make sure to install SFML or link to its path correctly.
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(pacman_game sfml-system sfml-window sfml-graphics sfml-audio)

# Include headers for helpers (if needed)
include_directories(include)

