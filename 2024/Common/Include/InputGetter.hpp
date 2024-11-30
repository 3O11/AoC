#ifndef AOC_2024_COMMON_INPUT_GETTER_HPP
#define AOC_2024_COMMON_INPUT_GETTER_HPP

#include "Core.hpp"

#include <string>

namespace AOC2024
{
    enum class GetInputFailure
    {
        NoSessionCookie,
        InvalidCookie,
        RequestFailed,
    };

    std::expected<std::string, GetInputFailure> GetPuzzleInput(uint32_t year, uint32_t day);
}

#endif //AOC_2024_COMMON_INPUT_GETTER_HPP
