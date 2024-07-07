#include "algorithm/ChatGptPrefixSearch.h"

#include <algorithm>
#include <iostream>
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
                                     std::string_view prefix)
{
    WordList result;
    // Mutex for thread-safe access to the result list
    std::mutex resultMutex;

    // Determine the number of threads to use
    const unsigned int numThreads = std::thread::hardware_concurrency();
    const size_t chunkSize = wordList.size() / numThreads;

    // Worker function to search in a chunk of the word list
    auto searchChunk = [&wordList, &prefix, &resultMutex, &result](size_t start,
                                                                   size_t end) {
        WordList localResult;
        for (size_t i = start; i < end; ++i) {
            if (std::string_view(wordList[i]).substr(0, prefix.size()) ==
                prefix) {
                localResult.push_back(wordList[i]);
            }
        }
        // Lock the mutex and add the local results to the global result list
        std::lock_guard lock(resultMutex);
        result.insert(result.end(), localResult.begin(), localResult.end());
    };

    // Create and launch threads
    std::vector<std::jthread> threads;
    for (unsigned int i = 0; i < numThreads; ++i) {
        size_t start = i * chunkSize;
        size_t end =
            (i == numThreads - 1) ? wordList.size() : (i + 1) * chunkSize;
        threads.emplace_back(searchChunk, start, end);
    }

    // Wait for all threads to complete
    for (auto &thread : threads) {
        thread.join();
    }

    return result;
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