#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <iomanip>

void dbgPrintMap(const std::vector<int8_t>& map, int64_t width, int64_t height, int64_t xmark = -1, int64_t ymark = -1)
{
    for (int64_t y = 0; y < height; ++y) {
        for (int64_t x = 0; x < width; ++x) {
            if (x == xmark && y == ymark) {
                std::cout << "X";
                continue;
            }

            std::cout << char(map[x + y * width] + '0');
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

bool checkVisibility(const std::vector<int8_t>& map, int64_t width, int64_t height, int64_t x, int64_t y)
{
    if (x == 0 || y == 0 || x == width - 1 || y == height - 1) { return true; }

    int64_t xr = x; bool xr_vis = true; while (++xr <  width ) { xr_vis = xr_vis && (map[x + y * height] > map[xr + y  * height]); }
    int64_t xl = x; bool xl_vis = true; while (--xl >= 0     ) { xl_vis = xl_vis && (map[x + y * height] > map[xl + y  * height]); }
    int64_t yd = y; bool yd_vis = true; while (++yd <  height) { yd_vis = yd_vis && (map[x + y * height] > map[x  + yd * height]); }
    int64_t yu = y; bool yu_vis = true; while (--yu >= 0     ) { yu_vis = yu_vis && (map[x + y * height] > map[x  + yu * height]); }
    
    return xr_vis || xl_vis || yd_vis || yu_vis;
}

int64_t scenicScore(const std::vector<int8_t>& map, int64_t width, int64_t height, int64_t x, int64_t y)
{
    if (x == 0 || y == 0 || x == width - 1 || y == height - 1) { return true; }

    int64_t xr = x; int64_t xr_sc = 0; while (++xr <  width ) { xr_sc++; if(map[x + y * height] <= map[xr + y  * height]) { break; } }
    int64_t xl = x; int64_t xl_sc = 0; while (--xl >= 0     ) { xl_sc++; if(map[x + y * height] <= map[xl + y  * height]) { break; } }
    int64_t yd = y; int64_t yd_sc = 0; while (++yd <  height) { yd_sc++; if(map[x + y * height] <= map[x  + yd * height]) { break; } }
    int64_t yu = y; int64_t yu_sc = 0; while (--yu >= 0     ) { yu_sc++; if(map[x + y * height] <= map[x  + yu * height]) { break; } }

    return xr_sc * xl_sc * yd_sc * yu_sc;
}

int main()
{
    int64_t width = 0;
    int64_t height = 0;
    std::vector<int8_t> map;

    std::string line;
    std::ifstream input("../../2022/inputs/day8.txt");
    while(std::getline(input, line))
    {
        height++;
        width = line.size();
        map.insert(map.end(), line.begin(), line.end());
    }
    input.close();
    std::for_each(map.begin(), map.end(), [](int8_t& tree) { tree -= '0'; });

    int64_t visibleCount = 0;
    int64_t scenicCount = 0;
    for (int64_t y = 0; y < height; ++y)
    {
        for (int64_t x = 0; x < width; ++x)
        {
            visibleCount += checkVisibility(map, width, height, x, y);
            scenicCount = std::max(scenicCount, scenicScore(map, width, height, x, y));
        }
    }

    std::cout << visibleCount << "\n";
    std::cout << scenicCount << "\n";
}
