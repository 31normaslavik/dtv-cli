#include "dataloader.h"

dtv::DataLoader::DataLoader(boost::urls::url_view const& url): _url{url}{

    // DownloadJsonsToDisk(urls);
    // FillingInVideoData();
}

void dtv::DataLoader::DownloadJsonsToDisk() {
    std::string const command("yt-dlp \"" + std::string(_url.buffer()) + "\" \
                --write-info-json --no-write-playlist-metafiles --skip-download");
    int result = system(command.c_str());
}

// std::vector<std::filesystem::directory_entry> dtv::DataLoader::CreateListJsonFromDisk() const {
//     std::vector<std::filesystem::directory_entry> v;

//     for (const auto& entry:
//          std::filesystem::directory_iterator(path_ptr_ -> GetPathToTemp())) {

//         std::cout << entry.path().filename().string() << " "
//                   << std::filesystem::file_size(entry.path().filename()) / 1024
//                   << " KiB" << std::endl;

//         if (entry.path().filename().string().find(".json") != std::string::npos) {
//             v.emplace_back(entry);
//         }
//     }

//     std::cout << "\n";

//     return v;
// }

// void dtv::DataLoader::FillingInVideoData() {

//     const auto vector_json = CreateListJsonFromDisk();

//     video_data_ptr_ = std::make_shared<dtv::VectorPtrVideos>();

//     for (const auto& json: vector_json) {

//         JsonExtractorInfo const ex(json);

//         std::shared_ptr<dtv::JsonData> json_data = ex.GetJsonData();

//         std::shared_ptr<Video> video;
        
//         if (json_data->_type() != "video"){
//             std::cerr << json_data -> Webpage_url() << " is not video source" << std::endl;
//             continue;
//         }
        
//         video_data_ptr_->PushBack(video);
//     }
// }

// std::shared_ptr<dtv::VectorPtrVideos> dtv::DataLoader::VideoData() { return video_data_ptr_; }

// TODO çàìåíèòü regex íà boost::url
// std::string dtv::DataLoader::createFormatForUrl(const std::string &url)
// {
//     return {};
// }
