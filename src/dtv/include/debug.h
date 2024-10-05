#pragma once
#include<version>

#ifdef __cpp_lib_format
    #include <format>
    #include <string_view>
#else
    #include <fmt/core.h>
    #include <fmt/format.h>
    #include <fmt/printf.h>
#endif

#include <iostream>

namespace dtv {

struct Debug
{
#ifndef NDEBUG
    inline static bool debug{true};
#else
    inline static bool debug{false};
#endif
};


#ifdef __cpp_lib_format

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

using std::format;

#else

template <typename... Args>
void debug(fmt::string_view fmt, Args&&... args){
    std::cout << fmt::vformat(fmt, fmt::make_format_args(args...));
}

template <typename... Args>
void debugln(fmt::string_view fmt, Args&&... args){
    std::cout << fmt::vformat(fmt, fmt::make_format_args(args...)) << "\n";
}


// template<typename... Args>
// using format = void(fmt::string_view fmt, Args&&... args);
// using format fmt::format;
using fmt::format;

#endif

} // namespace dtv
