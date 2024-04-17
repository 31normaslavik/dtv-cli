#pragma once

#include "commandline.h"

#include <iostream>
#include <vector>

#include <boost/program_options.hpp>

template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    std::copy(v.begin(), v.end(), std::ostream_iterator<T>(os, "\n"));
    return os;
}

namespace dtv{

const CommandLine command_line_parser(int argc, char *argv[]) ;

} // namespace dtv

