#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <fstream>

std::vector<std::string> strSplit(const std::string& str, const std::string& delim)
{
    std::vector<std::string> tokens;

    size_t begin = 0;
    size_t end = str.find(delim);
    while (end != std::string::npos)
    {
        tokens.push_back(str.substr(begin, end - begin));
        begin = end + delim.length();
        end = str.find(delim, begin);
    }
    tokens.push_back(str.substr(begin, end));

    return tokens;
}

bool contains(int64_t abegin, int64_t aend, int64_t bbegin, int64_t bend)
{
    int64_t begin = std::max(abegin, bbegin);
    int64_t end = std::min(aend, bend);
    return (abegin >= begin && aend <= end) || (bbegin >= begin && bend <= end);
}

bool overlaps(int64_t abegin, int64_t aend, int64_t bbegin, int64_t bend)
{
    int64_t begin = std::max(abegin, bbegin);
    int64_t end = std::min(aend, bend);
    return (begin <= end);
}

int main()
{
    int64_t tally1 = 0;
    int64_t tally2 = 0;

    std::string line;
    std::ifstream input("../../../2022/inputs/day4.txt");
    while(std::getline(input, line))
    {
        auto pair = strSplit(line, ",");
        auto first = strSplit(pair[0], "-");
        auto second = strSplit(pair[1], "-");
        tally1 += contains(std::stoi(first[0]), std::stoi(first[1]), std::stoi(second[0]), std::stoi(second[1]));
        tally2 += overlaps(std::stoi(first[0]), std::stoi(first[1]), std::stoi(second[0]), std::stoi(second[1]));
    }
    input.close();

    std::cout << tally1 << "\n";
    std::cout << tally2 << "\n";
}
