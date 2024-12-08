#ifndef AOC_2024_COMMON_PAIRS_HPP
#define AOC_2024_COMMON_PAIRS_HPP

#include <ranges>
#include <utility>

namespace AOC2024
{
    namespace Algo
    {
        template <std::ranges::input_range RangeType, typename FuncType>
        constexpr
        void Pairwise(RangeType&& range, FuncType func)
        {
            for (auto i = std::ranges::begin(range), end = std::ranges::end(range); i != end; ++i) {
                auto j = i;
                for (++j; j != end; ++j) {
                    func(std::make_pair(*i, *j));
                }
            }
        }
    }
}

#endif //AOC_2024_COMMON_PAIRS_HPP
