#include "algorithm/ChatGptPrefixSearch2.h"

#include <algorithm>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace algo
{

std::mutex _mtx;

void _searchPrefixInRange(const WordList &wordList,
                          std::string_view prefix,
                          WordList &result,
                          size_t start,
                          size_t end)
{
    WordList localResult;
    for (size_t i = start; i < end; ++i) {
        if (wordList[i].find(prefix) == 0) {
            localResult.emplace_back(wordList[i]);
        }
    }
    std::scoped_lock lock(_mtx);
    result.insert(result.end(), localResult.begin(), localResult.end());
}

WordList ChatGptPrefixSearch2::search(const WordList &wordList,
                                      std::string_view prefix) const
{
    size_t numCores = std::thread::hardware_concurrency();
    std::vector<std::string> result;
    size_t totalWords = wordList.size();
    size_t chunkSize = totalWords / numCores;
    std::vector<std::jthread> threads;

    for (size_t i = 0; i < numCores; ++i) {
        size_t start = i * chunkSize;
        size_t end = (i == numCores - 1) ? totalWords : (i + 1) * chunkSize;
        threads.emplace_back(_searchPrefixInRange,
                             std::ref(wordList),
                             std::ref(prefix),
                             std::ref(result),
                             start,
                             end);
    }

    for (auto &t : threads) {
        t.join();
    }

    std::ranges::sort(result);

    return result;
}

std::unique_ptr<PrefixSearchAlgorithm> ChatGptPrefixSearch2::clone() const
{
    return std::make_unique<ChatGptPrefixSearch2>();
}

const std::string &ChatGptPrefixSearch2::getName() const
{
    return _name;
}

} // namespace algo