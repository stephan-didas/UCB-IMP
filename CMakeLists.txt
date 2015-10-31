###
#   Preamble and project configuration
###

# Setting project name
cmake_minimum_required(VERSION 3.3)
set(PROJECT_NAME UCBImp)
project(${PROJECT_NAME})

# Add c++11 flag to found compiler
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Move created executables and shared libraries to respective dirs in out-folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${UCBImp_SOURCE_DIR}/out/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${UCBImp_SOURCE_DIR}/out/lib)



###
#   Adding subdirectories to cmake
#
#   Adding src directory, providing test target
###

# Add source directory
add_subdirectory(${UCBImp_SOURCE_DIR}/src)

# Provides target for unit testing
#
# This part defines a flag "test" to activate testing capabilities.
# The default value is ON.
option(test "Build all tests." ON)
if (test)

    # Enable cmake-test
    enable_testing()

    # Adding googletest to cmake
    add_subdirectory(${UCBImp_SOURCE_DIR}/third-party/googletest/googletest)

    # Adding directory for tests
    add_subdirectory(test)

endif()