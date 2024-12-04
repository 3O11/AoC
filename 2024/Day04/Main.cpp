#include "InputGetter.hpp"

#include <print>
#include <ranges>
#include <string>

int main()
{
    namespace views = std::views;

    auto input = AOC2024::GetPuzzleInput(2024, 4);
    if (!input) { return 1; }

    std::size_t offset = input->find('\n');
    std::erase(*input, '\n');

    auto xmas = [](const std::string& str) {
        return str == "XMAS" || str == "SAMX";
    };

    auto x_mas = [](const std::string& str) {
        return str == "SSAMM" | str == "MMASS" || str == "MSAMS" || str == "SMASM";
    };

    auto makeXmasCandidate = [&input] (std::size_t index, std::size_t offset) {
        return std::string {
            (*input)[index],
            (*input)[index + offset],
            (*input)[index + offset * 2],
            (*input)[index + offset * 3],
        };
    };

    auto makeX_masCandidate = [&input, &offset] (std::size_t index) {
        return std::string {
            (*input)[index],
            (*input)[index + 2],
            (*input)[index + offset + 1],
            (*input)[index + offset * 2],
            (*input)[index + 2 + offset * 2],
        };
    };

    std::int32_t result1 = 0;
    std::int32_t result2 = 0;
    for (std::size_t index : views::iota(0, std::int32_t(input->size()))) {
        std::size_t mod = index % offset;
        if (mod < (offset - 3) && index + 3 < input->size()) {
            result1 += xmas(makeXmasCandidate(index, 1));
        }
        if (index + 3 * offset < input->size()) {
            result1 += xmas(makeXmasCandidate(index, offset));
        }
        if (mod >= 3 && index + 3 * (offset - 1) < input->size()) {
            result1 += xmas(makeXmasCandidate(index, offset - 1));
        }
        if (mod < (offset - 3) && index + 3 * (offset + 1) < input->size()) {
            result1 += xmas(makeXmasCandidate(index, offset + 1));
        }

        if (mod < (offset - 2) && index + 2 + offset * 2 < input->size()) {
            result2 += x_mas(makeX_masCandidate(index));
        }
    }

    std::println("First solution: {}", result1);
    std::println("Second solution: {}", result2);

    return 0;
}
