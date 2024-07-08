#pragma once
#include <memory>
#include <string_view>

namespace logger
{

class Logger
{
public:
    virtual ~Logger() = default;
    virtual void log(std::string_view message) const = 0;
    virtual std::unique_ptr<Logger> clone() const = 0;
};

} // namespace logger