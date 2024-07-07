#include <chrono>
#include <iostream>
#include <string>

class ScopedTimer
{
public:
    using ClockType = std::chrono::steady_clock;

    explicit ScopedTimer(const char *func)
        : _function_name{func}, _start{ClockType::now()}
    {
    }

    ScopedTimer(const ScopedTimer &) = delete;
    ScopedTimer(ScopedTimer &&) = delete;

    auto operator=(const ScopedTimer &) -> ScopedTimer & = delete;
    auto operator=(ScopedTimer &&) -> ScopedTimer & = delete;

    ~ScopedTimer()
    {
        using namespace std::chrono;
        auto stop = ClockType::now();
        auto duration = (stop - _start);
        auto ms = duration_cast<microseconds>(duration).count();
        std::cout << ms << " ms " << _function_name << std::endl;
    }

private:
    const char *_function_name;
    const ClockType::time_point _start{};
};