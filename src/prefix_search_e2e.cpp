#include "PrefixSearchRegistry.h"
#include "ScopedTimer.h"
#include "algorithm/BinarySearch.h"
#include "algorithm/ChatGptPrefixSearch.h"
#include "algorithm/PrefixSearchAsync.h"
#include "algorithm/PsSimpleSingleThreaded.h"
#include "helper.h"

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

void test_find_no_word(PrefixSearchAlgorithm const &a, const WordList &wl)
{
    auto findings = a.search(wl, "abcd");
    assert(findings.size() == 0);

    findings = a.search(wl, "ABCDE");
    assert(findings.size() == 0);
}

void test_find_multiple_words(PrefixSearchAlgorithm const &a,
                              const WordList &wl)
{
    auto findings = a.search(wl, "ABC");
    assert(findings.size() == 26);
}

int main()
{
    size_t cores = std::thread::hardware_concurrency();
    auto psr = PrefixSearchRegistry(cores);

    std::cout << std::endl << "\033[1;32m";
    std::cout << "Running prefix search on " << cores << " cores" << std::endl;
    std::cout << "\033[0m";

    auto wl = generateSampleWordList();

    printFirstAndLastNElements(wl, 5);

    for (const auto &a : psr.getAlgorithm()) {
        test_find_one_word(*a, wl);
        test_find_no_word(*a, wl);
        test_find_multiple_words(*a, wl);
    }
}