#include "PrefixSearchRegistry.h"

#include "algorithm/BinarySearch.h"
#include "algorithm/ChatGptPrefixSearch.h"
#include "algorithm/ChatGptPrefixSearch2.h"
#include "algorithm/PrefixSearchAsync.h"
#include "algorithm/PsSimpleSingleThreaded.h"

PrefixSearchRegistry::PrefixSearchRegistry(
    size_t cores,
    std::unique_ptr<logger::Logger> logger)
{
    _algoList.emplace_back(std::make_unique<algo::PsSimpleSingleThreaded>());

    _algoList.emplace_back(std::make_unique<algo::PrefixSearchAsync>(
        std::make_unique<algo::PsSimpleSingleThreaded>(),
        cores,
        std::move(logger)));

    _algoList.emplace_back(std::make_unique<algo::BinarySearch>());

    _algoList.emplace_back(std::make_unique<algo::ChatGptPrefixSearch>());
    _algoList.emplace_back(std::make_unique<algo::ChatGptPrefixSearch2>());
}

const std::vector<std::unique_ptr<algo::PrefixSearchAlgorithm>> &
PrefixSearchRegistry::getAlgorithm() const
{
    return _algoList;
}
