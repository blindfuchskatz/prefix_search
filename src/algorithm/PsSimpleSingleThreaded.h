#pragma once
#include "PrefixSearchAlgorithm.h"

namespace algo
{

class PsSimpleSingleThreaded : public PrefixSearchAlgorithm
{
public:
    WordList search(const WordList &wordList,
                    std::string_view prefix) const override;
    std::unique_ptr<PrefixSearchAlgorithm> clone() const override;
    const std::string &getName() const override;

private:
    std::string _name = "prefix search simple single threaded";
};
} // namespace algo