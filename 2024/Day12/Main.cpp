#include "InputGetter.hpp"
#include "Stopwatch.hpp"

#include <print>
#include <ranges>

int main()
{
    AOC2024::ScopedStopwatch s("AoC 2024 Day 12");

    namespace ranges = std::ranges;
    namespace views = std::views;

    auto input = AOC2024::GetPuzzleInput(2024, 12);
    if (!input) { return 1; }

    std::int64_t result1 = 0;
    std::int64_t result2 = 0;

    std::println("First solution: {}", result1);
    std::println("Second solution: {}", result2);

    return 0;
}
