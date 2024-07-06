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
};
} // namespace algo