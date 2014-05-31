cmake_minimum_required(VERSION 2.8)

# define the name of the project. here "transfert"
project(hellogl)

add_subdirectory(src)
add_subdirectory(tests)

file(COPY models DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
