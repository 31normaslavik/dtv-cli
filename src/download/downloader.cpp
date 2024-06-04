#include "downloader.h"
#include "downloadingmedia.h"
#include "mergevideofile.h"
#include "readjson.h"

namespace dtv {


    Downloader::Downloader(const dtv::CommandLine& line): _line{line}
    {
        // path_ptr_ = std::make_shared<dtv::FsDirectories>(line_.Path());
        // data_loader_ptr_ = std::make_shared<dtv::DataLoader>(line_.Urls(), path_ptr_, line.Format());
    }

    void Downloader::Start() {

        // videos_ptr_ = data_loader_ptr_->VideoData()->GetAllData();
        // std::cout << "Total number of videos from all urls : " << videos_ptr_.size() << std::endl;
        

        for(const auto& url: _line.Urls())
        {
            DataLoader d(url);
            d.DownloadJsonsToDisk();

            ReadJson r;
            for(auto video = r.JsonToVideo(_line); video.has_value();){

                DownloadingMedia video_downloader(*video, _line);
                video_downloader.Download();
                MergeVideoFile split_video(*video, _line);
                split_video.Processing();

                video = r.JsonToVideo(_line);

            }



        }
    }    

} // namespace dtv
