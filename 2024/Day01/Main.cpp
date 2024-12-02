#include "InputGetter.hpp"

#include <algorithm>
#include <print>
#include <ranges>
#include <utility>
#include <vector>

int main()
{
    namespace ranges = std::ranges;
    namespace views = std::views;

    auto input = AOC2024::GetPuzzleInput(2024, 1);
    if (!input) { return 1; }
    std::vector<std::int32_t> left, right;

    auto parseLine = [](const auto& line) {
        auto view = views::split(line, ' ')
                  | views::filter([](const auto& item) { return item.size(); })
                  | views::transform([](const auto& item) { return std::stoi(std::string(item.begin(), item.end())); });
        return std::pair<std::int32_t, std::int32_t>(*view.begin(), *(view | views::drop(1)).begin() );
    };

    auto pairs = views::split(*input, '\n')
               | views::filter([](const auto& item){ return item.size(); })
               | views::transform(parseLine);

    for (auto [first, second] : pairs) {
        left.push_back(first);
        right.push_back(second);
    }

    ranges::sort(left);
    ranges::sort(right);

    std::int32_t result1 = ranges::fold_left(views::zip(left, right)
                         | views::transform([](const auto& pair) { return std::abs(std::get<0>(pair) - std::get<1>(pair)); }),
                         0, std::plus<std::int32_t>());

    auto similarityScore = [&right](auto lnum) {
        auto equalRange = right | views::filter([lnum](auto rnum) { return lnum == rnum; });
        std::int32_t equalCount = std::distance(equalRange.begin(), equalRange.end());
        return lnum * equalCount;
    };

    std::int32_t result2 = ranges::fold_left(left
                         | views::transform(similarityScore),
                         0, std::plus<std::int32_t>());
    std::println("First solution: {}", result1);
    std::println("Second result: {}", result2);

    return 0;
}
