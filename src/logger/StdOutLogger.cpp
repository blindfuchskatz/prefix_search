#include "logger/StdOutLogger.h"

#include <iostream>

namespace logger
{
void StdOutLogger::log(std::string_view message) const
{
    std::cout << message << std::endl;
}

std::unique_ptr<Logger> StdOutLogger::clone() const
{
    return std::make_unique<StdOutLogger>();
}

} // namespace logger