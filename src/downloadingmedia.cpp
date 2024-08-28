#include "downloadingmedia.h"
#include "debug.h"
#include "formater.h"
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

    Formater formater(_video, _line);

    std::string command(R"(yt-dlp ")" +
                _video.webpage_url + R"(" -f ")" +
                formater.GetFormat() + R"(" -o "%(id)s.___)" +
                _video.extractor_key + R"(___.___Video___.%(format_id)s.%(ext)s")");

    debugln("Func: {}", __func__);
    debugln("Video cmd: {}", command);

    std::cout << std::flush;
    result = system(command.c_str());

    debugln("Video result: {}", result);
}

void dtv::DownloadingMedia::DownloaderVotCli() {

    int result{};
    if (_line.Write_subs()) {
        std::cout << std::flush;
        std::string commandSub{std::format("vot-cli --lang \"{0}\" --reslang \"{1}\" --subs --subs-srt --output=\".\" --output-file=\"{3}.___Subtitles___.\" \"{2}\"",
                                         _line.Translate_from_lang(), _line.Sub_lang(), _video.webpage_url, _video.id)};
        debugln("Func: {}", __func__);
        debugln("Subtitles cmd: {}", commandSub);

        std::string commandVoice{std::format("vot-cli --lang \"{0}\" --reslang \"{1}\" --output=\".\" --output-file=\"{3}.___Voice___.\" \"{2}\"",
                                                 _line.Translate_from_lang(), _line.Translate_to_lang(), _video.webpage_url, _video.id)};

        debugln("Voice cmd: {}", commandVoice);

        result = system(commandSub.c_str());
        debugln("Subtitles result: {}", result);
        result = system(commandVoice.c_str());
        debugln("Voice result: {}", result);
    }
    else{
        std::cout << std::flush;
        std::string command{std::format("vot-cli --lang \"{0}\" --reslang \"{1}\" --output=\".\" --output-file=\"{3}.___Voice___.\" \"{2}\"",
                                         _line.Translate_from_lang(), _line.Translate_to_lang(), _video.webpage_url, _video.id)};

        debugln("Func: {}", __func__);
        debugln("Voice cmd: {}", command);

        result = system(command.c_str());
        debugln("Voice result: {}", result);
    }
}
