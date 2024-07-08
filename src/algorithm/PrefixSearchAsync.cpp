#include "PrefixSearchAsync.h"

#include "WordListSlicer.h"

#include <algorithm>
#include <iostream>
#include <thread>

namespace algo
{

PrefixSearchAsync::PrefixSearchAsync(
    std::unique_ptr<PrefixSearchAlgorithm> algo,
    size_t cores)
    : _algo(std::move(algo)), _cores(cores)
{
}

WordList PrefixSearchAsync::search(const WordList &wordList,
                                   std::string_view prefix) const
{
    if (_cores > wordList.size() || _cores == 0 || _cores > 128) {
        // todo PWA: add logger
        std::cout << "Warning: Either number of cores are invalid (" << _cores
                  << "), or word list size too short (" << wordList.size()
                  << "). Continue single threaded! " << std::endl;
        return _algo->search(wordList, prefix);
    }

    auto wls = WordListSlicer();
    auto slices = wls.slice(wordList, _cores);
    std::vector<WordList> findings(slices.size());

    _startSearchAsync(slices, findings, prefix);

    return _getFindings(findings);
}

std::unique_ptr<PrefixSearchAlgorithm> PrefixSearchAsync::clone() const
{
    return std::make_unique<PrefixSearchAsync>(_algo->clone(), _cores);
}

const std::string &PrefixSearchAsync::getName() const
{
    return _name;
}

void PrefixSearchAsync::_startSearchAsync(const std::vector<WordList> &slices,
                                          std::vector<WordList> &findings,
                                          std::string_view prefix) const
{
    std::vector<std::jthread> threads;

    for (size_t i = 0; i < slices.size(); ++i) {
        auto algo_clone = _algo->clone();
        threads.emplace_back(
            [&findings,
             i,
             algorithm = std::move(algo_clone),
             slice = slices[i],
             prefix]() { findings[i] = algorithm->search(slice, prefix); });
    }
}

WordList
PrefixSearchAsync::_getFindings(const std::vector<WordList> &results) const
{
    WordList findings;
    for (const auto &partialFindings : results) {
        findings.insert(
            findings.end(), partialFindings.begin(), partialFindings.end());
    }

    std::ranges::sort(findings);

    return findings;
}

} // namespace algo