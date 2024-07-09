#include "helper.h"

#include <algorithm>
#include <iostream>
#include <random>

WordList generateSampleWordList()
{
    WordList wl;

    for (char a = '0'; a <= 'z'; ++a) {
        for (char b = '0'; b <= 'z'; ++b) {
            for (char c = '0'; c <= 'z'; ++c) {
                for (char d = '0'; d <= 'z'; ++d) {
                    std::string word = {a, b, c, d};
                    wl.emplace_back(word);
                }
            }
        }
    }

    return wl;
}

void shuffleWordList(WordList &wl)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::ranges::shuffle(wl, g);
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
    for (size_t i = 0; i < n; ++i) {
        std::cout << wl[i] << std::endl;
    }

    for (size_t i = wl.size() - 1; i > wl.size() - n - 1; i--) {
        std::cout << wl[i] << std::endl;
    }
}