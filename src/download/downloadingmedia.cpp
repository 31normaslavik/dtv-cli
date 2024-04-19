#include "downloadingmedia.h"
#include <iostream>

dtv::DownloadingMedia::DownloadingMedia(std::shared_ptr<Video> video_ptr):
    video_ptr_{video_ptr}
{
}

void dtv::DownloadingMedia::Download(bool subtitles) {

    if(DownloaderYtDlp()){
        //resource_.unavailable_ = true;
        throw std::runtime_error("[yt_dlp_downloader]");
    };

    if(DownloaderVotCli(subtitles)){
        //resource_.unavailable_ = true;
        throw std::runtime_error("[vot_cli_downloader]");
    };
}

int dtv::DownloadingMedia::DownloaderYtDlp() {
    // _flushall();
    return std::system(
        std::string(R"(yt-dlp ")" +
                    video_ptr_->WebpageUrl() + R"(" -f ")" +
                    video_ptr_->WebpageUrlFormat()[video_ptr_->WebpageUrl()] + R"TTT(" -o "%(title)s.___)TTT" +
                    video_ptr_->Extractor() + R"TTT(___%(format_id)s.%(display_id)s.%(ext)s")TTT" + " \
                    --replace-in-metadata \"title,uploader\" \"[ @#$%^&*()<>?/\\\"-]\" \"_\" ").c_str());
    std::cout << "\n";
}

int dtv::DownloadingMedia::DownloaderVotCli(bool subtitles) {
// FIXME Разобрать синтаксис
    // _flushall();
    if (subtitles) {
        return std::system(std::string(R"(vot-cli --reslang ")" +
                                       video_ptr_->Language() + R"(" --subs --output="." ")" +
                                       video_ptr_->WebpageUrl() + R"(" && vot-cli --reslang ")" +
                                       video_ptr_->Language() + R"(" --output="." ")" +
                                       video_ptr_->WebpageUrl() + R"(")").c_str());
        std::cout << "\n";
    }
    else{
        return std::system(
            std::string(R"LLL(vot-cli --reslang ")LLL" + video_ptr_->Language() + R"LLL(" --output="." ")LLL" + video_ptr_->WebpageUrl() + "\"").c_str());
        std::cout << "\n";
    }
}
