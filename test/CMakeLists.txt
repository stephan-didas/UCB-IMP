## Copyright (c) 2015, Patrick Scheid, Axel Ohlmann, Stephan Didas

##
#   Adding unit tests created with googletest framework
##

# Adding needed header files
include_directories(
    ${gtest_SOURCE_DIR}/include                     # Include files from googletest
    ${UCBImp_SOURCE_DIR}/src/internal_headers       # Our internal header files
    ${UCBImp_SOURCE_DIR}/include                    # Our public header files (API)
)

# Collect all unit test source-files recursively
file (GLOB_RECURSE test_sources ${UCBImp_SOURCE_DIR}/test/ *.cpp)

# Compile a googletest test runner named "testrunner"
add_executable(testrunner ${test_sources})
target_link_libraries(testrunner gtest_main ucbimp)

# Make sure ucbimp library is build befor create testrunner
add_dependencies(testrunner ucbimp)



# Adding googletest testrunner as one test to ctest
# This enables the usage of 'ctest' or 'make test'
add_test(NAME runningTests COMMAND testrunner)

# Create 'gtesting' target
#
# Since ctest uses its own output, the more verbose output from googletest is masked.
# To provide a more convinient way to start testrunner executable an additional target 'gtesting'
# is defined. This target does nothing else than start the mentioned testrunner executable.
add_custom_target(gtesting COMMAND ${UCBImp_SOURCE_DIR}/out/bin/testrunner)
add_dependencies(gtesting testrunner)