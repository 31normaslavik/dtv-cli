//
// Created by pancake on 12/12/23.
//

#include "downloader.h"

#include <format>
#include <iostream>
#include <utility>

namespace dtv {
    DataLoader::DataLoader(const std::set<std::string>& urls,
                           std::shared_ptr<FsDirectories> path) : path_(std::move(path)),
                            video_data_{nullptr} {
        if (urls.empty()) {
            throw std::runtime_error("No urls provided");
        }
        for (const auto& url: urls) {
            if (url.empty()) {
                throw std::runtime_error("Empty url provided");
            }
        }
        for (const auto& url: urls) {
            if (url.find("://") == std::string::npos) {
                throw std::runtime_error("Invalid url provided");
            }
        }

        create_json(urls);
        fill_video_data();
    }

    void DataLoader::fill_video_data() {
        const auto vector_json = read_json();
        video_data_ = std::make_shared<VideoData>();

        for (const auto& json: vector_json) {
            JsonData json_data(json);
            std::shared_ptr<Video> youtube;

            // std::string extractor = json_data.get_extractor();
            // std::string id = json_data.get_id();
            // std::string title = json_data.get_title();
            // std::string url = json_data.webpage_url();
            // int64_t index =  json_data.get_playlist_index();
            // int64_t count = json_data.get_playlist_count();
            // int64_t duration = json_data.get_duration();
            // int64_t limit = json_data.get_age_limit();

            if(json_data.get_extractor() == "youtube")
            youtube = std::make_shared<VideoYoutube>(
                           json_data.get_id(), json_data.get_title(),
                           json_data.webpage_url(), json_data.get_extractor(),
                           json_data.get_playlist_index(), json_data.get_playlist_count(),
                           json_data.get_duration(), json_data.get_age_limit());

            // if(json_data.get_extractor() == "vimeo");
            // if(json_data.get_extractor() == "dailymotion");
            // if(json_data.get_extractor() == "twitch");
            // if(json_data.get_extractor() == "soundcloud");
            // if(json_data.get_extractor() == "mixcloud");
            // if(json_data.get_extractor() == "bandcamp");
            // if(json_data.get_extractor() == "deezer");
            //

            video_data_->add(youtube);
        }
    }

    std::shared_ptr<VideoData> DataLoader::get_video_data() { return video_data_; }

    void DataLoader::create_json(const std::set<std::string>& urls) const {
        std::cout<< std::filesystem::current_path() << std::endl;
        for (const auto& url: urls) {
            std::system(
                        std::string(
                                    "yt-dlp \"" + url +
                                    "\" --write-info-json "
                                    "--no-write-playlist-metafiles "
                                    "--skip-download "
                                    "--parse-metadata \"video::(?P<formats>)\" "
                                    "--parse-metadata \"video::(?P<thumbnails>)\" "
                                    "--parse-metadata \"video::(?P<thumbnail>)\" "
                                    "--parse-metadata \"video::(?P<tags>)\" "
                                    "--parse-metadata \"video::(?P<automatic_captions>)\" "
                                    "--replace-in-metadata \"title,uploader\" \"[ /|\']\" \"_\"")
                        .c_str());
        }
    }

    std::vector<std::filesystem::directory_entry> DataLoader::read_json() const {
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

    SplitMediaFilesDownloader::SplitMediaFilesDownloader(std::shared_ptr<Video> video,
                    std::shared_ptr<FsDirectories> path,
                    const FORMAT_VIDEO& format) : path_(std::move(path)),
                                                  video_(std::move(video)),
                                                  format_(format) {
    }

    void SplitMediaFilesDownloader::download_video() {
        yt_dlp_downloader(video_->get_webpage_url(), format_);
        vot_cli_downloader(video_->get_webpage_url());
    }

    int SplitMediaFilesDownloader::yt_dlp_downloader(const std::string& url,
                                           const FORMAT_VIDEO& format) {
        return std::system(
                           std::string(
                                       "yt-dlp " + url + " -f " + combinate_format(format) +
                                       " -o \"%(title)s.format_%(format_id)s.%(display_id)s.%(ext)s\"")
                           .c_str());
    }

    int SplitMediaFilesDownloader::vot_cli_downloader(const std::string& url, const std::string& language, bool subtitles) {

        if (subtitles) {
            return std::system(
                           std::string("vot-cli --reslang " + language + R"( --subs --output="." ")" + url + "\" "
                                                "&& vot-cli --reslang " + language + R"( --output="." ")" + url + R"(")").c_str());
        }
        else
        return std::system(
                           std::string("vot-cli --reslang " + language + R"( --output="." ")" + url + R"(")").c_str());
    }

    MergeVideoFile::MergeVideoFile(std::shared_ptr<Video> video, std::shared_ptr<FsDirectories> path) :
                                                                    video_(std::move(video)),
        path_(std::move(path)) {
        init_video();
        init_audio();
        init_voice();
        init_output();

        if (ffmpeg_merge(split_video_.video, split_video_.voice, split_video_.audio, split_video_.output) != 0) {
            throw std::runtime_error("Split video failed");
        };

        std::filesystem::copy_file(path_->getPathToTemp() / split_video_.output,
                                   path_->getPathToSave() / split_video_.output);
    }

    int MergeVideoFile::ffmpeg_merge(const std::string& video, const std::string& voice,
                                 const std::string& audio,
                                 const std::string& output) {
        return std::system(
                           std::string("ffmpeg -i \"" + video + "\" -i \"" + voice + "\" -i \"" +
                                       audio +
                                       "\" -c:v copy "
                                       "-filter_complex "
                                       "amix=inputs=2:duration=longest:dropout_transition=0:weights="
                                       "\"1 0.20 2 1.0\":normalize=1 -y \"" +
                                       output + "\"")
                           .c_str());
    }

    void MergeVideoFile::init_video() {
        for (const auto& entry: std::filesystem::directory_iterator(path_->getPathToTemp())) {
            if (std::string::size_type pos;
                    entry.path().filename().string().find(".format_") !=
                    std::string::npos &&
                    entry.path().filename().string().find(video_->get_id()) !=
                    std::string::npos) {
                pos = entry.path().filename().string().find(".format_");
                switch (static_cast<FORMAT_VIDEO> (stoi(entry.path().filename().string().substr(pos + 8,3)))) {
                    case FORMAT_VIDEO::MP4_640x360_30:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::WEBM_640x360_30:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::MP4_640x360_60_10:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::WEBM_640x360_60_10:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::MP4_854x480_30:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::WEBM_854x480_30:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::MP4_854x480_60_10:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::WEBM_854x480_60_10:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::MP4_1280x720_30:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::WEBM_1280x720_30:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::MP4_1280x720_60:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::WEBM_1280x720_60:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::MP4_1280x720_60_10:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::WEBM_1280x720_60_10:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::MP4_1920x1080_30:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::WEBM_1920x1080_30:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::MP4_1920x1080_60:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::WEBM_1920x1080_60:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::MP4_1920x1080_60_10:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::WEBM_1920x1080_60_10:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::MP4_2560x1440_30:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::WEBM_2560x1440_30:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::WEBM_2560x1440_60:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::MP4_2560x1440_60_10:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::WEBM_2560x1440_60_10:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::MP4_3840x2160_30:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::WEBM_3840x2160_30:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::WEBM_3840x2160_60:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::MP4_3840x2160_60_10:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::WEBM_3840x2160_60_10:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    case FORMAT_VIDEO::MP4_7680x4320_60_10:
                        split_video_.video = entry.path().filename();
                        split_video_.output = entry.path().filename().extension();
                        break;
                    default:
                        break;
                }
            }
        }
    }

    void MergeVideoFile::init_voice() {
        for (const auto& entry:
             std::filesystem::directory_iterator(path_->getPathToTemp())) {
            if (entry.path().filename().extension().string() == ".mp3" &&
                entry.path().filename().string().find(video_->get_id()) !=
                std::string::npos) {
                split_video_.voice = entry.path().filename();
            }
        }
    }

    void MergeVideoFile::init_audio() {
        for (const auto& entry:
             std::filesystem::directory_iterator(path_->getPathToTemp())) {
            if (std::string::size_type pos;
                    entry.path().filename().string().find(".format_") !=
                    std::string::npos &&
                    entry.path().filename().string().find(video_->get_id()) !=
                    std::string::npos) {
                pos = entry.path().filename().string().find(".format_");
                switch (static_cast<FORMAT_AUDIO> (stoi(entry.path().filename().string().substr(pos + 8, 3)))) {
                    case FORMAT_AUDIO::MP4_233:
                        split_video_.audio = entry.path().filename();
                        break;
                    case FORMAT_AUDIO::MP4_234:
                        split_video_.audio = entry.path().filename();
                        break;
                    case FORMAT_AUDIO::M4A_2_599:
                        split_video_.audio = entry.path().filename();
                        break;
                    case FORMAT_AUDIO::WEBM_2_600:
                        split_video_.audio = entry.path().filename();
                        break;
                    case FORMAT_AUDIO::M4A_2_139:
                        split_video_.audio = entry.path().filename();
                        break;
                    case FORMAT_AUDIO::WEBM_2_249:
                        split_video_.audio = entry.path().filename();
                        break;
                    case FORMAT_AUDIO::WEBM_2_250:
                        split_video_.audio = entry.path().filename();
                        break;
                    case FORMAT_AUDIO::M4A_2_140:
                        split_video_.audio = entry.path().filename();
                        break;
                    case FORMAT_AUDIO::WEBM_2_251:
                        split_video_.audio = entry.path().filename();
                        break;
                    default:
                        break;
                }
            }
        }
    }

    void MergeVideoFile::init_output() {
        const std::string str_tmp{"/@#$%^&*()+={}[]\\|;'\",<>/?| `~"};
        std::string new_title{video_->get_title()};
        for (char& ch: new_title) {
            for (std::string::size_type index = str_tmp.find_first_of(ch);
                 index != std::string::npos;
                 index = str_tmp.find_first_of(ch)) {
                ch = '_';
            }
        }

        while (new_title.starts_with("_")) {
            new_title.erase(0, 1);
        }
        while (new_title.ends_with("_")) {
            new_title.erase(new_title.length() - 1, 1);
        }
        while (new_title.find("__") != std::string::npos) {
            new_title.replace(new_title.find("__"), 2, "_");
        }

        split_video_.output = new_title + split_video_.output;
    }

    Downloader::Downloader(const std::set<std::string>& urls, const std::filesystem::path &pathToSave,
        const std::string& format):
            path_{std::make_shared<dtv::FsDirectories>(pathToSave)},
            format_{format}
    {
        data_loader_ = std::make_shared<dtv::DataLoader>(urls, path_);
    }

    void Downloader::download_videos_with_translate(const std::string& language, bool subtitles) {
        std::cout << std::filesystem::current_path().string() << std::endl;

        //dtv::DataLoader data_loader(urls_, path_);

        videos_ = data_loader_->get_video_data()->getAllData();
        std::cout << "Общее количество видео из всех url: " << videos_.size() << std::endl;

        for(const auto& video: videos_) {
            dtv::SplitMediaFilesDownloader video_downloader(video, path_, format_video_argv(format_));
            video_downloader.download_video();
            dtv::MergeVideoFile split_video(video, path_);
        }
    }

    MergeVideoFile::~MergeVideoFile() {
        if (std::filesystem::exists(split_video_.video)) {
            std::filesystem::remove(split_video_.video);
        }
        if (std::filesystem::exists(split_video_.voice)) {
            std::filesystem::remove(split_video_.voice);
        }
        if (std::filesystem::exists(split_video_.audio)) {
            std::filesystem::remove(split_video_.audio);
        }
        if (std::filesystem::exists(split_video_.output)) {
            std::filesystem::remove(split_video_.output);
        }

    }
} // namespace dtv
