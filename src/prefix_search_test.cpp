#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace testing;
using namespace std;

using WordList = std::vector<std::string>;

class PrefixSearchAlgorithm
{
public:
    virtual ~PrefixSearchAlgorithm() = default;
    virtual WordList search(const WordList &wordList,
                            std::string_view prefix) = 0;
};

class PsSimpleSingleThreaded : public PrefixSearchAlgorithm
{
public:
    ~PsSimpleSingleThreaded() override = default;

    WordList search(const WordList &wordList, std::string_view prefix) override
    {
        WordList findings;
        for (const auto &word : wordList) {
            if (word.starts_with(prefix)) {
                findings.emplace_back(word);
            }
        }

        std::ranges::sort(findings);
        return findings;
    }
};

class PrefixSearch
{
public:
    explicit PrefixSearch(std::unique_ptr<PrefixSearchAlgorithm> algo)
        : _algo(std::move(algo)){};

    WordList search(const WordList &wordList, std::string_view prefix) const
    {
        return _algo->search(wordList, prefix);
    }

private:
    std::unique_ptr<PrefixSearchAlgorithm> _algo;
};

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
    auto ps = PrefixSearch(std::make_unique<PsSimpleSingleThreaded>());

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