#include "PrefixSearch.h"

PrefixSearch::PrefixSearch(std::unique_ptr<algo::PrefixSearchAlgorithm> algo)
    : _algo(std::move(algo)){};

WordList PrefixSearch::search(const WordList &wordList,
                              std::string_view prefix) const
{
    return _algo->search(wordList, prefix);
}
