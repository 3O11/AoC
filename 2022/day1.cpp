#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdint>

int main()
{
    std::vector<int64_t> elves;

    std::fstream input("../../2022/inputs/day1.txt");
    std::string line;
    int64_t tally = 0;
    while(std::getline(input, line))
    {
        if (line == "")
        {
            elves.push_back(tally);
            tally = 0;
            continue;
        }

        tally += std::stoi(line);
    }
    input.close();

    std::sort(elves.rbegin(), elves.rend());
    std::cout << elves[0] << "\n";
    std::cout << elves[0] + elves[1] + elves[2] << "\n";
}
