#ifndef AOC_2024_COMMON_STOPWATCH_HPP
#define AOC_2024_COMMON_STOPWATCH_HPP

#include <chrono>
#include <print>
#include <ratio>
#include <string_view>

namespace AOC2024
{
    class ScopedStopwatch
    {
    public:
        using Clock = std::chrono::high_resolution_clock;
        using TimePoint = std::chrono::time_point<Clock>;
        using Duration = std::chrono::duration<double, std::milli>;

        ScopedStopwatch(std::string_view name)
            : mName(name), mStart(Clock::now())
        {}

        ~ScopedStopwatch()
        {
            std::println("Scope {} took: {}", mName, Duration(Clock::now() - mStart));
        }
    private:
        std::string_view mName;
        TimePoint mStart;
    };
}

#endif //AOC_2024_COMMON_STOPWATCH_HPP
