// #include "dataloader.h"
#include "downloader.h"
// #include "downloadingmedia.h"
#include "engine.h"
// #include "mergevideofile.h"
#include "extractor.h"

namespace dtv {


    Downloader::Downloader(const dtv::CommandLine& line): _line{line}
    {
    }

    void Downloader::Start() {

        for(const auto& url: _line.Urls())
        {
            // DataLoader dataLoader(url);
            // dataLoader.DownloadJsons();
            Engine::DownloadJson(url);            

            for(auto video = Extractor::JsonToVideo(_line); video.has_value(); video = Extractor::JsonToVideo(_line)){
                // DownloadingMedia videoDownloader(*video, _line);
                // videoDownloader.Download();
                // MergeVideoFile splitVideo(*video, _line);
                // splitVideo.Processing();
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
