#include "InputGetter.hpp"

#include <algorithm>
#include <print>
#include <ranges>
#include <map>
#include <utility>
#include <vector>

int main()
{
    namespace ranges = std::ranges;
    namespace views = std::views;

    auto input = AOC2024::GetPuzzleInput(2024, 5);
    if (!input) { return 1; }

    auto parseRule = [](const auto& line) {
        auto nums = line
                  | views::split('|')
                  | views::transform([](const auto& num) { return std::stoi(ranges::to<std::string>(num)); });
        return std::pair<std::int32_t, std::int32_t>(*nums.begin(), *(nums | views::drop(1)).begin() );
    };

    auto rawRules = *input
                  | views::split('\n')
                  | views::filter([](const auto& line) { return ranges::contains(line, '|'); })
                  | views::transform(parseRule)
                  | ranges::to<std::vector<std::pair<std::int32_t, std::int32_t>>>();

    std::map<std::int32_t, std::vector<std::int32_t>> rules;
    for (auto [mustPrecede, mustFollow] : rawRules) {
        rules[mustFollow].push_back(mustPrecede);
    }

    auto parseUpdate = [](const auto& line) {
        return line
             | views::split(',')
             | views::transform([](const auto& num) { return std::stoi(ranges::to<std::string>(num)); });
    };

    auto updates = *input
                 | views::split('\n')
                 | views::filter([](const auto& line) { return ranges::contains(line, ','); })
                 | views::transform(parseUpdate)
                 | ranges::to<std::vector<std::vector<std::int32_t>>>();

    auto verifyUpdate = [&rules](const std::vector<std::int32_t>& update) {
        for (auto [index, num] : update | views::enumerate) {
            auto rule = rules.find(num);
            if (rule == rules.end()) {
                continue;
            }
            for (auto predecessor : rule->second) {
                if (ranges::contains(update | views::drop(index + 1), predecessor)) {
                    return false;
                }
            }
        }
        return true;
    };

    auto fixUpdate = [&rules](const std::vector<std::int32_t>& update) {
        auto fixCopy = update;
        auto cmp = [&rules](std::int32_t a, std::int32_t b) {
            auto rule = rules.find(a);
            if (rule == rules.end()) {
                return false;
            }
            return ranges::contains(rule->second, b);
        };
        ranges::sort(fixCopy, cmp);
        return fixCopy;
    };

    std::int32_t result1 = ranges::fold_left(updates
                         | views::filter(verifyUpdate)
                         | views::transform([](const auto& update) { return update[update.size() / 2]; }),
                         0, std::plus{});

    std::int32_t result2 = ranges::fold_left(updates
                         | views::filter([&verifyUpdate](const auto& update) { return !verifyUpdate(update); })
                         | views::transform(fixUpdate)
                         | views::transform([](const auto& update) { return update[update.size() / 2]; }),
                         0, std::plus{});

    std::println("First solution: {}", result1);
    std::println("Second solution: {}", result2);

    return 0;
}
