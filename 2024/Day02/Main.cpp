#include "InputGetter.hpp"

#include <algorithm>
#include <cstdlib>
#include <print>
#include <ranges>
#include <vector>

int main()
{
    namespace ranges = std::ranges;
    namespace views = std::views;

    auto input = AOC2024::GetPuzzleInput(2024, 2);
    if (!input) { return 1; }
    std::vector<std::vector<std::int32_t>> reports;

    auto parseLine = [](const auto& line) {
        return views::split(line, ' ')
             | views::filter([](const auto& item) { return item.size(); })
             | views::transform([](const auto& item) { return std::stoi(ranges::to<std::string>(item)); })
             | ranges::to<std::vector<std::int32_t>>();
    };

    reports = views::split(*input, '\n')
            | views::filter([](const auto& item){ return item.size(); })
            | views::transform(parseLine)
            | ranges::to<std::vector<std::vector<std::int32_t>>>();

    auto diff = [](std::int32_t lnum, std::int32_t rnum) {
        return std::abs(lnum - rnum);
    };

    auto isSafe = [diff](const auto& report) {
        auto diffs = report
                   | views::slide(2)
                   | views::transform([diff](const auto& item) { return ranges::fold_left(item, 0, diff); })
                   | views::transform([](const auto& item) { return item >= 1 && item <= 3; });
        bool monotone = ranges::is_sorted(report) || ranges::is_sorted(report, std::greater{});
        return ranges::count(diffs, true) == (report.size() - 1) && monotone;
    };

    auto isSafeDampened = [diff](const auto& report) {
        for (std::size_t i : views::iota(0, std::int32_t(report.size()))) {
            auto skipped = report
                         | views::enumerate
                         | views::filter([i](const auto& kv) { return std::get<0>(kv) != i; })
                         | views::values;
            auto diffs = skipped
                       | views::slide(2)
                       | views::transform([diff](const auto& item) { return ranges::fold_left(item, 0, diff); })
                       | views::transform([](const auto& item) { return item >= 1 && item <= 3; });
            bool monotone = ranges::is_sorted(skipped) || ranges::is_sorted(skipped, std::greater{});
            if (ranges::count(diffs, true) == (report.size() - 2) && monotone) {
                return true;
            }
        }
        return false;
    };

    std::int32_t result1 = ranges::count(reports | views::transform(isSafe), true);
    std::int32_t result2 = ranges::count(reports | views::transform(isSafeDampened), true);

    std::println("First solution: {}", result1);
    std::println("Second solution: {}", result2);

    return 0;
}
