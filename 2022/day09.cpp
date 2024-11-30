#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <iomanip>

#include "StringTools.hpp"

struct Vec2i
{
    uint64_t ToInt() { return uint64_t(x) | (uint64_t(y) << 32); }
    int32_t Max() { return std::max(x, y); }
    int32_t Min() { return std::min(x, y); }

    int32_t x = 0;
    int32_t y = 0;
};
static Vec2i  operator+  (const Vec2i& u, const Vec2i& v) { return {u.x + v.x, u.y + v.y}; }
static Vec2i  operator-  (const Vec2i& u, const Vec2i& v) { return {u.x - v.x, u.y - v.y}; }
static Vec2i  operator*  (const Vec2i& u, int32_t s     ) { return {u.x * s, u.y * s}; }
static Vec2i& operator+= (      Vec2i& u, const Vec2i& v) { u.x += v.x; u.y += v.y; return u; }
static Vec2i  operator-  (const Vec2i& u)                 { return {-u.x, -u.y}; }
std::ostream& operator<< (std::ostream& out, Vec2i u)     { out << "{" << std::setw(3) << u.x << ", " << std::setw(3) << u.y << "}"; return out; }

void moveTail(Vec2i& tail, const Vec2i& head)
{
    auto delta = tail - head;
    if (std::abs(delta.x) == 2)
    {
        delta.x += (delta.x < 0) ? 1 : -1;
        tail += -delta;
    }
    else if (std::abs(delta.y) == 2)
    {
        delta.y += (delta.y < 0) ? 1 : -1;
        tail += -delta;
    }
}

int main()
{
    std::map<char, Vec2i> move{ { 'U', {0, 1} }, { 'D', {0, -1} }, { 'L', {1, 0} }, { 'R', {-1, 0} } };
    std::set<uint64_t> visited;
    Vec2i head;
    Vec2i tail;
    visited.insert(tail.ToInt());

    std::string line;
    std::ifstream input("../../2022/inputs/day09.txt");
    while (std::getline(input, line))
    {
        auto split = cc::StrSplit(line, " ");
        for (int64_t i = 0; i < std::stoll(split[1]); ++i)
        {
            head += move[split[0][0]];
            moveTail(tail, head);
            visited.insert(tail.ToInt());
            std::cout << split[0] << " " << move[split[0][0]] << " " << head << " " << tail << " " << tail.ToInt() << "\n";
        }
    }
    input.close();

    std::cout << visited.size() << "\n";
}
