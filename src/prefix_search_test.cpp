#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>

using namespace testing;
using namespace std;

class APrefixSearch : public Test
{
protected:
    void SetUp() override
    {
        // not relevant now
    }

    void TearDown() override
    {
        // not relevant now
    }
};

TEST_F(APrefixSearch, project_setup)
{
    ASSERT_THAT(100, 100);
}