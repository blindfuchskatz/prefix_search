#include "algorithm/ChatGptPrefixSearch.h"

#include <algorithm>
#include <mutex>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

namespace algo
{

ChatGptPrefixSearch::ChatGptPrefixSearch() = default;

ChatGptPrefixSearch::~ChatGptPrefixSearch() = default;

WordList ChatGptPrefixSearch::search(const WordList &wordList,
                                     std::string_view prefix) const
{
    WordList findings;
    std::mutex mutex;
    const unsigned int numThreads = std::thread::hardware_concurrency();
    const size_t chunkSize = wordList.size() / numThreads;

    auto searchChunk = [&wordList, &prefix, &mutex, &findings](size_t start,
                                                               size_t end) {
        WordList tmpWl;
        for (size_t i = start; i < end; ++i) {
            if (wordList[i].starts_with(prefix)) {
                tmpWl.emplace_back(wordList[i]);
            }
        }
        std::lock_guard lock(mutex);
        findings.insert(findings.end(), tmpWl.begin(), tmpWl.end());
    };

    std::vector<std::jthread> threads;
    for (unsigned int i = 0; i < numThreads; ++i) {
        size_t start = i * chunkSize;
        size_t end =
            (i == numThreads - 1) ? wordList.size() : (i + 1) * chunkSize;
        threads.emplace_back(searchChunk, start, end);
    }

    std::ranges::sort(findings);

    return findings;
}

std::unique_ptr<PrefixSearchAlgorithm> ChatGptPrefixSearch::clone() const
{
    return std::make_unique<ChatGptPrefixSearch>();
}

const std::string &ChatGptPrefixSearch::getName() const
{
    return _name;
}

} // namespace algo