#include "ScopedTimer.h"
#include "algorithm/PrefixSearchAsync.h"
#include "algorithm/PsSimpleSingleThreaded.h"
#include "helper.h"

#include <cassert>
#include <iostream>
#include <thread>

using namespace algo;

int main()
{
    size_t cores = std::thread::hardware_concurrency();

    std::cout << std::endl << "\033[1;32m";
    std::cout << "Running prefix search with " << cores << " cores"
              << std::endl;

    std::cout << "\033[0m";

    std::vector<std::unique_ptr<PrefixSearchAlgorithm>> algoList;

    algoList.emplace_back(std::make_unique<PsSimpleSingleThreaded>());
    algoList.emplace_back(std::make_unique<PrefixSearchAsync>(
        std::make_unique<PsSimpleSingleThreaded>(), cores));

    auto wl = generateSampleWordList();

    printFirstAndLastNElements(wl, 5);

    shuffleWordList(wl);

    printFirstAndLastNElements(wl, 5);

    for (const auto &a : algoList) {
        ScopedTimer timer(a->getName().c_str());
        auto findings = a->search(wl, "ABCD");

        assert(findings.size() == 1);
        assert(findings[0] == "ABCD");
    }
}