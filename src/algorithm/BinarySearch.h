#pragma once
#include "PrefixSearchAlgorithm.h"

namespace algo
{

class BinarySearch : public PrefixSearchAlgorithm
{
public:
    WordList search(const WordList &wordList,
                    std::string_view prefix) const override;
    std::unique_ptr<PrefixSearchAlgorithm> clone() const override;
    const std::string &getName() const override;

private:
    WordList _search(const WordList &wordList, std::string_view prefix) const;

    size_t _findPrefixStart(const std::vector<std::string> &words,
                            std::string_view prefix) const;

    std::string _name = "binary search";
};
} // namespace algo