#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdint>
#include <set>
#include <algorithm>
#include <iterator>

int main()
{
    int64_t sum1 = 0;
    int64_t sum2 = 0;

    int64_t linenum = 0;
    std::string line, prev1, prev2;
    std::ifstream input("../../../2022/inputs/day3.txt");
    while (std::getline(input, line))
    {
        std::set<char> checked;
        for (int64_t i = line.size() / 2; i < line.size(); ++i)
        {
            for (int64_t j = 0; j < line.size() / 2; ++j)
            {
                if (line[i] == line[j] && !checked.contains(line[i]))
                {
                    sum1 += 1 + ((line[i] <= 'Z') ? line[i] - 'A' + 26 : line[i] - 'a');
                    checked.insert(line[i]);
                    break;
                }
            }
        }

        if(linenum++ % 3 == 2)
        {
            std::vector<char> temp1;
            std::vector<char> temp2;
            std::sort(line.begin(), line.end());
            std::sort(prev1.begin(), prev1.end());
            std::sort(prev2.begin(), prev2.end());
            std::set_intersection(line.begin(),  line.end(),  prev1.begin(), prev1.end(), std::back_inserter(temp1));
            std::set_intersection(prev2.begin(), prev2.end(), temp1.begin(), temp1.end(), std::back_inserter(temp2));
            sum2 += 1 + ((temp2[0] <= 'Z') ? temp2[0] - 'A' + 26 : temp2[0] - 'a');
        }

        prev2 = prev1;
        prev1 = line;
    }
    input.close();

    std::cout << sum1 << "\n";
    std::cout << sum2 << "\n";
}
