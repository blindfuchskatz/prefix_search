#pragma once
#include "WordList.h"

#include <string>
#include <vector>

namespace algo
{

class PrefixSearchAlgorithm
{
public:
    virtual ~PrefixSearchAlgorithm() = default;
    virtual WordList search(const WordList &wordList,
                            std::string_view prefix) = 0;
};

} // namespace algo
