#include "algorithm/BinarySearch.h"
#include "algorithm/ChatGptPrefixSearch.h"
#include "algorithm/PrefixSearchAsync.h"
#include "algorithm/PsSimpleSingleThreaded.h"
#include "helper.h"

#include <algorithm>
#include <benchmark/benchmark.h>
#include <iostream>
#include <random>
#include <ranges>

using namespace algo;

void prefix_search_single_threaded_bm(benchmark::State &state)
{
    auto wl = generateSampleWordList();
    shuffleWordList(wl);
    auto n = state.range(0);
    auto sampleWl = getFirstNWords(wl, n);
    auto algo = std::make_unique<PsSimpleSingleThreaded>();

    for (auto _ : state) {
        benchmark::DoNotOptimize(algo->search(sampleWl, "ABCD"));
    }

    state.SetComplexityN(n);
}

void prefix_search_async_bm(benchmark::State &state)
{
    size_t cores = std::thread::hardware_concurrency();

    auto wl = generateSampleWordList();
    shuffleWordList(wl);
    auto n = state.range(0);
    auto sampleWl = getFirstNWords(wl, n);

    auto algo = std::make_unique<PrefixSearchAsync>(
        std::make_unique<PsSimpleSingleThreaded>(), cores);

    for (auto _ : state) {
        benchmark::DoNotOptimize(algo->search(sampleWl, "ABCD"));
    }

    state.SetComplexityN(n);
}

void prefix_binary_search_bm(benchmark::State &state)
{
    auto wl = generateSampleWordList();
    auto n = state.range(0);
    auto sampleWl = getFirstNWords(wl, n);

    auto algo = std::make_unique<BinarySearch>();

    for (auto _ : state) {
        benchmark::DoNotOptimize(algo->search(sampleWl, "ABCD"));
    }

    state.SetComplexityN(n);
}

void prefix_chat_gpt_prefix_search_bm(benchmark::State &state)
{
    auto wl = generateSampleWordList();
    auto n = state.range(0);
    auto sampleWl = getFirstNWords(wl, n);

    auto algo = std::make_unique<ChatGptPrefixSearch>();

    for (auto _ : state) {
        benchmark::DoNotOptimize(algo->search(sampleWl, "ABCD"));
    }

    state.SetComplexityN(n);
}

BENCHMARK(prefix_search_single_threaded_bm)
    ->RangeMultiplier(10)
    ->Range(100, 400000)
    ->Complexity();

BENCHMARK(prefix_search_async_bm)
    ->RangeMultiplier(10)
    ->Range(100, 400000)
    ->Complexity();

BENCHMARK(prefix_binary_search_bm)
    ->RangeMultiplier(10)
    ->Range(100, 400000)
    ->Complexity();

BENCHMARK(prefix_chat_gpt_prefix_search_bm)
    ->RangeMultiplier(10)
    ->Range(100, 400000)
    ->Complexity();

BENCHMARK_MAIN();
