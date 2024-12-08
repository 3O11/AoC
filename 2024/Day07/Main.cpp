#include "InputGetter.hpp"

#include <algorithm>
#include <print>
#include <ranges>
#include <vector>

int main()
{
    namespace ranges = std::ranges;
    namespace views = std::views;

    auto input = AOC2024::GetPuzzleInput(2024, 7);
    if (!input) { return 1; }

    auto parseLine = [](const auto& line) {
        auto parseNumberList = [](const auto& list) {
            return list
                 | views::split(' ')
                 | views::transform([](const auto& item) { return ranges::to<std::string>(item); })
                 | views::filter([](const std::string& item) { return item.size(); })
                 | views::transform([](const std::string& item) { return std::stoll(item); })
                 | ranges::to<std::vector<std::int64_t>>();
        };

        auto splitLine = line
                       | views::split(':');

        return std::pair<std::int64_t, std::vector<std::int64_t>>(
            std::stoll(ranges::to<std::string>(*splitLine.begin())),
            parseNumberList(*(splitLine | views::drop(1)).begin())
        );
    };

    auto pairs = *input
               | views::split('\n')
               | views::transform([](const auto& line) { return ranges::to<std::string>(line); })
               | views::filter([](const auto& line) { return line.size(); })
               | views::transform(parseLine)
               | ranges::to<std::vector>();

    std::int64_t result1 = [&pairs]() {
        auto canEqual = [](const auto& pair) {
            if (pair.second.size() > 64) { return false; }
            auto evaluate = [](const std::vector<std::int64_t>& items, std::int64_t bits) {
                auto applyOp = [bits](const auto& l, const auto& r) {
                    std::int64_t lnum = std::get<1>(l);
                    std::int64_t rnum = std::get<1>(r);
                    return std::make_pair(0, (bits & (1 << std::get<0>(r))) ? lnum * rnum : lnum + rnum);
                };
                return ranges::fold_left(items
                     | views::drop(1)
                     | views::enumerate,
                     std::make_pair(0, items[0]), applyOp).second;
            };

            std::uint64_t maxValue = (1ull << (pair.second.size() - 1));
            for (std::uint64_t ops = 0; ops < maxValue; ++ops) {
                if (evaluate(pair.second, ops) == pair.first) {
                    return true;
                }
            }
            return false;
        };

        return ranges::fold_left(pairs
             | views::filter(canEqual)
             | views::transform([](const auto& pair) { return pair.first; }),
             0, std::plus{});
    }();

    std::int64_t result2 = [&pairs]() {
        enum class Op : std::uint8_t { Add = 0x00, Mul = 0x01, Cat = 0x02, };

        auto canEqual = [](const auto& pair) {
            auto evaluate = [](const std::vector<std::int64_t>& items, const std::vector<Op>& ops) {
                auto applyOp = [&ops](const auto& l, const auto& r) {
                    auto cat = [](std::int64_t l, std::int64_t r) {
                        std::int64_t mul = 1;
                        std::int64_t rc = r;
                        while (rc > 0) {
                            mul *= 10;
                            rc /= 10;
                        }
                        return l * mul + r;
                    };

                    std::int64_t lnum = std::get<1>(l);
                    std::int64_t rnum = std::get<1>(r);
                    switch (ops[std::get<0>(r)]) {
                        case Op::Add: return std::make_pair(0, lnum + rnum);
                        case Op::Mul: return std::make_pair(0, lnum * rnum);
                        case Op::Cat: return std::make_pair(0, cat(lnum, rnum));
                    };
                };
                return ranges::fold_left(items
                     | views::drop(1)
                     | views::enumerate,
                     std::make_pair(0, items[0]), applyOp).second;
            };

            auto incOps = [](std::vector<Op>& ops) {
                for (const auto& [i, op] : ops | views::enumerate) {
                    op = Op((std::to_underlying(op) + 1) % 3);
                    if (op != Op::Add) {
                        return true;
                    }
                }
                return false;
            };

            std::vector<Op> ops(pair.second.size(), Op::Add);
            while (incOps(ops)) {
                if (evaluate(pair.second, ops) == pair.first) {
                    return true;
                }
            }
            return false;
        };

        return ranges::fold_left(pairs
             | views::filter(canEqual)
             | views::transform([](const auto& pair) { return pair.first; }),
             0, std::plus{});
    }();

    std::println("First solution: {}", result1);
    std::println("Second solution: {}", result2);

    return 0;
}
