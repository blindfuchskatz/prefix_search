#pragma once
#include "PrefixSearchAlgorithm.h"

#include <memory>
#include <mutex>
#include <string>
#include <vector>

namespace algo
{

class ChatGptPrefixSearch2 : public PrefixSearchAlgorithm
{
public:
    WordList search(const WordList &wordList,
                    std::string_view prefix) const override;
    std::unique_ptr<PrefixSearchAlgorithm> clone() const override;
    const std::string &getName() const override;

private:
    std::string _name = "chat gpt prefix search 2";
};
} // namespace algo