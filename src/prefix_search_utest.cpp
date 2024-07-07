#include "PrefixSearchAlgorithm.h"
#include "algorithm/BinarySearch.h"
#include "algorithm/ChatGptPrefixSearch.h"
#include "algorithm/PrefixSearchAsync.h"
#include "algorithm/PsSimpleSingleThreaded.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using namespace std;
using namespace algo;

class APrefixSearch : public Test
{
protected:
    void SetUp() override
    {
        _algoList.clear();
        _algoList.emplace_back(std::make_unique<PsSimpleSingleThreaded>());
        _algoList.emplace_back(std::make_unique<PrefixSearchAsync>(
            std::make_unique<PsSimpleSingleThreaded>(), 16));

        _algoList.emplace_back(std::make_unique<BinarySearch>());
        _algoList.emplace_back(std::make_unique<ChatGptPrefixSearch>());
    }
    void ASSERT_WL_EQ(const WordList &expected, const WordList &actual) const
    {
        ASSERT_EQ(expected.size(), actual.size());
        ASSERT_THAT(expected, actual);
    }

    std::vector<std::unique_ptr<PrefixSearchAlgorithm>> _algoList;
};

TEST_F(APrefixSearch, returnsWordWhichMatchPrefixOfAOneWordList)
{

    for (const auto &a : _algoList) {
        ASSERT_WL_EQ({}, a->search({}, "ab"));
        ASSERT_WL_EQ({"ab"}, a->search({"ab"}, "ab"));
        ASSERT_WL_EQ({}, a->search({"ab"}, "bc"));
        ASSERT_WL_EQ({}, a->search({"abc"}, "bc"));
        ASSERT_WL_EQ({"abc"}, a->search({"abc"}, "ab"));
    }
}

TEST_F(APrefixSearch, returnsAllMatchingPrefixes)
{

    WordList wl = {"aaaa", "aaab", "aaac", "aaad", "aaae", "aaaf", "aaah",
                   "aaai", "aaaj", "aaak", "aaal", "aaam", "aaao", "aaap",
                   "aaaq", "aaar", "aaas", "aaat", "aaav", "aaaw", "aaax",
                   "aaay", "aaaz", "xxag", "xxan", "xxau"};

    for (const auto &a : _algoList) {
        ASSERT_WL_EQ({"xxag", "xxan", "xxau"}, a->search(wl, "xx"));
    }
}
