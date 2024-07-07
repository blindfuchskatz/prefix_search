#include "algorithm/PrefixSearchAsync.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;
using namespace std;

class StubAlgorithm : public algo::PrefixSearchAlgorithm
{
public:
    WordList search(const WordList &wordList, std::string_view prefix) override
    {
        auto p = std::string(prefix);
        return {wordList[0] + p};
    };

    std::unique_ptr<PrefixSearchAlgorithm> clone() const override
    {
        return std::make_unique<StubAlgorithm>();
    }

    const std::string &getName() const override
    {
        return name;
    }

private:
    std::string name = "StubAlgorithm";
};

class APrefixSearchAsync : public Test
{
protected:
    // todo PWA: duplicated code
    void ASSERT_WL_EQ(const WordList &expected, const WordList &actual) const
    {
        ASSERT_EQ(expected.size(), actual.size());
        ASSERT_THAT(expected, actual);
    }
};

TEST_F(APrefixSearchAsync, assignWordListSlicesToEachRealCoreAndFetchResults)
{
    auto psa = algo::PrefixSearchAsync(std::make_unique<StubAlgorithm>(), 4);

    auto findings = psa.search({"a", "b", "c", "d", "e", "f"}, "abc");

    ASSERT_WL_EQ({"aabc", "cabc", "eabc", "fabc"}, findings);
}

TEST_F(APrefixSearchAsync, processAlgorithmSingleWhenWordListToShort)
{
    auto psa = algo::PrefixSearchAsync(std::make_unique<StubAlgorithm>(), 7);

    auto findings = psa.search({"a", "b", "c", "d", "e", "f"}, "abc");

    ASSERT_WL_EQ({"aabc"}, findings);
}

TEST_F(APrefixSearchAsync, processAlgorithmSingleWhenNumberOfCoreTooLittle)
{
    auto psa = algo::PrefixSearchAsync(std::make_unique<StubAlgorithm>(), 7);

    auto findings = psa.search({"a", "b", "c", "d", "e", "f"}, "abc");

    ASSERT_WL_EQ({"aabc"}, findings);
}

TEST_F(APrefixSearchAsync, processAlgorithmSingleWhenNumberOfCoreTooMuch)
{
    auto psa = algo::PrefixSearchAsync(std::make_unique<StubAlgorithm>(), 129);

    auto findings = psa.search({"a", "b", "c", "d", "e", "f"}, "abc");

    ASSERT_WL_EQ({"aabc"}, findings);
}