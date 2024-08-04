#include "downloader.h"
#include "command_line_parser.h"
#include <iostream>

int main(int argc, char** argv) try {

    setlocale(LC_ALL, "ru_RU.utf8");
    printf("Current locale: %s\n", setlocale(LC_ALL, NULL));

    dtv::CommandLine const& line = dtv::command_line_parser(argc, argv);
    dtv::Downloader downloader(line);
    downloader.Start();

    return EXIT_SUCCESS;

} catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
}
