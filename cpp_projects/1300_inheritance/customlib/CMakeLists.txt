# Set the project name
project (customlib)

# Add a library with the above sources
add_library(${PROJECT_NAME} src/overdraft.cpp)
add_library(sub::lib2 ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    sub::lib1
)