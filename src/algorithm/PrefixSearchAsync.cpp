#include "PrefixSearchAsync.h"

#include "WordListSlicer.h"

#include <algorithm>
#include <iostream>

namespace algo
{

PrefixSearchAsync::PrefixSearchAsync(
    std::unique_ptr<PrefixSearchAlgorithm> algo,
    size_t cores)
    : _algo(std::move(algo)), _cores(cores){};

WordList PrefixSearchAsync::search(const WordList &wordList,
                                   std::string_view prefix)
{
    if (_cores > wordList.size() || _cores == 0 || _cores > 128) {
        // todo PWA: introduce abstract logger -> no std::out during unit
        // tests
        std::cout << "Warning: Either number of cores are invalid (" << _cores
                  << "),or word list size to short (" << wordList.size()
                  << "). Continue single threaded! " << std::endl;
        return _algo->search(wordList, prefix);
    }

    auto wls = WordListSlicer();
    std::vector<std::future<WordList>> futures;
    auto slices = wls.slice(wordList, _cores);

    _startSearchAsync(slices, futures, prefix);

    return _getFindings(futures);
};

std::unique_ptr<PrefixSearchAlgorithm> PrefixSearchAsync::clone() const
{
    return std::make_unique<PrefixSearchAsync>(_algo->clone(), _cores);
}

const std::string &PrefixSearchAsync::getName() const
{
    return _name;
}

void PrefixSearchAsync::_startSearchAsync(
    const std::vector<WordList> &slices,
    std::vector<std::future<WordList>> &futures,
    std::string_view prefix) const
{
    for (const auto &s : slices) {
        auto algo_clone = _algo->clone();
        futures.push_back(
            std::async(std::launch::async,
                       [algorithm = std::move(algo_clone), s, prefix]() {
                           return algorithm->search(s, prefix);
                       }));
    }
}

WordList PrefixSearchAsync::_getFindings(
    std::vector<std::future<WordList>> &futures) const
{
    WordList findings;
    for (auto &future : futures) {
        WordList partialFindings = future.get();
        findings.insert(
            findings.end(), partialFindings.begin(), partialFindings.end());
    }

    std::ranges::sort(findings);

    return findings;
}

} // namespace algo