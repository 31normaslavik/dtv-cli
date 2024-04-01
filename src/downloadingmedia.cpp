#include "downloadingmedia.h"

dtv::DownloadingMedia::DownloadingMedia(std::vector<Source> resources): resources_{resources}
{
}

void dtv::DownloadingMedia::Download() {

    for(auto& i: resources_){

        if(DownloaderYtDlp(i)){
            i.unavailable_ = true;
            //throw std::runtime_error("[yt_dlp_downloader]");
        };

        if(DownloaderVotCli(i)){
            i.unavailable_ = true;
            //throw std::runtime_error("[vot_cli_downloader]");
        };
    }


}

int dtv::DownloadingMedia::DownloaderYtDlp(const Source& source) {
    return std::system(
        std::string(R"(yt-dlp ")" +
                    source.url_ + R"(" -f ")" +
                    source.format_ + R"TTT(" -o "%(title)s.___)TTT" +
                    source.resource_ + R"TTT(___%(format_id)s.%(display_id)s.%(ext)s")TTT").c_str());
}

int dtv::DownloadingMedia::DownloaderVotCli(const Source& source, const std::string& language, bool subtitles) {

    if (subtitles) {
        return std::system(std::string(R"(vot-cli --reslang ")" +
                                       language + R"(" --subs --output="." ")" +
                                       source.url_ + R"(" && vot-cli --reslang ")" +
                                       language + R"(" --output="." ")" +
                                       source.url_ + R"(")").c_str());
    }
    else{
        return std::system(
            std::string(R"(vot-cli --reslang ")" + language + R"(" --output="." ")" + source.url_ + "\"").c_str());
    }
}
