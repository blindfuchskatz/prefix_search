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

add_executable(
  prefix_search_utest
  src/prefix_search_utest.cpp
  src/WordListSlicer_utest.cpp
  src/PrefixSearch.cpp
  src/WordListSlicer.cpp
  src/algorithm/PsSimpleSingleThreaded.cpp
)
target_link_libraries(
  prefix_search_utest
  GTest::gtest_main
  GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(prefix_search_utest)


add_executable(
  prefix_search_bm
  src/prefix_search_bm.cpp
  src/PrefixSearch.cpp
  src/helper.cpp
  src/algorithm/PsSimpleSingleThreaded.cpp
)

target_link_libraries(
  prefix_search_bm
  benchmark::benchmark
)

add_executable(
  prefix_search_e2e
  src/prefix_search_e2e.cpp
  src/PrefixSearch.cpp
  src/helper.cpp
  src/algorithm/PsSimpleSingleThreaded.cpp
)

