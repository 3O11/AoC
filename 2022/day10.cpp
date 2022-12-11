#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>
#include <iomanip>

#include "StringTools.hpp"

enum class Operation { nop, add, };

struct Instruction
{
    Operation op = Operation::nop;
    int64_t   duration = 1;
    int64_t   value = 0;
    int64_t   elapsed = 0;
};

int main ()
{
    int64_t cycle = 0;
    Instruction inFlight;
    int64_t regx  = 1;
    int64_t snaps = 0;

    std::string line;
    std::ifstream input("../../../2022/inputs/day10.txt");
    while (true)
    {
        if (inFlight.duration <= inFlight.elapsed)
        {
            if (!std::getline(input, line)) break;

            auto split = cc::StrSplit(line, " ");
            if (split[0] == "addx")
            {
                inFlight = {.op = Operation::add, .duration = 2, .value = std::stoi(split[1])};
            }
            if (split[0] == "noop")
            {
                inFlight = {.op = Operation::nop, .duration = 1};
            }
        }

        if (!((cycle - 20) % 40))
        {
            snaps += regx * cycle;
            //std::cout << std::setw(4) << cycle << " * " << std::setw(4) << regx <<  " = " << std::setw(4)  << regx * cycle << "\n";
        }
        else
        {
            //std::cout << std::setw(4) << cycle << " | " << std::setw(4) << regx <<  " = " << std::setw(4)  << regx * cycle << "\n";
        }

        std::cout << (std::abs(((cycle) % 40) - regx - 1) <= 1 ? "#" : ".");
        if (!((cycle - 1) % 40)) std::cout << "\n";

        if (inFlight.duration <= ++inFlight.elapsed)
        {
            switch (inFlight.op)
            {
            case Operation::add:
                regx += inFlight.value;
                break;
            case Operation::nop:
                break;
            default:
                std::cout << "This should never happen!\n";
                break;
            }
        }

        ++cycle;
    }
    input.close();

    std::cout << snaps << "\n";
}
