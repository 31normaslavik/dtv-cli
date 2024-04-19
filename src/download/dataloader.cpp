#include "dataloader.h"

#include "jsondata.h"
#include "presentation.h"
#include "commandline.h"
#include "videosource.h"

#include <iostream>
#include <regex>

dtv::DataLoader::DataLoader(const std::vector<std::string> &urls,
                            std::shared_ptr<FsDirectories> path_ptr, const std::string &format) :
    path_ptr_(path_ptr),
    video_data_ptr_{nullptr},
    format_{format} {

    DownloadJsonsToDisk(urls);
    FillingInVideoData();
}

void dtv::DataLoader::DownloadJsonsToDisk(const std::vector<std::string> &urls) const {

    for (const auto& url: urls) {
        _flushall();
        system(
            std::string("yt-dlp \"" + url + "\" \
                        --write-info-json --no-write-playlist-metafiles --skip-download \
                        --parse-metadata \"video::(?P<thumbnails>)\" \
                        --parse-metadata \"video::(?P<thumbnail>)\" --parse-metadata \"video::(?P<tags>)\" \
                        --replace-in-metadata \"title,uploader\" \"[ @#$%^&*()<>?/\\\"-]\" \"_\" ").c_str());
        std::cout << "\n";
    }
}

std::vector<std::filesystem::directory_entry> dtv::DataLoader::CreateListJsonFromDisk() const {
    std::vector<std::filesystem::directory_entry> v;

    for (const auto& entry:
         std::filesystem::directory_iterator(path_ptr_ -> GetPathToTemp())) {

        std::cout << entry.path().filename().string() << " "
                  << std::filesystem::file_size(entry.path().filename()) / 1024
                  << " KiB" << std::endl;

        if (entry.path().filename().string().find(".json") != std::string::npos) {
            v.emplace_back(entry);
        }
    }

    std::cout << "\n";

    return v;
}

void dtv::DataLoader::FillingInVideoData() {

    const auto vector_json = CreateListJsonFromDisk();

    video_data_ptr_ = std::make_shared<dtv::VectorPtrVideos>();

    for (const auto& json: vector_json) {

        JsonExtractorInfo const ex(json);

        std::shared_ptr<dtv::JsonData> json_data = ex.GetJsonData();

        std::shared_ptr<Video> video;
        
        if (json_data->_type() != "video"){
            std::cerr << json_data -> Webpage_url() << " is not video source" << std::endl;
            continue;
        }


        if(json_data->Extractor() == "youtube"){
            video = std::make_shared<VideoYoutube>();
            video->Id(json_data->Id());
            video->Title(json_data->Title());
            video->WebpageUrlFormat(json_data->Webpage_url(),
                               createFormatForUrl(json_data->Webpage_url()));
            video->WebpageUrl(json_data->Webpage_url());
            video->Extractor(json_data->Extractor());
            video->Playlist_index(json_data->Playlist_index());
            video->Playlist_count(json_data->Playlist_count());
            video->N_entries(json_data->N_entries());
            video->Age_limit(json_data->Age_limit());
            video->Duration(json_data->Duration());
            video->Format(json_data->Format());
            video->Format_id(json_data->Format_id());
        }

        else if(json_data->Extractor() == "vimeo"){
            video = std::make_shared<VideoVimeo>();
            video->Id(json_data->Id());
            video->Title(json_data->Title());
            video->WebpageUrlFormat(json_data->Webpage_url(),
                                    createFormatForUrl(json_data->Webpage_url()));
            video->WebpageUrl(json_data->Webpage_url());
            video->Extractor(json_data->Extractor());
            video->Duration(json_data->Duration());
        }

        else if(json_data->Extractor() == "9gag"){
            video = std::make_shared<VideoNineGag>();
            video->Id(json_data->Id());
            video->Title(json_data->Title());
            video->WebpageUrlFormat(json_data->Webpage_url(),
                                    createFormatForUrl(json_data->Webpage_url()));
            video->WebpageUrl(json_data->Webpage_url());
            video->Extractor(json_data->Extractor());
            video->Duration(json_data->Duration());

        }

        else if(json_data->Extractor() == "vimeo"){}
        else if(json_data->Extractor() == "dailymotion"){}
        else if(json_data->Extractor() == "twitch"){}
        else if(json_data->Extractor() == "soundcloud"){}
        else if(json_data->Extractor() == "mixcloud"){}
        else if(json_data->Extractor() == "bandcamp"){}
        else if(json_data->Extractor() == "deezer"){}
        
        video_data_ptr_->PushBack(video);
    }
}

std::shared_ptr<dtv::VectorPtrVideos> dtv::DataLoader::VideoData() { return video_data_ptr_; }

std::string dtv::DataLoader::createFormatForUrl(const std::string &url)
{
    for(const auto& res : resources){
        std::string regex = R"(^(http(s?)\://)(www\.|m\.|player\.|my\.|proxitok\.|inv\.)?()" + res + R"()+\.(com|edu|gov|m+il|net|org|biz|info|name|museum|us|ca|uk|tv|ru|be|es|video|cc)(\:[0-9]+)*(/($|[a-zA-Z0-9\.+\,\;\?\'\\\+\&amp;%\$#\=~_\-]+))*$)";
        std::regex e(regex);
        if(std::regex_match(url, e)){
            dtv::FormatVideo format_video = Format::FormatVideoArgv(format_, res);
            std::string frmt = Format::CombinateFormat(format_video, res);
            return frmt;
        }
    }
    return {};
}
