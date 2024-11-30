#include "InputGetter.hpp"

#include <print>

int main()
{
    auto input = AOC2024::GetPuzzleInput(2024, 1);

    if (!input) {
        std::println("Couldn't get the input!");
        return 1;
    }

    std::println("The input:\n{}", *input);

    return 0;
}
