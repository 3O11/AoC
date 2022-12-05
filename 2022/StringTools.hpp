#ifndef _CC_STRING_TOOLS_HPP
#define _CC_STRING_TOOLS_HPP

// #include "Base/Commonh.h"

namespace cc
{
    [[maybe_unused]]
    std::string& StrLtrim(std::string& str)
    {
        str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
        return str;
    }

    [[maybe_unused]]
    std::string& StrRtrim(std::string& str)
    {
        str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), str.end());
        return str;
    }

    [[maybe_unused]]
    std::string& StrTrim(std::string& str)
    {
        StrLtrim(str);
        StrRtrim(str);
        return str;
    }

    [[nodiscard]]
    std::string StrLtrim(std::string_view str)
    {
        auto trimmed = std::string(str);
        StrLtrim(trimmed);
        return trimmed;
    }

    [[nodiscard]]
    std::string StrRtrim(std::string_view str)
    {
        auto trimmed = std::string(str);
        StrRtrim(trimmed);
        return trimmed;
    }

    [[nodiscard]]
    std::string StrTrim(std::string_view str)
    {
        auto trimmed = std::string(str);
        StrLtrim(trimmed);
        StrRtrim(trimmed);
        return trimmed;
    }

    enum class StrSplitOpts : uint32_t
    {
        None        = 0x00,
        RemoveEmpty = 0x01,
        Trim        = 0x02,
    };

    template <StrSplitOpts opts = StrSplitOpts::None>
    [[nodiscard]]
    inline std::vector<std::string> StrSplit(std::string_view str, std::string_view delim)
    {
        std::vector<std::string> tokens;

        size_t begin = 0;
        size_t end = str.find(delim);
        while (end != std::string::npos)
        {
            auto token = std::string(str.substr(begin, end - begin));
            if constexpr (uint32_t(opts) & uint32_t(StrSplitOpts::Trim))
            {
                StrTrim(token);
            }

            if constexpr (uint32_t(opts) & uint32_t(StrSplitOpts::RemoveEmpty))
            {
                if (token.length())
                {
                    tokens.push_back(token);
                }
            }
            else
            {
                tokens.push_back(token);
            }
            begin = end + delim.length();
            end = str.find(delim, begin);
        }
        tokens.push_back(std::string(str.substr(begin, end)));

        return tokens;
    }

    [[nodiscard]]
    inline int64_t StrBeginningWhitespace(std::string_view str)
    {
        int64_t count = 0;
        while(std::isspace(str[count++]));
        return count;
    }
}

#endif //_CC_STRING_TOOLS_HPP