#include <filesystem>
#include <iostream>
#include <vector>
#include <boost/program_options.hpp>
namespace opt = boost::program_options;

struct ParserLine{
    std::set<std::string> urls;
    std::filesystem::path pathToSave;
    std::string format;
};

template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
  std::copy(v.begin(), v.end(), std::ostream_iterator<T>(os, " "));
  return os;
}

ParserLine command_line_parser(int argc, char *argv[]);
