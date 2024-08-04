#include "downloadingmedia.h"
#include <iostream>

dtv::DownloadingMedia::DownloadingMedia(Video& video, CommandLine const& line):
    _video{video},
    _line{line}
{
}

void dtv::DownloadingMedia::Download() {

    DownloaderYtDlp();
    DownloaderVotCli();
}

void dtv::DownloadingMedia::DownloaderYtDlp() {

    int result{};

    std::string command(R"(yt-dlp ")" +
                _video.webpage_url + R"(" -f ")" +
                _video.webpage_url + R"(" -o "%(id)s.___)" +
                _video.extractor_key + R"(___%(format_id)s.%(display_id)s.%(ext)s")");

    std::cout << std::flush;
    result = system(command.c_str());
}

void dtv::DownloadingMedia::DownloaderVotCli() {

    int result{};
    if (_line.Write_subs()) {
        std::cout << std::flush;

        std::string command(R"(vot-cli --lang ")" + _line.Translate_from_lang() + R"(" --reslang ")" +
                    _line.Translate_to_lang() + R"(" --subs --output="." ")" +
                    _video.webpage_url + R"(" && vot-cli --lang ")" + _line.Translate_from_lang() + R"(" --reslang ")" +
                    _line.Translate_to_lang() + R"(" --output="." ")" +
                    _video.webpage_url + R"(")");

        result = system(command.c_str());
    }
    else{
        std::cout << std::flush;

        std::string command(R"("vot-cli --lang ")" + _line.Translate_from_lang() + R"(" --reslang ")" +
                            _line.Translate_to_lang() + R"(" --output="." ")" +
                            _video.webpage_url + R"(")");

        result = system(command.c_str());
    }
}
