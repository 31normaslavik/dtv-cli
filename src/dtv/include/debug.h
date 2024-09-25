#pragma once

#include <format>
#include <iostream>
#include <string_view>

namespace dtv {

struct Debug
{
#ifndef NDEBUG
    inline static bool debug{true};
#else
    inline static bool debug{false};
#endif
};

template<typename... Args>
void debug(std::string_view rt_fmt_str, Args&&... args)
{
    if(Debug::debug) {
        std::cout << std::vformat(rt_fmt_str, std::make_format_args(args...));
    }
}

template<typename... Args>
void debugln(std::string_view rt_fmt_str, Args&&... args)
{
    if(Debug::debug) {
        std::cout << std::vformat(rt_fmt_str, std::make_format_args(args...)) << "\n";
    }
}

} // namespace dtv
