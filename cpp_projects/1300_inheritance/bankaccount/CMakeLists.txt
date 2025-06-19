project(bankaccount)

# Create the executable
add_executable(${PROJECT_NAME} main.cpp)

# Link the static library from simlib using its alias sub::lib1
# This will cause the include directories for that target to be added to this project
target_link_libraries(${PROJECT_NAME}
    sub::lib1
    sub::lib2
)