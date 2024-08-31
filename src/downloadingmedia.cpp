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

    std::any a = formater.GetFormat();
    std::string const command(std::format("yt-dlp \"{}\" -f \"{}\" -o \"%(id)s.___{}___.___Video___.%(format_id)s.%(ext)s\"",
                                    _video.webpage_url, std::any_cast<std::string>(a), _video.extractor_key));

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
        std::string const commandSub{std::format("vot-cli --lang \"{}\" --reslang \"{}\" --subs --subs-srt --output=\".\" --output-file=\"{}.___Subtitles___.\" \"{}\"",
                                         _line.Translate_from_lang(), _line.Sub_lang(), _video.id, _video.webpage_url)};
        debugln("Func: {}", __func__);
        debugln("Subtitles cmd: {}", commandSub);

        std::string const commandVoice{std::format("vot-cli --lang \"{}\" --reslang \"{}\" --output=\".\" --output-file=\"{}.___Voice___.\" \"{}\"",
                                                 _line.Translate_from_lang(), _line.Translate_to_lang(), _video.id, _video.webpage_url)};

        debugln("Voice cmd: {}", commandVoice);

        result = system(commandSub.c_str());
        debugln("Subtitles result: {}", result);
        result = system(commandVoice.c_str());
        debugln("Voice result: {}", result);
    }
    else{
        std::cout << std::flush;
        std::string const command{std::format("vot-cli --lang \"{}\" --reslang \"{}\" --output=\".\" --output-file=\"{}.___Voice___.\" \"{}\"",
                                         _line.Translate_from_lang(), _line.Translate_to_lang(), _video.id, _video.webpage_url)};

        debugln("Func: {}", __func__);
        debugln("Voice cmd: {}", command);

        result = system(command.c_str());
        debugln("Voice result: {}", result);
    }
}
