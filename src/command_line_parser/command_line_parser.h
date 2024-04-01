#pragma once
#include "../commandline.h"

#include <iostream>
#include <vector>
#include <boost/program_options.hpp>

template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    std::copy(v.begin(), v.end(), std::ostream_iterator<T>(os, " "));
    return os;
}

namespace dtv{

//namespace opt = boost::program_options;

CommandLine command_line_parser(int argc, char *argv[]);

} // namespace dtv

