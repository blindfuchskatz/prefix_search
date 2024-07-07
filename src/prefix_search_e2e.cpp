#include "PrefixSearch.h"
#include "algorithm/PsSimpleSingleThreaded.h"
#include "helper.h"

#include <algorithm>
#include <cassert>
#include <random>
#include <ranges>

using namespace algo;

int main()
{
    auto wl = generateSampleWordList();
    auto ps = PrefixSearch(std::make_unique<PsSimpleSingleThreaded>());

    printFirstAndLastNElements(wl, 5);

    shuffleWordList(wl);

    printFirstAndLastNElements(wl, 5);

    auto findings = ps.search(wl, "ABCD");

    assert(findings.size() == 1);
    assert(findings[0] == "ABCD");
}