#include "dataloader.h"
#include "debug.h"

dtv::DataLoader::DataLoader(boost::urls::url_view const& url): _url{url}
{
}

void dtv::DataLoader::DownloadJsonsToDisk() {
    std::string const command{std::format("yt-dlp \"{}\" --write-info-json --no-write-playlist-metafiles --skip-download", std::string(_url.buffer()))};

    debugln("Func: {}\nCommand: {}", __func__, command);
    int result = system(command.c_str());
    debugln("Result: {}", result);
}

