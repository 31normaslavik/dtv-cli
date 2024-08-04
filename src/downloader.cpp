#include "dataloader.h"
#include "downloader.h"
#include "downloadingmedia.h"
#include "mergevideofile.h"
#include "extractor.h"

namespace dtv {


    Downloader::Downloader(const dtv::CommandLine& line): _line{line}
    {
    }

    void Downloader::Start() {

        for(const auto& url: _line.Urls())
        {
            DataLoader d(url);
            d.DownloadJsonsToDisk();

            for(auto video = Extractor::JsonToVideo(_line); video.has_value(); video = Extractor::JsonToVideo(_line)){
                DownloadingMedia video_downloader(*video, _line);
                video_downloader.Download();
                MergeVideoFile split_video(*video, _line);
                split_video.Processing();                
            }
        }
    }    

} // namespace dtv
