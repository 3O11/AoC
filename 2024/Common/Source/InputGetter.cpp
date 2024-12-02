#include "InputGetter.hpp"
#include "Core.hpp"

#include <cpr/cpr.h>

#include <filesystem>
#include <format>
#include <fstream>
#include <iterator>
#include <optional>
#include <sstream>
#include <system_error>

namespace AOC2024
{
    namespace fs = std::filesystem;

    namespace
    {
        std::expected<std::string, GetInputFailure> LoadSessionCookie()
        {
            std::ifstream sessionCookieInput("../session_cookie.txt");

            if (!sessionCookieInput) {
                return std::unexpected(GetInputFailure::NoSessionCookie);
            }

            return std::string(
                std::istreambuf_iterator<char>(sessionCookieInput),
                std::istreambuf_iterator<char>{}
            );
        }

        bool CachePuzzleInput(uint32_t year, uint32_t day, const std::string& input)
        {
            std::error_code ec;

            if (!fs::exists("../inputs", ec)) {
                fs::create_directories("../inputs", ec);
                if (ec) {
                    return false;
                }
            }

            std::ofstream inputCache(std::format("../inputs/{}D{}.txt", year, day), std::ios::binary | std::ios::trunc);
            if (!inputCache) {
                return false;
            }

            inputCache << input;
            inputCache.close();
            return true;
        }

        std::optional<std::string> LoadPuzzleInput(uint32_t year, uint32_t day)
        {
            std::ifstream inputCache(std::format("../inputs/{}D{}.txt", year, day), std::ios::binary);
            if (!inputCache) {
                return std::nullopt;
            }

            std::stringstream inputBuffer;
            inputBuffer << inputCache.rdbuf();
            return inputBuffer.str();
        }
    }

    std::expected<std::string, GetInputFailure> GetPuzzleInput(uint32_t year, uint32_t day)
    {
        auto cachedInput = LoadPuzzleInput(year, day);
        if (cachedInput) {
            return *cachedInput;
        }

        auto sessionCookie = LoadSessionCookie();
        if (!sessionCookie) {
            return sessionCookie;
        }

        cpr::Response sponse = cpr::Get(
            cpr::Url(std::format("https://adventofcode.com/{}/day/{}/input", year, day)),
            cpr::Cookie("session", sessionCookie.value(), ".adventofcode.com")
        );

        if (!cachedInput) {
            CachePuzzleInput(year, day, sponse.text);
        }

        if (sponse.status_code == 200) {
            return sponse.text;
        }
        else if (sponse.status_code == 400) {
            return std::unexpected(GetInputFailure::InvalidCookie);
        }
        else {
            return std::unexpected(GetInputFailure::RequestFailed);
        }
    }
}
