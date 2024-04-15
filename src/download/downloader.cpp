#include "downloader.h"
#include "downloadingmedia.h"
#include "mergevideofile.h"
#include <iostream>

namespace dtv {


    Downloader::Downloader(const dtv::CommandLine& line): line_{line}
    {
        path_ptr_ = std::make_shared<dtv::FsDirectories>(line_.Path());
        data_loader_ptr_ = std::make_shared<dtv::DataLoader>(line_.Urls(), path_ptr_, line.Format());
    }

    void Downloader::DownloadVideosWithTranslate(const std::string& language, bool subtitles) {

        videos_ptr_ = data_loader_ptr_->VideoData()->GetAllData();
        std::cout << "Общее количество видео из всех url: " << videos_ptr_.size() << std::endl;
        std::cout << "\n";

        for(const auto& video_ptr: videos_ptr_)
        {
            //try {
            dtv::DownloadingMedia video_downloader(video_ptr);
            video_downloader.Download();

            dtv::MergeVideoFile split_video(video_ptr, path_ptr_);
            split_video.Init();

        }
    }    

} // namespace dtv
