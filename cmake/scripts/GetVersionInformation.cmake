# GetVersionInformation.cmake
#
# This script parses the latests git tag (needs to be like v0.0.1), refspec and SHA1 commit hash key.
# It provides the parsed information through several cmake variables
#
# Description:
#
#       VERSION_MAJOR   Major version number
#       VERSION_MINOR   Minor version number
#       VERSION_PATCH   Patch number
#
#       GIT_SHA1        Actual commit number
#       GIT_BRANCH      Actual checked out branch
#
#       VERSION_SHORT   MAJOR.MINOR.PATCH
#       VERSION_LONG    MAJOR.MINOR.PATCH-SHA1
#
#
# Example:
#   v2.10.5 would give MAJOR=2, MINOR=10 and PATCH=5
#
#
# This script uses GetGitRevisionDescription (https://github.com/rpavlik/cmake-modules)
#

# Include GetGitRevisionDescription
include(GetGitRevisionDescription)

# Get information from git
git_describe(VERSION --tags --dirty=-dirty)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)

# Parse strings returned by git with regular expressions
string(REGEX REPLACE "^v([0-9]+)\\..*" "\\1" VERSION_MAJOR "${VERSION}")
string(REGEX REPLACE "^v[0-9]+\\.([0-9]+).*" "\\1" VERSION_MINOR "${VERSION}")
string(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" VERSION_PATCH "${VERSION}")
string(REGEX REPLACE "^refs/heads/(.*)" "\\1" GIT_BRANCH "${GIT_REFSPEC}")

# Combine variables to abbreviations VERSION_SHORT and VERSION_LONG
set(VERSION_SHORT "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
set(VERSION_LONG  "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}-${GIT_SHA1}")
