#include "InputGetter.hpp"

#include <print>

int main()
{
    auto input = AOC2024::GetPuzzleInput(2024, 4);
    if (!input) { return 1; }

    std::int32_t result1 = 0;
    std::int32_t result2 = 0;

    std::println("First solution: {}", result1);
    std::println("Second solution: {}", result2);

    return 0;
}
