#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>

#include "StringTools.hpp"

void dbgPrintStacks(const std::vector<std::vector<char>>& stacks) {
    for (const auto& stack : stacks) {
        for (const auto& item : stack) {
            std::cout << item << " ";
        }
        std::cout << "\n";
    }
}

void dbgPrintCmd(int64_t count, int64_t from, int64_t to) {
    std::cout << "count: " << count << ", from: " << from << ", to: " << to << "\n";
}

void printTops(const std::vector<std::vector<char>>& stacks) {
    std::string tops;
    for (const auto& stack : stacks) {
        tops.append(std::string(1, stack.back()));
    }
    std::cout << tops << "\n";
}

std::vector<std::vector<char>> parseStacks(std::ifstream& input) {
    std::vector<std::vector<char>> stacks;
    std::string line;
    while(std::getline(input, line) && !line.starts_with(" 1")) {
        int64_t index = 0;
        while(index < line.length()) {
            if (line[index] == '[') {
                if (stacks.size() <= (index / 4)) {
                    stacks.resize((index / 4) + 1);
                }
                stacks[index / 4].insert(stacks[index / 4].begin(), line[index + 1]);
            }
            index += 4;
        }
    }
    return stacks;
}

int main()
{
    std::ifstream input("../../2022/inputs/day5.txt");
    auto stacks1 = parseStacks(input);
    auto stacks2 = stacks1;

    std::string line;
    std::getline(input, line); // Consume empty line
    while (std::getline(input, line)) {
        auto split = cc::StrSplit(line, " ");
        assert(split.size() == 6);
        int64_t count = std::stoll(split[1]);
        int64_t from = std::stoll(split[3]) - 1;
        int64_t to = std::stoll(split[5]) - 1;

        for (int64_t i = 0; i < count; ++i) {
            stacks1[to].push_back(stacks1[from].back());
            stacks1[from].pop_back();
        }

        stacks2[to].insert(stacks2[to].end(), stacks2[from].end() - count, stacks2[from].end());
        stacks2[from].erase(stacks2[from].end() - count, stacks2[from].end());
    }
    input.close();

    printTops(stacks1);
    printTops(stacks2);
}
