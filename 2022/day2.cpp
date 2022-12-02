#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

int64_t mod(int64_t x, int64_t m)
{
    return (x%m + m)%m;
}

int64_t evaluateMatch(int64_t p1, int64_t p2)
{
    if (p1 == p2) { return 3; }
    return mod(p1 - p2, 3) == 2 ? 6 : 0;
}

int64_t findSymbol(int64_t p1, int64_t strat)
{
    if (strat == 1) return p1;
    return mod(p1 - (strat == 0 ? 1 : 2), 3);
}

int main()
{
    int64_t score1 = 0;
    int64_t score2 = 0;

    std::ifstream input("../../2022/inputs/day2.txt");
    while(true)
    {
        char p1, p2;
        input >> p1 >> p2;
        if (input.eof()) break;

        score1 += (p2 - 'W');                            // Symbol score
        score1 += evaluateMatch((p1 - 'A'), (p2 - 'X')); // Match score

        int64_t symbol = findSymbol((p1 - 'A'), (p2 - 'X'));
        score2 += symbol + 1;
        score2 += evaluateMatch((p1 - 'A'), symbol);
    }
    input.close();

    std::cout << score1 << "\n";
    std::cout << score2 << "\n";
}
