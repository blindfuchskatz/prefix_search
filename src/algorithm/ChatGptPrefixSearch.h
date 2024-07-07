#pragma once
#include "PrefixSearchAlgorithm.h"

namespace algo
{

class ChatGptPrefixSearch : public PrefixSearchAlgorithm
{
public:
    ChatGptPrefixSearch();
    ~ChatGptPrefixSearch() override;
    WordList search(const WordList &wordList, std::string_view prefix) override;
    std::unique_ptr<PrefixSearchAlgorithm> clone() const override;
    const std::string &getName() const override;

private:
    size_t _findPrefixStart(const std::vector<std::string> &words,
                            std::string_view prefix) const;

    std::string _name = "chat gpt prefix search";
};
} // namespace algo