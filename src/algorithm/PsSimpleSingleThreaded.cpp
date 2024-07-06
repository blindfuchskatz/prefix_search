#include "algorithm/PsSimpleSingleThreaded.h"

#include <algorithm>

namespace algo
{

PsSimpleSingleThreaded::PsSimpleSingleThreaded() = default;

PsSimpleSingleThreaded::~PsSimpleSingleThreaded() = default;

WordList PsSimpleSingleThreaded::search(const WordList &wordList,
                                        std::string_view prefix)
{
    WordList findings;
    for (const auto &word : wordList) {
        if (word.starts_with(prefix)) {
            findings.emplace_back(word);
        }
    }

    std::ranges::sort(findings);
    return findings;
}

} // namespace algo
