# CMakeLists.txt
# This file is used to build the sim_queue project using CMake.

cmake_minimum_required (VERSION 3.5...3.10) # Specify the minimum required version of CMake

project(sim_queue) # Define the project name

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Ensure the C++ standard is enforced
set(CMAKE_CXX_EXTENSIONS OFF) # Disable compiler-specific extensions
# Add the include directories for the project
add_subdirectory(simlib) # Include the simlib directory for the String class
add_subdirectory(simlib_bin) # Include the simlib_bin directory for the main application