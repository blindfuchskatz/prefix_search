#pragma once
#include "PrefixSearchAlgorithm.h"

#include <future>
#include <memory>

namespace algo
{

class PrefixSearchAsync : public PrefixSearchAlgorithm
{
public:
    explicit PrefixSearchAsync(std::unique_ptr<PrefixSearchAlgorithm> algo,
                               size_t cores);

    WordList search(const WordList &wordList, std::string_view prefix) override;

    std::unique_ptr<PrefixSearchAlgorithm> clone() const override;

    const std::string &getName() const override;

private:
    void _startSearchAsync(const std::vector<WordList> &slices,
                           std::vector<std::future<WordList>> &futures,
                           std::string_view prefix) const;

    WordList _getFindings(std::vector<std::future<WordList>> &futures) const;

    std::unique_ptr<PrefixSearchAlgorithm> _algo;
    size_t _cores;
    std::string _name = "prefix search async";
};

} // namespace algo