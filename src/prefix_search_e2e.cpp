#include "PrefixSearchRegistry.h"
#include "ScopedTimer.h"
#include "algorithm/BinarySearch.h"
#include "algorithm/ChatGptPrefixSearch.h"
#include "algorithm/PrefixSearchAsync.h"
#include "algorithm/PsSimpleSingleThreaded.h"
#include "helper.h"
#include "logger/StdOutLogger.h"

#include <cassert>
#include <iostream>
#include <thread>

using namespace algo;

void test_find_one_word(const PrefixSearchAlgorithm &a, const WordList &wl)
{
    ScopedTimer timer(a.getName().c_str());
    auto findings = a.search(wl, "ABCD");

    assert(findings.size() == 1);
    assert(findings[0] == "ABCD");
}

int main()
{
    size_t cores = std::thread::hardware_concurrency();
    auto psr =
        PrefixSearchRegistry(cores, std::make_unique<logger::StdOutLogger>());

    std::cout << std::endl << "\033[1;32m";
    std::cout << "Running prefix search on " << cores << " cores" << std::endl;
    std::cout << "\033[0m";

    auto wl = generateSampleWordList();

    printFirstAndLastNElements(wl, 5);

    for (const auto &a : psr.getAlgorithm()) {
        test_find_one_word(*a, wl);
    }
}