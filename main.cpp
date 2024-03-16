#include "downloader.h"
#include <iostream>
//#include <set>
//#include "presentation.h"
#include "command_line_parser.h"

// dtv-cli --output ./ --format [ mp4[1080,720,480], webm[1080,720,480] ]  urls
int main(int argc, char** argv) try {
    using std::cout;
    using std::endl;

    ParserLine parse = command_line_parser(argc, argv);

    // if (argc < 5) {
    //     std::cerr << "dtv-cli --output ./ "
    //                  "--format [mp4 webm] [_4320 _2160 _1440 _1080 _720 _480 _360] "
    //                  "[_30 _30_10 _60 _60_10]  urls\n" << std::endl;
    //     std::cerr << "Format 480p 30 fps" << std::endl;
    //     std::cerr << "dtv-cli --output ./playlist4 --format mp4_480_30 \"url1\" \"url2\"\n" << std::endl;

    //     std::cerr << "Format 1080p 60 fps" << std::endl;
    //     std::cerr << "dtv-cli --output ./playlist1 --format mp4_1080_60 \"url\"\n" << std::endl;

    //     std::cerr << "Format 2160p 60 fps HDR" << std::endl;
    //     std::cerr << "dtv-cli --output ./playlist4 --format mp4_2160_60_10 \"url1\" \"url2\"\n" << std::endl;

    //     std::cerr << "Format 2160p 60 fps HDR" << std::endl;
    //     std::cerr << "dtv-cli --output ./playlist2 --format webm_2160_60_10 \"url1\" \"url2\" \"url3\"\n" << endl;
    //     return 0;
    // }

    // if (std::string(argv[1]) != "--output") {
    //     std::cerr << "arg1 --output" << endl;
    //     return 0;
    // }

    // if (std::string(argv[2]).find("https://") != std::string::npos) {
    //     std::cerr << "arg2 path incorrect" << endl;
    //     return 0;
    // }

    // if (std::string(argv[3]) != "--format") {
    //     std::cerr << "arg3 --format" << endl;
    //     return 0;
    // }

    // if(format_video_argv(argv[4]) == FORMAT_VIDEO::UNKNOWNV){
    //     std::cerr<<"arg4 format incorrect"<<endl;
    //     return 0;
    // }

    // std::set<std::string> urls;

    // for (size_t i{5}; i < argc; ++i)
    //     urls.insert(argv[i]);


    dtv::Downloader d(parse.urls, parse.pathToSave, parse.format);

    d.download_videos_with_translate();
    return 0;

} catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
}
