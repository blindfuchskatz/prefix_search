#include "PrefixSearch.h"
#include "PrefixSearchAlgorithm.h"
#include "algorithm/PsSimpleSingleThreaded.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using namespace std;

class WordListSlicer
{
public:
    std::vector<WordList> slice(WordList &wl, size_t slices) const
    {

        if (wl.empty() || slices == 0 || slices > wl.size()) {
            return {};
        }

        std::vector<WordList> result;
        size_t total_size = wl.size();
        size_t slice_size = total_size / slices;
        size_t remainder = total_size % slices;

        auto it = wl.begin();
        for (size_t i = 0; i < slices; ++i) {
            size_t current_slice_size = slice_size + (i < remainder ? 1 : 0);

            auto slice_range =
                std::ranges::subrange(it, std::next(it, current_slice_size));

            result.emplace_back(slice_range.begin(), slice_range.end());

            std::advance(it, current_slice_size);
        }

        return result;
    }
};

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