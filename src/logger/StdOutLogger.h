#pragma once

#include "Logger.h"

namespace logger
{

class StdOutLogger : public Logger
{
public:
    void log(std::string_view message) const override;
    std::unique_ptr<Logger> clone() const override;
};

} // namespace logger