#include "InputGetter.hpp"

#include <print>
#include <ranges>

int main()
{
    namespace ranges = std::ranges;
    namespace views = std::views;

    auto input = AOC2024::GetPuzzleInput(2024, 5);
    if (!input) { return 1; }

    std::int32_t result1 = 0;
    std::int32_t result2 = 0;

    std::println("First solution: {}", result1);
    std::println("Second solution: {}", result2);

    return 0;
}
