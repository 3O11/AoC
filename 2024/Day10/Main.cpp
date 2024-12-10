#include "InputGetter.hpp"
#include "Stopwatch.hpp"

#include <algorithm>
#include <mdspan>
#include <print>
#include <ranges>
#include <unordered_set>
#include <utility>
#include <vector>

enum class Direction : std::uint8_t
{
    Up,
    Down,
    Left,
    Right,
};

Direction Opposite(Direction dir)
{
    switch (dir) {
        case Direction::Up   : return Direction::Down  ;
        case Direction::Down : return Direction::Up    ;
        case Direction::Left : return Direction::Right ;
        case Direction::Right: return Direction::Left  ;
    }
    std::unreachable();
}

struct Vec2i
{
    std::int32_t x;
    std::int32_t y;

    static Vec2i FromDirection(Direction dir)
    {
        switch (dir) {
            case Direction::Up   : return { .x =  0, .y = -1 };
            case Direction::Down : return { .x =  0, .y =  1 };
            case Direction::Left : return { .x = -1, .y =  0 };
            case Direction::Right: return { .x =  1, .y =  0 };
        }
        std::unreachable();
    }

    friend Vec2i operator- (Vec2i u) { return { .x = -u.x, .y = -u.y }; }

    friend Vec2i operator+ (Vec2i u, Vec2i v) { return { .x = u.x + v.x, .y = u.y + v.y, }; }
    friend Vec2i operator- (Vec2i u, Vec2i v) { return { .x = u.x - v.x, .y = u.y - v.y, }; }
};

int main()
{
    AOC2024::ScopedStopwatch s("AoC 2024 Day 10");

    namespace ranges = std::ranges;
    namespace views = std::views;

    auto input = AOC2024::GetPuzzleInput(2024, 10);
    if (!input) { return 1; }

    Vec2i mapSize = {
        .x = std::int32_t(input->find('\n')),
        .y = std::int32_t(ranges::count(*input, '\n')),
    };
    std::erase(*input, '\n');
    auto map = std::mdspan(input->data(), mapSize.x, mapSize.y);

    auto vecFromIndex = [mapSize](std::size_t index) {
        return Vec2i{ .x = std::int32_t(index % mapSize.x), .y = std::int32_t(index / mapSize.y), };
    };

    auto indexFromVec = [mapSize](Vec2i vec) {
        return std::size_t(vec.x) + std::size_t(vec.y) * std::size_t(mapSize.x);
    };

    auto inBounds = [mapSize](Vec2i index) {
        return (index.x >= 0) && (index.x < mapSize.x) && (index.y >= 0) && (index.y < mapSize.y);
    };

    std::int64_t result1 = 0;
    std::int64_t result2 = 0;

    auto trailStarts = *input
                     | views::enumerate
                     | views::filter([](const auto& item) { return std::get<1>(item) == '0'; })
                     | views::transform([](const auto& item) { return std::get<0>(item); });

    for (auto index : trailStarts) {
        struct TrailExploreItem
        {
            std::size_t Index;
            Direction Dir;
            char PrevHeight;
        };

        std::unordered_set<std::size_t> visitedTrailEnds;
        std::vector<TrailExploreItem> explorationStack {
            { .Index = std::size_t(index), .Dir = Direction::Up,    .PrevHeight = '0', },
            { .Index = std::size_t(index), .Dir = Direction::Down,  .PrevHeight = '0', },
            { .Index = std::size_t(index), .Dir = Direction::Left,  .PrevHeight = '0', },
            { .Index = std::size_t(index), .Dir = Direction::Right, .PrevHeight = '0', },
        };

        while (explorationStack.size()) {
            auto [index, dir, prev] = explorationStack.back();
            explorationStack.pop_back();

            Vec2i newPos = vecFromIndex(index) + Vec2i::FromDirection(dir);
            std::size_t newIndex = indexFromVec(newPos);
            if (!inBounds(newPos) || (map[newPos.y, newPos.x] - prev) != 1) {
                continue;
            }

            if (map[newPos.y, newPos.x] == '9') {
                if (!visitedTrailEnds.contains(newIndex)) {
                    ++result1;
                    visitedTrailEnds.insert(newIndex);
                }
                ++result2;
                continue;
            }

            for (auto newDir : { Direction::Up, Direction::Down, Direction::Left, Direction::Right, }) {
                if (newDir != Opposite(dir)) {
                    explorationStack.push_back({
                        .Index = newIndex,
                        .Dir = newDir,
                        .PrevHeight = map[newPos.y, newPos.x],
                    });
                }
            }
        }
    }

    std::println("First solution: {}", result1);
    std::println("Second solution: {}", result2);

    return 0;
}
