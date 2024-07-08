cmake_minimum_required(VERSION 3.14)
project(my_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -I${CMAKE_SOURCE_DIR}/src")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -I${CMAKE_SOURCE_DIR}/src")
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.8.4
)
FetchContent_MakeAvailable(benchmark)

enable_testing()

set(COMMON_SOURCES
  src/WordListSlicer.cpp
  src/algorithm/PsSimpleSingleThreaded.cpp
  src/algorithm/PrefixSearchAsync.cpp
  src/algorithm/BinarySearch.cpp
  src/algorithm/ChatGptPrefixSearch.cpp
)

set(TEST_SOURCES
  src/prefix_search_utest.cpp
  src/WordListSlicer_utest.cpp
  src/utest_helper.cpp
  src/algorithm/PrefixSearchAsync_utest.cpp
)

set(BM_SOURCES
  src/prefix_search_bm.cpp
  src/helper.cpp
)

set(E2E_SOURCES
  src/prefix_search_e2e.cpp
  src/helper.cpp
)

# Add the test executable
add_executable(prefix_search_utest ${TEST_SOURCES} ${COMMON_SOURCES})
target_link_libraries(prefix_search_utest GTest::gtest_main GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(prefix_search_utest)

# Add the benchmark executable
add_executable(prefix_search_bm ${BM_SOURCES} ${COMMON_SOURCES})
target_link_libraries(prefix_search_bm benchmark::benchmark)

# Add the end-to-end executable
add_executable(prefix_search_e2e ${E2E_SOURCES} ${COMMON_SOURCES})

