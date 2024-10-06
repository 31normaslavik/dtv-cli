#include "commandline_parser.h"
#include "debug.h"
#include "downloader.h"
#include "engine.h"
#include <iostream>
#include <span>
#include <vector>

int main(int argc, char **argv) try {

    setlocale(LC_ALL, "ru_RU.utf8");
    dtv::debugln("Current locale: {}", setlocale(LC_ALL, nullptr));

    auto arguments = std::span(argv, static_cast<size_t>(argc));
    const std::vector<std::string> args(arguments.begin() + 1, arguments.end());

    // TODO: переделать на std::span
    dtv::CommandLine const &line = dtv::command_line_parser(args);
    dtv::Downloader downloader(line);
    dtv::Cmd cmd(line);

    cmd.ExecBefore();
    downloader.Start();
    cmd.ExecAfter();
    return EXIT_SUCCESS;

} catch (const std::exception &e) {
    std::cerr << e.what() << "\n";
}
