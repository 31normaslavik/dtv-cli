#include "mergevideofile.h"
#include "../presentation/presentation.h"

dtv::MergeVideoFile::MergeVideoFile(std::shared_ptr<Video> video, std::shared_ptr<FsDirectories> path): video_(video), path_(path)
{
    InitVideo();
    InitAudio();
    InitVoice();
    InitOutput();

    if (MergeFfmpeg(split_video_.video_, split_video_.voice_, split_video_.audio_, split_video_.output_) != 0) {
        throw std::runtime_error("Split video failed");
    };

    std::filesystem::copy_file(path_->getPathToTemp()/split_video_.output_, path_->getPathToSave()/split_video_.output_, std::filesystem::copy_options::overwrite_existing);
}

int dtv::MergeVideoFile::MergeFfmpeg(const std::string& video, const std::string& voice,
                                     const std::string& audio,
                                     const std::string& output) {
    return std::system(
        std::string(R"(ffmpeg -i ")" +
                    video + R"(" -i ")" +
                    voice + R"(" -i ")" +
                    audio + R"(" -c:v copy -filter_complex amix=inputs=2:duration=longest:dropout_transition=0:weights="1 0.20 2 1.0":normalize=1 -y ")" +
                    output + R"(")")
            .c_str());
}

void dtv::MergeVideoFile::InitVideo() {
    using FORMAT_VIDEO = dtv::Format::FORMAT_VIDEO;

    if (video_->Extractor() == "youtube")
    {
        for (const auto& entry: std::filesystem::directory_iterator(path_->getPathToTemp())) {
            if (std::string::size_type pos;
                entry.path().filename().string().find(".___youtube___") !=
                    std::string::npos &&
                entry.path().filename().string().find(video_->Id()) !=
                    std::string::npos) {
                pos = entry.path().filename().string().find(".___youtube___");
                switch (static_cast<FORMAT_VIDEO> (stoi(entry.path().filename().string().substr(pos + 8,3)))) {
                case FORMAT_VIDEO::MP4_640x360_30:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::WEBM_640x360_30:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::MP4_640x360_60_10:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::WEBM_640x360_60_10:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::MP4_854x480_30:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::WEBM_854x480_30:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::MP4_854x480_60_10:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::WEBM_854x480_60_10:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::MP4_1280x720_30:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::WEBM_1280x720_30:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::MP4_1280x720_60:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::WEBM_1280x720_60:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::MP4_1280x720_60_10:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::WEBM_1280x720_60_10:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::MP4_1920x1080_30:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::WEBM_1920x1080_30:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::MP4_1920x1080_60:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::WEBM_1920x1080_60:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::MP4_1920x1080_60_10:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::WEBM_1920x1080_60_10:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::MP4_2560x1440_30:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::WEBM_2560x1440_30:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::WEBM_2560x1440_60:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::MP4_2560x1440_60_10:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::WEBM_2560x1440_60_10:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::MP4_3840x2160_30:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::WEBM_3840x2160_30:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::WEBM_3840x2160_60:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::MP4_3840x2160_60_10:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::WEBM_3840x2160_60_10:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                case FORMAT_VIDEO::MP4_7680x4320_60_10:
                    split_video_.video_ = entry.path().filename();
                    split_video_.output_ = entry.path().filename().extension();
                    break;
                default:
                    break;
                }
            }
        }

    } else if  (video_->Extractor() == "9gag")

    {
        for (const auto& entry: std::filesystem::directory_iterator(path_->getPathToTemp())) {
            if (std::string::size_type pos;
                entry.path().filename().string().contains(".___9gag___") /*!=
                    std::string::npos*/ &&
                entry.path().filename().string().contains(video_->Id()) /*!=
                    std::string::npos*/)
            {
                //pos = entry.path().filename().string().find(".___9gag___");
                //entry.path().
                std::vector<std::string> v{"460sv", "460sv-h265", "460sv-vp8", "460sv-vp9"};

                for (const auto& i : v) {
                    if (entry.path().filename().string().contains(i)){
                        split_video_.video_ = entry.path().filename();
                        split_video_.output_ = entry.path().filename().extension();
                        break;
                    }
                }


                // switch (static_cast<FORMAT_VIDEO> (stoi(entry.path().filename().string().substr(pos + 11,3))))
                // {
                //     case FORMAT_VIDEO::MP4_460x816_460sv:
                //         split_video_.video_ = entry.path().filename();
                //         split_video_.output_ = entry.path().filename().extension();
                //         break;
                //     case FORMAT_VIDEO::MP4_460x816_460sv_h265:
                //         split_video_.video_ = entry.path().filename();
                //         split_video_.output_ = entry.path().filename().extension();
                //         break;
                //     case FORMAT_VIDEO::WEBM_460x816_460sv_vp8:
                //         split_video_.video_ = entry.path().filename();
                //         split_video_.output_ = entry.path().filename().extension();
                //         break;
                //     case FORMAT_VIDEO::WEBM_460x816_460sv_vp9:
                //         split_video_.video_ = entry.path().filename();
                //         split_video_.output_ = entry.path().filename().extension();
                //         break;
                //     default:
                //         break;
                // }
            }
        }
    }
}



void dtv::MergeVideoFile::InitVoice() {
    for (const auto& entry:
         std::filesystem::directory_iterator(path_->getPathToTemp())) {
        if (entry.path().filename().extension().string() == ".mp3" &&
            entry.path().filename().string().find(video_->Id()) !=
                std::string::npos) {
            split_video_.voice_ = entry.path().filename();
        }
    }
}

void dtv::MergeVideoFile::InitAudio() {
    using FORMAT_AUDIO = dtv::Format::FORMAT_AUDIO;
    for (const auto& entry:
         std::filesystem::directory_iterator(path_->getPathToTemp())) {
        if (std::string::size_type pos;
            entry.path().filename().string().find(".format_") !=
                std::string::npos &&
            entry.path().filename().string().find(video_->Id()) !=
                std::string::npos) {
            pos = entry.path().filename().string().find(".format_");
            switch (static_cast<FORMAT_AUDIO> (stoi(entry.path().filename().string().substr(pos + 8, 3)))) {
            case FORMAT_AUDIO::MP4_233:
                split_video_.audio_ = entry.path().filename();
                break;
            case FORMAT_AUDIO::MP4_234:
                split_video_.audio_ = entry.path().filename();
                break;
            case FORMAT_AUDIO::M4A_2_599:
                split_video_.audio_ = entry.path().filename();
                break;
            case FORMAT_AUDIO::WEBM_2_600:
                split_video_.audio_ = entry.path().filename();
                break;
            case FORMAT_AUDIO::M4A_2_139:
                split_video_.audio_ = entry.path().filename();
                break;
            case FORMAT_AUDIO::WEBM_2_249:
                split_video_.audio_ = entry.path().filename();
                break;
            case FORMAT_AUDIO::WEBM_2_250:
                split_video_.audio_ = entry.path().filename();
                break;
            case FORMAT_AUDIO::M4A_2_140:
                split_video_.audio_ = entry.path().filename();
                break;
            case FORMAT_AUDIO::WEBM_2_251:
                split_video_.audio_ = entry.path().filename();
                break;
            default:
                break;
            }
        }
    }
}

void dtv::MergeVideoFile::InitOutput() {
    const std::string str_tmp{"/@#$%^&*()+={}[]\\|;'\",<>/?| `~"};
    std::string new_title{video_->Title()};
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

    split_video_.output_ = new_title + split_video_.output_;
}
