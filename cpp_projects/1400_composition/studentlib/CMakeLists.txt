# Set the project name
project (studentlib)

# Add a library with the above sources
add_library(${PROJECT_NAME} src/student.cpp)
add_library(sub::lib2 ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    sub::lib1
)