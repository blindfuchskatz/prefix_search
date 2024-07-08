#include "PrefixSearchAlgorithm.h"
#include "PrefixSearchRegistry.h"
#include "algorithm/BinarySearch.h"
#include "algorithm/ChatGptPrefixSearch.h"
#include "algorithm/PrefixSearchAsync.h"
#include "algorithm/PsSimpleSingleThreaded.h"
#include "utest_helper.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using namespace std;
using namespace algo;

const size_t NUMBER_OF_CORES = 16;

class APrefixSearch : public Test
{
protected:
    PrefixSearchRegistry _psr = PrefixSearchRegistry(NUMBER_OF_CORES);
};

TEST_F(APrefixSearch, returnsWordWhichMatchPrefixOfAOneWordList)
{

    for (const auto &a : _psr.getAlgorithm()) {
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

    for (const auto &a : _psr.getAlgorithm()) {
        ASSERT_WL_EQ({"xxag", "xxan", "xxau"}, a->search(wl, "xx"));
    }
}
