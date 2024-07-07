#include "PrefixSearch.h"
#include "algorithm/PsSimpleSingleThreaded.h"
#include "helper.h"

#include <algorithm>
#include <benchmark/benchmark.h>
#include <random>
#include <ranges>

using namespace algo;

void prefix_search_bm(benchmark::State &state)
{
    auto wl = generateSampleWordList();
    shuffleWordList(wl);
    auto n = state.range(0);
    auto sampleWl = getFirstNWords(wl, n);
    auto ps = PrefixSearch(std::make_unique<PsSimpleSingleThreaded>());

    for (auto _ : state) {
        benchmark::DoNotOptimize(ps.search(sampleWl, "ABCD"));
    }

    state.SetComplexityN(n);
}

BENCHMARK(prefix_search_bm)
    ->RangeMultiplier(10)
    ->Range(10, 400000)
    ->Complexity();

BENCHMARK_MAIN();
