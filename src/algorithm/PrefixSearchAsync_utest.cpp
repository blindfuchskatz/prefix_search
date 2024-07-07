#include "PrefixSearchAlgorithm.h"
#include "WordListSlicer.h"

#include <future>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

using namespace testing;
using namespace std;

namespace algo
{

class PrefixSearchAsync : public PrefixSearchAlgorithm
{
public:
    explicit PrefixSearchAsync(std::unique_ptr<PrefixSearchAlgorithm> algo,
                               size_t cores)
        : _algo(std::move(algo)), _cores(cores){};

    WordList search(const WordList &wordList, std::string_view prefix) override
    {
        if (_cores > wordList.size() || _cores == 0 || _cores > 128) {
            // todo PWA: introduce abstract logger -> no std::out during unit
            // tests
            std::cout << "Warning: Either number of cores are invalid ("
                      << _cores << "),or word list size to short ("
                      << wordList.size() << "). Continue single threaded! "
                      << std::endl;
            return _algo->search(wordList, prefix);
        }

        auto wls = WordListSlicer();
        std::vector<std::future<WordList>> futures;
        auto slices = wls.slice(wordList, _cores);

        _startSearchAsync(slices, futures, prefix);

        return _getFindings(futures);
    };

    std::unique_ptr<PrefixSearchAlgorithm> clone() const override
    {
        return std::make_unique<PrefixSearchAsync>(_algo->clone(), _cores);
    }

private:
    void _startSearchAsync(const std::vector<WordList> &slices,
                           std::vector<std::future<WordList>> &futures,
                           std::string_view prefix) const
    {
        for (const auto &s : slices) {
            auto algo_clone = _algo->clone();
            futures.push_back(
                std::async(std::launch::async,
                           [algorithm = std::move(algo_clone), s, prefix]() {
                               return algorithm->search(s, prefix);
                           }));
        }
    }

    WordList _getFindings(std::vector<std::future<WordList>> &futures) const
    {
        WordList findings;
        for (auto &future : futures) {
            WordList partialFindings = future.get();
            findings.insert(
                findings.end(), partialFindings.begin(), partialFindings.end());
        }

        return findings;
    }

    std::unique_ptr<PrefixSearchAlgorithm> _algo;
    size_t _cores;
};

} // namespace algo

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