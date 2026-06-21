cmake_minimum_required(VERSION 3.28)
project(MandelbrotSFML LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(mandelbrot src/mandelbrot.cpp)
target_compile_features(mandelbrot PRIVATE cxx_std_17)
target_link_libraries(mandelbrot PRIVATE SFML::Graphics)

# Statically link MinGW runtime libraries for portable binary
if(MINGW)
    target_link_options(mandelbrot PRIVATE -static-libstdc++ -static-libgcc)
endif()

# Install target and create distributable package
install(TARGETS mandelbrot DESTINATION bin)
install(FILES LICENSE.md README.md DESTINATION . OPTIONAL)
