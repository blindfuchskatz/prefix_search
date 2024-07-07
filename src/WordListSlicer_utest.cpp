#include "WordListSlicer.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using namespace std;

class AWordListSlicer : public Test
{
protected:
    void ASSERT_SWL_EQ(const std::vector<WordList> &expected,
                       const std::vector<WordList> &actual) const
    {
        ASSERT_EQ(expected.size(), actual.size());
        ASSERT_THAT(expected, actual);
    }
};

TEST_F(AWordListSlicer, returnEmptySliceListWhenWordListIsEmpty)
{
    auto wls = WordListSlicer();
    WordList wl = {};

    ASSERT_SWL_EQ({}, wls.slice(wl, 1));
}

TEST_F(AWordListSlicer, sliceWordListToOneSlice)
{
    auto wls = WordListSlicer();
    WordList wl = {"a", "b", "c", "d"};

    ASSERT_SWL_EQ({{"a", "b", "c", "d"}}, wls.slice(wl, 1));
}

TEST_F(AWordListSlicer, sliceEvenWordListToForSlices)
{
    auto wls = WordListSlicer();
    WordList wl = {"a", "b", "c", "d"};

    ASSERT_SWL_EQ({{"a"}, {"b"}, {"c"}, {"d"}}, wls.slice(wl, 4));
}

TEST_F(AWordListSlicer, sliceUnevenWordListToForSlices)
{
    auto wls = WordListSlicer();
    WordList wl = {"a", "b", "c", "d", "e"};

    ASSERT_SWL_EQ({{"a", "b"}, {"c"}, {"d"}, {"e"}}, wls.slice(wl, 4));
}

TEST_F(AWordListSlicer, sliceEvenWordListToUnevenSlices)
{
    auto wls = WordListSlicer();
    WordList wl = {"a", "b", "c", "d"};

    ASSERT_SWL_EQ({{"a", "b"}, {"c"}, {"d"}}, wls.slice(wl, 3));
}

TEST_F(AWordListSlicer, returnEmptySliceListWhenSlicesAreZero)
{
    auto wls = WordListSlicer();
    WordList wl = {};

    ASSERT_SWL_EQ({}, wls.slice(wl, 0));
}

TEST_F(AWordListSlicer, returnEmptySliceListWhenSlicesGreaterThanWordList)
{
    auto wls = WordListSlicer();
    WordList wl = {"a", "b", "c", "d", "e"};

    ASSERT_SWL_EQ({}, wls.slice(wl, 6));
}