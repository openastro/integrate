# Copyright (c) 2014-2022 Kartik Kumar (me@kartikkumar.com)
# Distributed under the MIT License.
# See accompanying file LICENSE or copy at http://opensource.org/licenses/MIT

# The CMake setup for this project is based off of the following sources:
# - https://cliutils.gitlab.io/modern-cmake
# - https://github.com/catchorg/Catch2/blob/devel/docs/cmake-integration.md

# @TODO: add find_package call to use Catch2 that is already present and only fetch otherwise
# @TODO: consider only using the Catch2 single header to avoid building the whole library (slow)

# -----------------------------------------------

# List all files that should be included in the library here
set(
  TESTS_SOURCE_LIST
	testEuler.cpp
  testRK4.cpp
  testRKF45.cpp
  testRKF78.cpp
  )

# -----------------------------------------------

# Fetch Catch2 testing library
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1 # or a later release
)
FetchContent_MakeAvailable(Catch2)

add_library(
  integrate_tests_lib
  "testState.cpp"
  "testState.hpp"
	"testDynamicalModels.cpp"
	"testDynamicalModels.hpp"
)
target_include_directories(integrate_tests_lib PRIVATE ../tests)
target_compile_features(integrate_tests_lib PRIVATE cxx_std_11)

# Add test executables and linked libraries
add_executable(integrate_tests ${TESTS_SOURCE_LIST})
target_compile_features(integrate_tests PRIVATE cxx_std_11)
target_link_libraries(integrate_tests PRIVATE integrate_lib integrate_tests_lib Catch2::Catch2WithMain)

# Register tests in CTest
include(Catch)
catch_discover_tests(integrate_tests)
