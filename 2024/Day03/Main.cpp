#include "InputGetter.hpp"

#include <ctre.hpp>

#include <algorithm>
#include <print>
#include <ranges>

int main()
{
    namespace ranges = std::ranges;
    namespace views = std::views;

    auto input = AOC2024::GetPuzzleInput(2024, 3);
    if (!input) { return 1; }

    constexpr ctll::fixed_string expr = R"((?<expr>(mul|do|don't)\([0-9,]*\)))";
    constexpr ctll::fixed_string mulExpr = R"(mul\((?<lnum>[0-9]+),(?<rnum>[0-9]+)\))";

    auto mul = [](const auto& mul){
        return mul.template get<"lnum">().to_number() * mul.template get<"rnum">().to_number();
    };

    std::int32_t result1 = ranges::fold_left(ctre::search_all<mulExpr>(*input)
                                             | views::transform(mul),
                                             0, std::plus{});

    std::int32_t result2 = 0;
    bool enabled = true;
    for (const auto& item : ctre::search_all<expr>(*input)) {
        enabled = (item == "do()") ? true : (item == "don't()") ? false : enabled;
        if (auto match = ctre::match<mulExpr>(item); enabled && match) {
            result2 += match.get<"lnum">().to_number() * match.get<"rnum">().to_number();
        }

    }

    std::println("First solution: {}", result1);
    std::println("Second solution: {}", result2);

    return 0;
}
