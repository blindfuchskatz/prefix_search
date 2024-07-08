#pragma once
#include "Logger.h"
#include "WordList.h"

void ASSERT_WL_EQ(const WordList &expected, const WordList &actual);

class StubLogger : public logger::Logger
{
public:
    void log([[maybe_unused]] std::string_view message) const override;
    std::unique_ptr<Logger> clone() const override;
};
