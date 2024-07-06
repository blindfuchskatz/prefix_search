#pragma once
#include "PrefixSearchAlgorithm.h"
#include "WordList.h"

#include <memory>

class PrefixSearch
{
public:
    explicit PrefixSearch(std::unique_ptr<algo::PrefixSearchAlgorithm> algo);

    WordList search(const WordList &wordList, std::string_view prefix) const;

private:
    std::unique_ptr<algo::PrefixSearchAlgorithm> _algo;
};