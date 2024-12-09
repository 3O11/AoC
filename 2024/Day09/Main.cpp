#include "InputGetter.hpp"
#include "Stopwatch.hpp"

#include <algorithm>
#include <print>
#include <ranges>
#include <vector>

int main()
{
    AOC2024::ScopedStopwatch s("AoC 2024 Day 9");

    namespace ranges = std::ranges;
    namespace views = std::views;

    auto input = AOC2024::GetPuzzleInput(2024, 9);
    if (!input) { return 1; }
    std::erase(*input, '\n');

    std::vector<std::uint16_t> unpackedDisk;
    std::vector<std::pair<std::size_t, std::uint8_t>> files;
    std::vector<std::pair<std::size_t, std::uint8_t>> freeSpaces;

    unpackedDisk.reserve(input->size() * 10);
    files.reserve(input->size());
    freeSpaces.reserve(input->size());

    bool file = true;
    std::uint16_t id = 0;
    for (char ch : *input) {
        std::uint8_t size = ch - '0';
        if (file) {
            files.push_back({unpackedDisk.size(), size});
            for (std::uint16_t i = 0; i < size; ++i) {
                unpackedDisk.push_back(id);
            }
            ++id;
        }
        else {
            if (size) {
                freeSpaces.push_back({unpackedDisk.size(), size});
            }
            for (std::uint16_t i = 0; i < size; ++i) {
                unpackedDisk.push_back(std::uint16_t(-1));
            }
        }
        file = !file;
    }

    std::int64_t result1 = [unpackedDisk]() mutable {
        auto isEmptyBlock = [](std::uint16_t item) { return item == std::uint16_t(-1); };
        auto isFileBlock = [](std::uint16_t item) { return item != std::uint16_t(-1); };

        auto inserter = ranges::find_if(unpackedDisk, isEmptyBlock);
        auto reader = ranges::find_if(views::reverse(unpackedDisk), isFileBlock);
        while ((inserter - unpackedDisk.begin()) < (unpackedDisk.size() - (reader - unpackedDisk.rbegin())) &&
                inserter != unpackedDisk.end() && reader != unpackedDisk.rend()) {
            *inserter = *reader;
            *reader = std::uint16_t(-1);
            inserter = std::find_if(inserter, unpackedDisk.end(), isEmptyBlock);
            reader = std::find_if(reader, unpackedDisk.rend(), isFileBlock);
        }

        auto filledBlocks = ranges::subrange(unpackedDisk.begin(), ranges::find(unpackedDisk, std::uint16_t(-1)));
        std::int64_t checksum = 0;
        for (auto [blockIndex, fileId] : filledBlocks | views::enumerate) {
            checksum += blockIndex * fileId;
        }
        return checksum;
    }();

    std::int64_t result2 = [&unpackedDisk, &files, &freeSpaces]() mutable {
        for (auto& [filePos, fileSize] : views::reverse(files)) {
            auto freeSpacePos = ranges::find_if(freeSpaces, [&fileSize](const auto& freeSpace) { return freeSpace.second >= fileSize; });
            if (freeSpacePos == freeSpaces.end() || freeSpacePos->first > filePos) {
                continue;
            }
            for (std::size_t i = 0; i < fileSize; ++i) {
                unpackedDisk[freeSpacePos->first + i] = unpackedDisk[filePos];
                unpackedDisk[filePos] = std::uint16_t(-1);
                ++filePos;
            }
            filePos = freeSpacePos->first;
            freeSpacePos->first += fileSize;
            freeSpacePos->second -= fileSize;
        }

        std::int64_t checksum = ranges::fold_left(unpackedDisk
                              | views::enumerate
                              | views::filter([](auto block) { return std::get<1>(block) != std::uint16_t(-1); }),
                              0ll, [](std::int64_t sum, auto block) { return sum + std::get<0>(block) * std::get<1>(block); });
        return checksum;
    }();

    std::println("First solution: {}", result1);
    std::println("Second solution: {}", result2);

    return 0;
}
