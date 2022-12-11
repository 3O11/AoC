#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

#include "StringTools.hpp"

struct Monkey
{
    char op = '+';
    int64_t opValue = 0;
    int64_t divTest = 0;
    int64_t testPassDest = 0;
    int64_t testFailDest = 0;
    std::vector<int64_t> items;
    int64_t inspected = 0;
};

int main ()
{
    constexpr int64_t maxRounds1 = 20;
    constexpr int64_t maxRounds2 = 10000;
    std::vector<Monkey> monkeys1;
    std::vector<Monkey> monkeys2;

    std::string line;
    std::ifstream input("../../../2022/inputs/day11.txt");
    while (std::getline(input, line))
    {
        std::getline(input, line);
        std::vector<std::string> strItems = cc::StrSplit(line.substr(17), ", ");
        std::vector<int64_t> items;
        std::transform(strItems.begin(), strItems.end(), std::back_inserter(items), [](const std::string& strItem){ return std::stoll(strItem); });
        std::getline(input, line);
        char op = line[23];
        int64_t opValue = line.ends_with("old") ? -1 : std::stoll(cc::StrSplit(line, " ").back());
        std::getline(input, line);
        int64_t divTest = std::stoll(cc::StrSplit(line, " ").back());
        std::getline(input, line);
        int64_t testPassDest = std::stoll(cc::StrSplit(line, " ").back());
        std::getline(input, line);
        int64_t testFailDest = std::stoll(cc::StrSplit(line, " ").back());
        monkeys1.push_back({.op = op, .opValue = opValue, .divTest = divTest, .testPassDest = testPassDest, .testFailDest = testFailDest, .items = items});
        std::getline(input, line); // Consume empty line
    }
    input.close();
    monkeys2 = monkeys1;

    for (int64_t round = 0; round < maxRounds1; ++round) 
    {
        int64_t i = 0;
        for (auto& monkey : monkeys1)
        {
            //std::cout << "Monkey " << i++ << ":\n";
            while (monkey.items.size())
            {
                int64_t item = *monkey.items.begin();
                monkey.items.erase(monkey.items.begin());
                //std::cout << "  Monkey inspects an item with a worry level of " << item << ".\n";

                int64_t worry = 0;
                int64_t opVal = monkey.opValue == -1 ? item : monkey.opValue;
                switch(monkey.op)
                {
                case '+':
                    worry = item + opVal;
                    //std::cout << "    Worry level increases by " << opVal << " to " << worry << ".\n";
                    break;
                case '*':
                    worry = item * opVal;
                    //std::cout << "    Worry level is multiplied by " << opVal << " to " << worry << ".\n";
                    break;
                }

                //std::cout << "    Monkey gets bored with item. Worry level is divided by 3 to " << worry / 3 << ".\n";
                if (!((worry / 3) % monkey.divTest))
                {
                    monkeys1[monkey.testPassDest].items.push_back(worry / 3);
                    //std::cout << "    Current worry level is not divisible by " << monkey.divTest << ".\n";
                    //std::cout << "    Item with worry level " << worry / 3 << " is thrown to monkey " << monkey.testPassDest << ".\n";
                }
                else
                {
                    monkeys1[monkey.testFailDest].items.push_back(worry / 3);
                    //std::cout << "    Current worry level is not divisible by " << monkey.divTest << ".\n";
                    //std::cout << "    Item with worry level " << worry / 3 << " is thrown to monkey " << monkey.testFailDest << ".\n";
                }

                monkey.inspected++;
            }
        }
    }

    for (int64_t round = 0; round < maxRounds2; ++round)
    {
        std::cout << "Round: " << round << "\n";
        for (auto& monkey : monkeys2)
        {
            while (monkey.items.size())
            {
                int64_t item = *monkey.items.begin();
                monkey.items.erase(monkey.items.begin());

                int64_t worry = 0;
                int64_t opVal = monkey.opValue == -1 ? item : monkey.opValue;
                switch(monkey.op)
                {
                case '+':
                    worry = item + opVal;
                    break;
                case '*':
                    worry = item * opVal;
                    break;
                }

                if (!(worry % monkey.divTest))
                {
                    monkeys2[monkey.testPassDest].items.push_back(worry);
                }
                else
                {
                    monkeys2[monkey.testFailDest].items.push_back(worry);
                }

                monkey.inspected++;
            }
        }
    }

    int64_t max = 0, runnerUp = 0;
    for (auto& monkey : monkeys1)
    {
        if (monkey.inspected > max)
        {
            runnerUp = max;
            max = monkey.inspected;
        }
        else if (monkey.inspected > runnerUp)
        {
            runnerUp = monkey.inspected;
        }
    }
    std::cout << "Monke biz 1: " << max * runnerUp << "\n";
    max = 0;
    runnerUp = 0;
    for (auto& monkey : monkeys2)
    {
        if (monkey.inspected > max)
        {
            runnerUp = max;
            max = monkey.inspected;
        }
        else if (monkey.inspected > runnerUp)
        {
            runnerUp = monkey.inspected;
        }
    }
    std::cout << "Monke biz 2: " << max * runnerUp << "\n";
}
