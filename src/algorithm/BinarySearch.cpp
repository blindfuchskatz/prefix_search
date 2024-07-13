#include "algorithm/BinarySearch.h"

#include <algorithm>
#include <execution>
#include <numeric>
#include <ranges>

namespace algo
{

WordList BinarySearch::search(const WordList &wordList,
                              std::string_view prefix) const
{
    if (std::ranges::is_sorted(wordList) == false) {
        WordList copyWordList = wordList;
        std::ranges::sort(copyWordList);
        return _search(copyWordList, prefix);
    }
    return _search(wordList, prefix);
}

std::unique_ptr<PrefixSearchAlgorithm> BinarySearch::clone() const
{
    return std::make_unique<BinarySearch>();
}

const std::string &BinarySearch::getName() const
{
    return _name;
}

WordList BinarySearch::_search(const WordList &wordList,
                               std::string_view prefix) const
{
    WordList findings;
    size_t startIdx = _findPrefixStart(wordList, prefix);

    for (size_t i = startIdx; i < wordList.size(); ++i) {
        if (wordList[i].compare(0, prefix.size(), prefix) == 0) {
            findings.emplace_back(wordList[i]);
        }
        else {
            break; // Since the vector is sorted, no need to continue if the
                   // prefix doesn't match
        }
    }

    return findings;
}

size_t BinarySearch::_findPrefixStart(const std::vector<std::string> &words,
                                      std::string_view prefix) const
{
    size_t low = 0;
    size_t high = words.size();

    while (low < high) {
        size_t mid = std::midpoint(low, high);
        if (words[mid].compare(0, prefix.size(), prefix) < 0) {
            low = mid + 1;
        }
        else {
            high = mid;
        }
    }
    return low;
}

} // namespace algo