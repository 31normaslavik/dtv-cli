#include "downloader.h"
#include "command_line_parser.h"
#include <iostream>

int main(int argc, char** argv) try {
    //using std::cout;
    //using std::endl;

    dtv::CommandLine line = dtv::command_line_parser(argc, argv);

    dtv::Downloader downloader(line);
    
    downloader.DownloadVideosWithTranslate();
    return 0;

} catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
}
