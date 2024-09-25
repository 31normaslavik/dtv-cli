#include "commandline_parser.h"
#include "debug.h"
#include "downloader.h"
#include "engine.h"
#include <iostream>

int main(int argc, char **argv) try {

    setlocale(LC_ALL, "ru_RU.utf8");
    dtv::debugln("Current locale: {}", setlocale(LC_ALL, NULL));

    dtv::CommandLine const &line = dtv::command_line_parser(argc, argv);
    dtv::Downloader downloader(line);
    dtv::Cmd cmd(line);
    
    cmd.ExecBefore();
    downloader.Start();
    cmd.ExecAfter();
    return EXIT_SUCCESS;

} catch (const std::exception &e) {
    std::cerr << e.what() << "\n";
}
