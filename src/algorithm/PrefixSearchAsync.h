#pragma once
#include "Logger.h"
#include "PrefixSearchAlgorithm.h"

#include <future>
#include <memory>

namespace algo
{
class PrefixSearchAsync : public PrefixSearchAlgorithm
{
public:
    PrefixSearchAsync(std::unique_ptr<PrefixSearchAlgorithm> algo,
                      size_t cores,
                      std::unique_ptr<logger::Logger> logger);

    WordList search(const WordList &wordList,
                    std::string_view prefix) const override;
    std::unique_ptr<PrefixSearchAlgorithm> clone() const override;
    const std::string &getName() const override;

private:
    void _startSearchAsync(const std::vector<WordList> &slices,
                           std::vector<WordList> &findings,
                           std::string_view prefix) const;
    WordList _getFindings(const std::vector<WordList> &results) const;

    std::unique_ptr<PrefixSearchAlgorithm> _algo;
    size_t _cores;

    std::unique_ptr<logger::Logger> _logger;
    std::string _name = "PrefixSearchAsync";
};

} // namespace algo