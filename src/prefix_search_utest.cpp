#include "PrefixSearch.h"
#include "PrefixSearchAlgorithm.h"
#include "algorithm/PsSimpleSingleThreaded.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using namespace std;
using namespace algo;

class APrefixSearch : public Test
{
protected:
    void ASSERT_WL_EQ(const WordList &expected, const WordList &actual) const
    {
        ASSERT_EQ(expected.size(), actual.size());
        ASSERT_THAT(expected, actual);
    }
};

TEST_F(APrefixSearch, returnsWordWhichMatchPrefixOfAOneWordList)
{
    auto ps = PrefixSearch(std::make_unique<algo::PsSimpleSingleThreaded>());

    ASSERT_WL_EQ({}, ps.search({}, "ab"));
    ASSERT_WL_EQ({"ab"}, ps.search({"ab"}, "ab"));
    ASSERT_WL_EQ({}, ps.search({"ab"}, "bc"));
    ASSERT_WL_EQ({}, ps.search({"abc"}, "bc"));
    ASSERT_WL_EQ({"abc"}, ps.search({"abc"}, "ab"));
}

TEST_F(APrefixSearch, returnsAllMatchingPrefixes)
{
    auto ps = PrefixSearch(std::make_unique<PsSimpleSingleThreaded>());

    WordList wl = {"aaaa", "aaab", "aaac", "aaad", "aaae", "aaaf", "xxag",
                   "aaah", "aaai", "aaaj", "aaak", "aaal", "aaam", "xxau",
                   "aaao", "aaap", "aaaq", "aaar", "aaas", "aaat", "xxan",
                   "aaav", "aaaw", "aaax", "aaay", "aaaz"};

    ASSERT_WL_EQ({"xxag", "xxan", "xxau"}, ps.search(wl, "xx"));
}