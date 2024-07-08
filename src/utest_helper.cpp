#include "utest_helper.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

void ASSERT_WL_EQ(const WordList &expected, const WordList &actual)
{
    ASSERT_EQ(expected.size(), actual.size());
    ASSERT_THAT(expected, actual);
}

void StubLogger::log([[maybe_unused]] std::string_view message) const
{
    // do nothing
}

std::unique_ptr<logger::Logger> StubLogger::clone() const
{
    return std::make_unique<StubLogger>();
}
