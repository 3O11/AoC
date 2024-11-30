#include "InputGetter.hpp"
#include "Core.hpp"

#include <__expected/unexpect.h>
#include <__expected/unexpected.h>
#include <cpr/cpr.h>

#include <format>
#include <fstream>
#include <iterator>

namespace AOC2024
{
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
    }

    std::expected<std::string, GetInputFailure> GetPuzzleInput(uint32_t year, uint32_t day)
    {
        auto sessionCookie = LoadSessionCookie();

        if (!sessionCookie) {
            return sessionCookie;
        }

        cpr::Response sponse = cpr::Get(
            cpr::Url(std::format("https://adventofcode.com/{}/day/{}/input", year, day)),
            cpr::Cookie("session", sessionCookie.value(), ".adventofcode.com")
        );

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
