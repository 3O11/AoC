#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <cstdint>
#include <vector>

std::string buildPath(const std::vector<std::string>& dirs)
{
    if (!dirs.size()) {
        return "/";
    } else {
        std::string path;
        for (auto&& dir : dirs) {
            path.append("/").append(dir);
        }
        return path;
    }
}

int main()
{
    std::unordered_map<std::string, int64_t> dirSizes;
    std::vector<std::string> path;

    std::string line;
    std::ifstream input("../../2022/inputs/day7.txt");
    while (std::getline(input, line))
    {
        if (line[0] == '$')
        {
            if (line.substr(2, 2) == "cd")
            {
                std::string targetDir = line.substr(5);
                if (targetDir == "..")
                {
                    path.pop_back();
                }
                else if (targetDir == "/")
                {
                    path.clear();
                }
                else
                {
                    path.push_back(targetDir);
                }
            }
            // else starts with ls, we don't need to worry about that
        }
        else if (std::isdigit(line[0]))
        {
            int64_t itemSize = std::stoi(line);
            for (int64_t i = 0; i <= path.size(); ++i)
            {
                dirSizes[buildPath(std::vector<std::string>(path.begin(), path.begin() + i))] += itemSize;
            }
        }
        // only dir <name> remains, we do not need to parse that
    }
    input.close();

    int64_t total = 0;

    int64_t neededSpace = 30'000'000 - (70'000'000 - dirSizes["/"]);
    std::string candidateDir;
    int64_t candidateSize = INT64_MAX;
    for (auto&& [dir, size] : dirSizes)
    {
        if (size < 100'000) { total += size; }

        if (size >= neededSpace && size < candidateSize)
        {
            candidateSize = size;
            candidateDir = dir;
        }
    }

    std::cout << total << "\n";
    std::cout << candidateDir << ": " << candidateSize << "\n";
}
