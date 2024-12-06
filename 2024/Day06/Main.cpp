#include "InputGetter.hpp"

#include <algorithm>
#include <mdspan>
#include <print>
#include <ranges>
#include <utility>

enum class Direction : std::uint8_t
{
    Up    = 0x00,
    Right = 0x01,
    Down  = 0x02,
    Left  = 0x03,
};

std::optional<Direction> MakeDirection (char ch)
{
    switch (ch) {
        case '^': return Direction::Up;
        case '>': return Direction::Right;
        case 'v': return Direction::Down;
        case '<': return Direction::Left;
        default : return std::nullopt;
    }
}

char ToChar(Direction dir)
{
    switch (dir) {
        case Direction::Up   : return '^';
        case Direction::Right: return '>';
        case Direction::Down : return 'v';
        case Direction::Left : return '<';
    }
    std::unreachable();
}

bool Vertical(Direction dir)
{
    return dir == Direction::Up || dir == Direction::Down;
}

bool Horizontal(Direction dir)
{
    return dir == Direction::Left || dir == Direction::Right;
}

bool Opposite(Direction d1, Direction d2)
{
    return (d1 == Direction::Up    && d2 == Direction::Down )
        || (d1 == Direction::Down  && d2 == Direction::Up   )
        || (d1 == Direction::Left  && d2 == Direction::Right)
        || (d2 == Direction::Right && d2 == Direction::Left );
}

struct Position
{
    std::int32_t x;
    std::int32_t y;

    friend bool operator== (const Position& p1, const Position& p2)
    {
        return (p1.x == p2.x) && (p1.y == p2.y);
    }
};

struct Guard
{
    Position Pos;
    Direction Dir;

    Position Next () const
    {
        switch (Dir) {
            case Direction::Up   : return { .x = Pos.x,     .y = Pos.y - 1 };
            case Direction::Right: return { .x = Pos.x + 1, .y = Pos.y     };
            case Direction::Down : return { .x = Pos.x,     .y = Pos.y + 1 };
            case Direction::Left : return { .x = Pos.x - 1, .y = Pos.y     };
            default              : std::unreachable();
        };
    }

    void Move () { Pos = Next(); }
    void TurnRight () { Dir = Direction((std::to_underlying(Dir) + 1) % 4); }
};

int main()
{
    namespace ranges = std::ranges;
    namespace views = std::views;

    auto input = AOC2024::GetPuzzleInput(2024, 6);
    if (!input) { return 1; }

    std::int32_t mapWidth = input->find('\n');
    std::int32_t mapHeight = ranges::count(*input, '\n');
    std::erase(*input, '\n');
    std::string mapData = *input;
    auto map = std::mdspan(mapData.data(), mapWidth, mapHeight);

    auto resetMap = [&mapData, &input]() {
        mapData = *input;
    };

    auto mapIter = views::cartesian_product(
                       views::iota(0, mapHeight),
                       views::iota(0, mapWidth))
                 | views::transform([](const auto& coord) { return Position{ .x = std::get<1>(coord), .y = std::get<0>(coord) }; });

    auto gPos = ranges::find_if(mapIter, [&map](const auto& pos) { return MakeDirection(map[pos.y, pos.x]).has_value(); });
    if (gPos == mapIter.end()) { return 1; }
    auto gDir = MakeDirection(map[(*gPos).y, (*gPos).x]);
    Guard g { .Pos = *gPos, .Dir = *gDir };

    auto inBounds = [mapWidth, mapHeight](Position pos) {
        return (pos.x >= 0) && (pos.x < mapWidth) && (pos.y >= 0) && (pos.y < mapHeight);
    };

    auto hasObstacle = [inBounds, &map](Position pos) {
        return inBounds(pos) && (map[pos.y, pos.x] == '#' || map[pos.y, pos.x] == 'O');
    };

    std::int32_t result1 = [&map, &mapData, &resetMap, &inBounds, &hasObstacle, g]() mutable {
        auto mark = [&map, &g]() {
            map[g.Pos.y, g.Pos.x] = 'X';
        };

        while (inBounds(g.Pos)) {
            mark();
            while (hasObstacle(g.Next())) {
                g.TurnRight();
            }
            g.Move();
        }

        std::int32_t marked = ranges::count(mapData, 'X');
        resetMap();
        return marked;
    }();

    std::int32_t result2 = [&map, &resetMap, &mapIter, &inBounds, &hasObstacle, g]() mutable {
        auto resetGuard = [g](Guard& movedGuard) { movedGuard = g; };
        auto setObstacle = [&map] (Position pos) { map[pos.y, pos.x] = 'O'; };
        auto hideGuard = [&map] (Position pos) { map[pos.y, pos.x] = '.'; };

        auto mark = [&map, &hasObstacle, &g]() {
            char& field = map[g.Pos.y, g.Pos.x];
            auto fieldDir = MakeDirection(field);

            if (field == '.') {
                field = ToChar(g.Dir);
            }
            else if (fieldDir && Opposite(*fieldDir, g.Dir)) {
                field = Vertical(g.Dir) ? '|' : '-';
            }
            else if ((field == '-' && Vertical(g.Dir)) ||
                     (field == '|' && Horizontal(g.Dir))) {
                field = '+';
            }
            else if (fieldDir && *fieldDir != g.Dir && !Opposite(*fieldDir, g.Dir)) {
                field = '+';
            }
        };

        auto repeats = [&map, &inBounds, &hasObstacle, &g]() {
            if (!inBounds(g.Pos)) {
                return false;
            }
            auto dir = MakeDirection(map[g.Pos.y, g.Pos.x]);
            return dir && g.Dir == *dir;
        };

        std::int32_t loopCount = 0;
        for (Position obstacle : mapIter) {
            if (hasObstacle(obstacle) || g.Pos == obstacle) {
                continue;
            }
            setObstacle(obstacle);
            hideGuard(g.Pos);

            bool hasLoop = false;
            while (inBounds(g.Pos) && !hasLoop) {
                if (repeats()) {
                    ++loopCount;
                    hasLoop = true;
                }
                mark();
                while (hasObstacle(g.Next())) {
                    g.TurnRight();
                }
                g.Move();
            }

            resetGuard(g);
            resetMap();
        }
        return loopCount;
    }();

    std::println("First solution: {}", result1);
    std::println("Second solution: {}", result2);

    return 0;
}
