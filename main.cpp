#include "downloader.h"
#include <iostream>
#include "command_line_parser.h"

int main(int argc, char** argv) try {
    using std::cout;
    using std::endl;

    ParserLine parse = command_line_parser(argc, argv);

    dtv::Downloader d(parse.urls, parse.pathToSave, parse.format);

    d.download_videos_with_translate();
    return 0;

} catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
}
