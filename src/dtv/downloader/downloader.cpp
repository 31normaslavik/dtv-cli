#include "downloader.h"
#include "engine.h"
#include "extractor.h"
#include <boost/url/parse.hpp>

namespace dtv {


Downloader::Downloader(const dtv::CommandLine& line): _line{line}
{
}

void Downloader::Start() {

    for(const auto& url: _line.Urls())
    {
        Engine::DownloadJson(boost::urls::parse_uri(url).value());

        for(auto video = Extractor::JsonToVideo(_line); video.has_value(); video = Extractor::JsonToVideo(_line)){
            Engine engine(*video, _line);
            engine.DownloadVideo();
            engine.DownloadVoice();
            engine.DownloadSubtitles();
            engine.DownloadAnotation();
            engine.Merge();
        }
    }
}

} // namespace dtv
