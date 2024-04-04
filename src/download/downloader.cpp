//
// Created by pancake on 12/12/23.
//

#include "downloader.h"
#include "downloadingmedia.h"
#include "../merge/mergevideofile.h"
#include "../interface/video.h"
#include <iostream>
//#include <utility>

namespace dtv {


    std::shared_ptr<dtv::VideoData> dtv::DataLoader::VideoData() { return video_data_; }

    void DataLoader::DownloadJsonsToDisk(const std::set<Source,cmpSource>& urls) const {
        std::cout<< std::filesystem::current_path() << std::endl;
        for (const auto& url: urls) {
            std::system(
                        std::string("yt-dlp \"" + url.url_ + "\" \
--write-info-json --no-write-playlist-metafiles --skip-download \
--parse-metadata \"video::(?P<formats>)\" --parse-metadata \"video::(?P<thumbnails>)\" \
--parse-metadata \"video::(?P<thumbnail>)\" --parse-metadata \"video::(?P<tags>)\" \
--parse-metadata \"video::(?P<automatic_captions>)\" \
--replace-in-metadata \"title,uploader\" \"[ @#$%^&*()<>?/\\-]\" \"_\" ").c_str());
        }
    }

    std::vector<std::filesystem::directory_entry> DataLoader::JsonListOnDisk() const {
        std::vector<std::filesystem::directory_entry> v;

        for (const auto& entry:
             std::filesystem::directory_iterator(path_ -> getPathToTemp())) {
            std::cout << entry.path().filename() << " "
                      << std::filesystem::file_size(entry.path().filename()) / 1024
                    << " KiB" << std::endl;
            if (entry.path().filename().string().find(".json") != std::string::npos) {
                v.emplace_back(entry);
            }
        }

        return v;
    }


    Downloader::Downloader(const dtv::CommandLine& line)
    {
        path_ = std::make_shared<dtv::FsDirectories>(line.Path());
        std::set<Source, cmpSource> const s = line.Resources();
        resources_.insert(resources_.cbegin(),s.cbegin(), s.cend());
        data_loader_ = std::make_shared<dtv::DataLoader>(line.Resources(), path_);

        std::cout<< "path_" <<"\tget() = " << path_.get()
                  << ", use_count() = " << path_.use_count() << '\n';

    }

    void Downloader::DownloadVideosWithTranslate(const std::string& language, bool subtitles) {
        std::cout << std::filesystem::current_path().string() << std::endl;

        //dtv::DataLoader data_loader(urls_, path_);

        videos_ = data_loader_->VideoData()->GetAllData();
        std::cout << "Общее количество видео из всех url: " << videos_.size() << std::endl;

        std::cout<< "path_" <<"\tget() = " << path_.get()
                  << ", use_count() = " << path_.use_count() << '\n';

        dtv::DownloadingMedia video_downloader(resources_);
        video_downloader.Download();

        for(const auto& video: videos_)
        {
            dtv::MergeVideoFile const split_video(video, path_);

        }
    }

    // MergeVideoFile::~MergeVideoFile() {
    //     if (std::filesystem::exists(split_video_.video)) {
    //         std::filesystem::remove(split_video_.video);
    //     }
    //     if (std::filesystem::exists(split_video_.voice)) {
    //         std::filesystem::remove(split_video_.voice);
    //     }
    //     if (std::filesystem::exists(split_video_.audio)) {
    //         std::filesystem::remove(split_video_.audio);
    //     }
    //     if (std::filesystem::exists(split_video_.output)) {
    //         std::filesystem::remove(split_video_.output);
    //     }

    // }

} // namespace dtv
