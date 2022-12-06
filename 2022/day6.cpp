#include <iostream>
#include <fstream>
#include <cstdint>
#include <set>

int64_t findUniqueSubstr(const std::string& str, int64_t length)
{
    for (int64_t i = length - 1; i < str.length(); ++i) {
        bool unique = true;
        for (int64_t j = 0; j < length && unique; ++j) {
            for (int64_t k = j + 1; k < length; ++k) {
                if (str[i - j] == str[i - k]) {
                    unique = false;
                    break;
                }
            }
        }
        if (unique) {
            return i + 1;   
        }
    }
    return -1;
}

int64_t findUniqueSubstr2(const std::string& str, int64_t length)
{
    for (int64_t i = length; i < str.length(); ++i) {
        if (std::set(str.begin() + i - length, str.begin() + i).size() == str.substr(i - length + 1, length).size())
            return i;
    }
    return -1;
}

int main()
{
    std::string line;
    std::ifstream input("../../2022/inputs/day6.txt");
    std::getline(input, line);
    input.close();
    std::cout << findUniqueSubstr(line, 4) << "\n";
    std::cout << findUniqueSubstr(line, 14) << "\n";
}
