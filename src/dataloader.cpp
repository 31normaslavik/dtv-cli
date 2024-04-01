#include "dataloader.h"
#include "commandline.h"
#include "fs_directories.h"
#include "interface/interface.h"
#include "interface/videoninegag.h"
#include "interface/videovimeo.h"
#include "interface/videoyoutube.h"
#include "jsondata/jsondata.h"
#include <iostream>
#include <set>

dtv::DataLoader::DataLoader(const std::set<Source,cmpSource>& urls,
                       std::shared_ptr<FsDirectories> path) : path_(path),
      video_data_{nullptr} {

    std::cout<< "path_" <<"\tget() = " << path_.get()
              << ", use_count() = " << path_.use_count() << '\n';


    // if (urls.empty()) {
    //     throw std::runtime_error("[DataLoader] No urls provided");
    // }
    // for (const auto& url: urls) {
    //     if (url.url_.empty()) {
    //         throw std::runtime_error("[DataLoader] Empty url provided");
    //     }
    // }
    // for (const auto& url: urls) {
    //     if (url.url_.find("://") == std::string::npos) {
    //         throw std::runtime_error("[DataLoader] Invalid url provided");
    //     }
    // }

    DownloadJsonsToDisk(urls);
    FillingInVideoData();
}

void dtv::DataLoader::FillingInVideoData() {
    const auto vector_json = JsonListOnDisk();
    video_data_ = std::make_shared<dtv::VideoData>();

    for (const auto& json: vector_json) {
        JsonExtractorInfo const ex(json);
        std::shared_ptr<JsonData> json_data = ex.get_json_data();
        std::shared_ptr<Video> video;

        // std::string extractor = json_data.Extractor();
        // std::string id = json_data.Id();
        // std::string title = json_data.Title();
        // std::string url = json_data.webpage_url();
        // int64_t index =  json_data.PlaylistIndex();
        // int64_t count = json_data.PlaylistCount();
        // int64_t duration = json_data.Duration();
        // int64_t limit = json_data.AgeLimit();


        if(json_data->get_extractor() == "youtube"){
            video = std::make_shared<VideoYoutube>(
                json_data->get_id(), json_data->get_title(),
                json_data->webpage_url(), json_data->get_extractor(),
                json_data->get_playlist_index(), json_data->get_playlist_count(),
                json_data->get_duration(), json_data->get_age_limit());
        }
        else if(json_data->get_extractor() == "vimeo"){
            video = std::make_shared<VideoVimeo>(
                json_data->get_id(), json_data->get_title(),
                json_data->webpage_url(), json_data->get_extractor(),
                json_data->get_playlist_index(), json_data->get_playlist_count(),
                json_data->get_duration(), json_data->get_age_limit());
        }
        else if(json_data->get_extractor() == "vimeo"){}
        else if(json_data->get_extractor() == "dailymotion"){}
        else if(json_data->get_extractor() == "twitch"){}
        else if(json_data->get_extractor() == "soundcloud"){}
        else if(json_data->get_extractor() == "mixcloud"){}
        else if(json_data->get_extractor() == "bandcamp"){}
        else if(json_data->get_extractor() == "deezer"){}

        else if(json_data->get_extractor() == "9gag"){
            video = std::make_shared<VideoNineGag>(
                json_data->get_id(), json_data->get_title(),
                json_data->webpage_url(), json_data->get_extractor(),
                json_data->get_playlist_index(), json_data->get_playlist_count(),
                json_data->get_duration(), json_data->get_age_limit());
        }

        video_data_->PushBack(video);
    }
}

