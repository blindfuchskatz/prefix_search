#pragma once
#include "WordList.h"

#include <memory>
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
    virtual std::unique_ptr<PrefixSearchAlgorithm> clone() const = 0;
    virtual const std::string &getName() const = 0;
};

} // namespace algo
