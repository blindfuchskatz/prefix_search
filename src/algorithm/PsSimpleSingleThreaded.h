#pragma once
#include "PrefixSearchAlgorithm.h"

namespace algo
{

class PsSimpleSingleThreaded : public PrefixSearchAlgorithm
{
public:
    PsSimpleSingleThreaded();
    ~PsSimpleSingleThreaded() override;
    WordList search(const WordList &wordList, std::string_view prefix) override;
    std::unique_ptr<PrefixSearchAlgorithm> clone() const override;
    const std::string &getName() const override;

private:
    std::string _name = "prefix search simple single threaded";
};
} // namespace algo