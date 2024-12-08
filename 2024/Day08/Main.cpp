#include "InputGetter.hpp"
#include "Algo.hpp"

#include <algorithm>
#include <mdspan>
#include <print>
#include <ranges>
#include <vector>

struct Vec2i
{
    std::int32_t x;
    std::int32_t y;

    friend Vec2i operator- (Vec2i u) { return { .x = -u.x, .y = -u.y }; }

    friend Vec2i operator+ (Vec2i u, Vec2i v) { return { .x = u.x + v.x, .y = u.y + v.y }; }
    friend Vec2i operator- (Vec2i u, Vec2i v) { return { .x = u.x - v.x, .y = u.y - v.y }; }
};

int main()
{
    namespace ranges = std::ranges;
    namespace views = std::views;

    auto input = AOC2024::GetPuzzleInput(2024, 8);
    if (!input) { return 1; }

    Vec2i mapSize {
        .x = std::int32_t(input->find('\n')),
        .y = std::int32_t(ranges::count(*input, '\n'))
    };
    std::erase(*input, '\n');
    auto map = std::mdspan(input->data(), mapSize.x, mapSize.y);

    std::string charset = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    auto inBounds = [mapSize](Vec2i pos) {
        return (pos.x >= 0) && (pos.x < mapSize.x) && (pos.y >= 0) && (pos.y < mapSize.y);
    };

    auto vecFromIndex = [mapSize](std::size_t index) {
        return Vec2i{ .x = std::int32_t(index % mapSize.x), .y = std::int32_t(index / mapSize.x) };
    };

    std::int32_t result1 = [&input, mapSize, map, &charset, inBounds, vecFromIndex]() {
        std::string scratchData(mapSize.x * mapSize.y, '.');
        auto scratchMap = std::mdspan(scratchData.data(), mapSize.x, mapSize.y);

        auto setAntinode = [inBounds, scratchMap](Vec2i pos) {
            if (inBounds(pos)) {
                scratchMap[pos.y, pos.x] = '#';
            }
        };

        for (char ch : charset) {
            std::vector<std::size_t> occurences;

            std::size_t i = input->find(ch, i + 1);
            while (i != std::string::npos) {
                occurences.push_back(i);
                i = input->find(ch, i + 1);
            }

            AOC2024::Algo::Pairwise(occurences, [vecFromIndex, setAntinode](const auto& pair) {
                Vec2i u = vecFromIndex(pair.first);
                Vec2i v = vecFromIndex(pair.second);
                Vec2i diff = u - v;
                setAntinode(u + diff);
                setAntinode(v - diff);
            });
        }

        return ranges::count(scratchData, '#');
    }();


    std::int32_t result2 = [&input, mapSize, map, &charset, inBounds, vecFromIndex]() {
        std::string scratchData(mapSize.x * mapSize.y, '.');
        auto scratchMap = std::mdspan(scratchData.data(), mapSize.x, mapSize.y);

        auto setAntinodes = [inBounds, scratchMap](Vec2i pos, Vec2i diff) {
            if (inBounds(pos)) {
                scratchMap[pos.y, pos.x] = '#';
            }
            while (inBounds(pos + diff)) {
                pos = pos + diff;
                scratchMap[pos.y, pos.x] = '#';
            }
        };

        for (char ch : charset) {
            std::vector<std::size_t> occurences;

            std::size_t i = input->find(ch, i + 1);
            while (i != std::string::npos) {
                occurences.push_back(i);
                i = input->find(ch, i + 1);
            }

            AOC2024::Algo::Pairwise(occurences, [vecFromIndex, setAntinodes](const auto& pair) {
                Vec2i u = vecFromIndex(pair.first);
                Vec2i v = vecFromIndex(pair.second);
                Vec2i diff = u - v;
                setAntinodes(u, diff);
                setAntinodes(v, -diff);
            });
        }

        return ranges::count(scratchData, '#');
    }();

    std::println("First solution: {}", result1);
    std::println("Second solution: {}", result2);

    return 0;
}
