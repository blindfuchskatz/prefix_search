#include "helper.h"

#include <algorithm>
#include <iostream>
#include <random>

void shuffleWordList(WordList &wl)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::ranges::shuffle(wl, g);
}

WordList generateSampleWordList()
{
    WordList wl;
    char start = 'A';
    char end = 'Z';

    for (char a = start; a <= end; ++a) {
        for (char b = start; b <= end; ++b) {
            for (char c = start; c <= end; ++c) {
                for (char d = start; d <= end; ++d) {
                    std::string word = {a, b, c, d};
                    wl.emplace_back(word);
                }
            }
        }
    }

    shuffleWordList(wl);

    return wl;
}

WordList getFirstNWords(WordList &wl, size_t n)
{
    if (n > wl.size()) {
        n = wl.size();
    }

    return WordList(wl.begin(), wl.begin() + n);
}

void printFirstAndLastNElements(const WordList &wl, uint n)
{
    std::cout << "First " << n << " words:" << std::endl;
    for (size_t i = 0; i < n; ++i) {
        std::cout << wl[i] << std::endl;
    }

    std::cout << std::endl << "Last " << n << " words:" << std::endl;

    for (size_t i = wl.size() - 1; i > wl.size() - n - 1; i--) {
        std::cout << wl[i] << std::endl;
    }

    std::cout << std::endl;
}