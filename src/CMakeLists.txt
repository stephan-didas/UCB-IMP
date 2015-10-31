##
#   Adding source code and definition for library
##


# Adding needed header files
include_directories(
    ${UCBImp_SOURCE_DIR}/include                # Our internal header files
    ${UCBImp_SOURCE_DIR}/src/internal_headers   # Our public header files (API)
)

# Collecting sources for library recursively
file (GLOB_RECURSE libucbimp_sources ${UCBImp_SOURCE_DIR}/src *.cpp)

# Create library libucbimp
add_library(ucbimp SHARED ${libucbimp_sources})