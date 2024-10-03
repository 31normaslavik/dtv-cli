#pragma once

#include "commandline.h"
#include <iostream>
#include <iterator>
#include <vector>

template <class T>
std::ostream &operator<<(std::ostream &oss, const std::vector<T> &vec) {
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>(oss, "\n"));
    return oss;
}

namespace dtv{

CommandLine command_line_parser(std::vector<std::string> const &arguments);

} // namespace dtv

