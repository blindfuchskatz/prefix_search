# Prefix Search

This project is inspired by the book *C++ High Performance (ISBN 978-1839216541)* and serves as a playground for enhancing skills in performance-oriented programming in C++. The goal is to identify the most efficient algorithm for prefix search. A prefix search algorithm collects all occurrences of a given prefix in a list of words and stores the results in a separate list.

## Project Setup

The easiest, but not resource-saving way to use the Prefix Search project is via the *prefix_search_sdk*.
The following commands have been tested exclusively in an Ubuntu 22.04 environment with Docker installed.


For building the *prefix_search_sdk* docker image use the following command in the root directory of the project:

        ./run_build_sdk.sh

After the image was build run the following command in the root directory of the project to start the *prefix_search_sdk*:

        ./run_sdk.sh

All following commands shall be executed within the *prefix_search_sdk*

## Build and Run Unit and E2E Tests

The project uses CMake for building the executables. The following command build and run the unit and e2e tests:

        ./build_and_verify.sh

During the execution of the e2e tests the run time for each implemented algorithm is measure and printed into std::out for comparison purpose.

## Adding new algorithms for investigations

The project have a plug in structure.
All current investigated are implemented in the [algorithm](./src/algorithm) directory.

If you want to add a new algorithm just place your source and header next to the existing ones. The new algorithm must derive from the interface class [PrefixSearchAlgorithm](./src/PrefixSearchAlgorithm.h).

After storing the new algorithm source and header file append the source file name at the end of the following [CMakeLists](./CMakeLists.txt) section.

        set(COMMON_SOURCESset(COMMON_SOURCES
            SomeAlgorithmSourceFiles.cpp
            PlaceHereYourNewAlgorithmSourceFile.cpp
        )

Finally you have to add your new algorithm analog to the existing ones to the [PrefixSearchRegistry](./src/PrefixSearchRegistry.cpp).

## Run google Benchmark Framework

In addition to the simple performance measurement during executing the e2e tests, there is the opportunity to run a more sophisticated performance measurement with the google benchmark framework.

To run the google benchmark framework execute the following command:

        ./build_and_bm.sh

If you want to add your own written algorithm as well to the benchmark execution, simple add it in the same manner as the existing ones.