#pragma once
#include "WordList.h"

#include <vector>

class WordListSlicer
{
public:
    std::vector<WordList> slice(const WordList &wl, size_t slices) const;
};