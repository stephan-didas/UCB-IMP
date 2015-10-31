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

# Add third-party modules and cmake scripts to cmake module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/scripts")



###
#   Adding subdirectories to cmake
#
#   Adding src directory, providing test- and doc-target
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

# Provides target for documentary generation with doxygen
#
# This part defines a flag "doc" to activate documentary generation.
# The default value is ON. If generated, the documentary is stored in doc/.
option(doc  "Generate documentation with documentation." ON)
if (doc)

    # Finding doxygen on current system
    # @TODO: Implement Workaround for Windows
    # @TODO: Remove REQUIRED since not really neccessary for compilation
    find_package(Doxygen REQUIRED)

    if(DOXYGEN_FOUND)
        # Adding target for generating doxygen documentation
        add_custom_target(
                doc
                ${DOXYGEN_EXECUTABLE}
                ${UCBImp_SOURCE_DIR}/conf/Doxyfile
                COMMENT "Generating API documentation with Doxygen" VERBATIM
        )
    endif()

endif()

# Update version in doxyfile if doxygen was found
if (DOXYGEN_FOUND)
    configure_file("${UCBImp_SOURCE_DIR}/cmake/infiles/Doxyfile.in" "${UCBImp_SOURCE_DIR}/conf/Doxyfile")
endif()



###
#   Reading out version from git tag
#
#   Readout git version, provide them as variables and update project files.
###

# Reading version information from git and save it in cmake variables
include(GetVersionInformation)

# Update VERSION file with new version
file(WRITE ${UCBImp_SOURCES_DIR}VERSION "${VERSION_SHORT}")

# Update version.h header file
configure_file(
        "${UCBImp_SOURCE_DIR}/cmake/infiles/version.h.in"
        "${UCBImp_SOURCE_DIR}/include/version.h"
)
