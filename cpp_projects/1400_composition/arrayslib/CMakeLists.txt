# Set the project name
project (arrayslib)

# Add a library with the above sources
add_library(${PROJECT_NAME} src/arraydb.cpp)
add_library(sub::lib1 ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
