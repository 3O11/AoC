#include <iostream>
#include <fstream>
#include <cstdint>

int main()
{
    constexpr int64_t window = 14;
    std::string line;
    std::ifstream input("../../2022/inputs/day6.txt");
    std::getline(input, line);
    input.close();

    for (int64_t i = window - 1; i < line.length(); ++i)
    {
        bool unique = true;
        for (int64_t j = 0; j < window; ++j)
        {
            for (int64_t k = j + 1; k < window; ++k)
            {
                if (line[i - j] == line[i - k])
                {
                    unique = false;
                    break;
                }
            }
        }
        if (unique)
        {
            std::cout << i + 1 << "\n";
            return 0;
        }
    }
}
