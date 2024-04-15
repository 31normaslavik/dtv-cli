#include "mergevideofile.h"
#include "presentation.h"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

dtv::MergeVideoFile::MergeVideoFile(std::shared_ptr<Video> video_ptr,
                                    std::shared_ptr<FsDirectories> path_ptr):
    video_ptr_{video_ptr} ,
    path_ptr_{path_ptr}
{

}

void dtv::MergeVideoFile::Init()
{
        InitVideo();
        InitAudio();
        InitVoice();
        InitOutput();

        MergeFfmpeg();
        MoveOnDisk();
}

void dtv::MergeVideoFile::MoveOnDisk()
{
    namespace fs = std::filesystem;

    fs::copy_file(path_ptr_->GetPathToTemp() / (split_video_.output_ + split_video_.extension_),
                               path_ptr_->GetPathToSave() / (split_video_.output_ + split_video_.extension_),
                               fs::copy_options::overwrite_existing);

    std::cout << "the [" + split_video_.output_ + split_video_.extension_ + "] file has been successfully created\n\n";

    fs::remove(path_ptr_->GetPathToTemp() / (split_video_.output_ + split_video_.extension_));
    fs::remove(path_ptr_->GetPathToTemp() / (split_video_.video_));
    fs::remove(path_ptr_->GetPathToTemp() / (split_video_.audio_));
    fs::remove(path_ptr_->GetPathToTemp() / (split_video_.voice_));

    if(! split_video_.tempf_.empty())
        fs::remove(path_ptr_->GetPathToTemp() / (split_video_.tempf_));

}

void dtv::MergeVideoFile::MergeFfmpeg() {
    std::cout << "\n";
    int result_operation = 0;

    if(!split_video_.video_.empty() &&
        !split_video_.voice_.empty() &&
        !split_video_.audio_.empty() &&
        !split_video_.output_.empty()){

        result_operation = std::system(
        std::string(R"(ffmpeg -i ")" +
                    split_video_.video_ + R"(" -i ")" +
                    split_video_.audio_ + R"(" -i ")" +
                    split_video_.voice_ + R"(" -c:v copy -filter_complex amix=inputs=2:duration=longest:dropout_transition=0:weights="0.10 1":normalize=1 -y ")" +
                    split_video_.output_ + split_video_.extension_ + R"(")")
                .c_str());
        std::cout << "\n";
    }
    else if(split_video_.voice_.empty()){

        result_operation = std::system(
            std::string(R"(ffmpeg -i ")" +
                        split_video_.video_ + R"(" -i ")" +
                        split_video_.audio_ + R"(" -y -c:v copy -c:a copy ")" +
                        split_video_.output_ + split_video_.extension_ + R"(")")
                .c_str());
        std::cout << "\n";
    }
    if (result_operation != 0)
        throw std::runtime_error("Operate merge end with error");
    return;
}


void dtv::MergeVideoFile::InitVideo() {
    
    if (video_ptr_->Extractor() == "youtube"){
        for (const auto& entry: std::filesystem::directory_iterator(path_ptr_->GetPathToTemp())) {
            if (std::string::size_type pos;
                entry.path().filename().string().contains(".___youtube___") &&
                entry.path().filename().string().contains(video_ptr_->Id()) ) {

                pos = entry.path().filename().string().find(".___youtube___");

                // std::cout<<pos<<std::endl;
                // std::cout<<entry.path().filename().string().substr(pos + 14, 3)<<std::endl;

                switch (static_cast<dtv::FormatVideo> (std::stoi(entry.path().filename().string().substr(pos + 14, 3)))) {
                case dtv::FormatVideo::MP4_640x360_30:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::WEBM_640x360_30:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::MP4_640x360_60_10:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::WEBM_640x360_60_10:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::MP4_854x480_30:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::WEBM_854x480_30:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::MP4_854x480_60_10:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::WEBM_854x480_60_10:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::MP4_1280x720_30:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::WEBM_1280x720_30:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::MP4_1280x720_60:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::WEBM_1280x720_60:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::MP4_1280x720_60_10:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::WEBM_1280x720_60_10:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::MP4_1920x1080_30:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::WEBM_1920x1080_30:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::MP4_1920x1080_60:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::WEBM_1920x1080_60:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::MP4_1920x1080_60_10:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::WEBM_1920x1080_60_10:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::MP4_2560x1440_30:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::WEBM_2560x1440_30:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::WEBM_2560x1440_60:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::MP4_2560x1440_60_10:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::WEBM_2560x1440_60_10:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::MP4_3840x2160_30:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::WEBM_3840x2160_30:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::WEBM_3840x2160_60:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::MP4_3840x2160_60_10:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::WEBM_3840x2160_60_10:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                case dtv::FormatVideo::MP4_7680x4320_60_10:
                    split_video_.video_ = entry.path().filename();
                    split_video_.extension_ = entry.path().filename().extension();
                    break;
                default:
                    break;
                }
                if(! split_video_.video_.empty()) break;
            }
        }
        
    } else if  (video_ptr_->Extractor() == "9gag"){
        for (const auto& entry: std::filesystem::directory_iterator(path_ptr_->GetPathToTemp())) {
            if (entry.path().filename().string().contains(".___9gag___") &&
                entry.path().filename().string().contains(video_ptr_->Id()) ){


                for (const auto& i : {"460sv", "460sv-h265", "460sv-vp8", "460sv-vp9"}) {
                    if (entry.path().filename().string().contains(i)){

                        split_video_.tempf_ = entry.path().filename().string();

                        split_video_.video_ = entry.path().stem().string() +
                                              ".___video___" +
                                              entry.path().extension().string();

                        split_video_.extension_ = entry.path().extension();

                        /**
                         * @brief creates an audio track from a media file
                         */
                        std::system(
                            std::string("ffmpeg -i \"" +
                                        entry.path().filename().string() +
                                        "\" -map 0:a -acodec copy \"" +
                                        entry.path().stem().string() +
                                        ".___audio___" +
                                        entry.path().extension().string() + "\"" ).c_str());

                        /**
                         * @brief creates an video track from a media file
                         */
                        std::system(
                            std::string("ffmpeg -i \"" +
                                        entry.path().filename().string() +
                                        "\" -map 0:v -vcodec copy \"" +
                                        entry.path().stem().string() +
                                        ".___video___" +
                                        entry.path().extension().string() + "\"" ).c_str());
                        break;
                    }
                }

            }
        }
    }
     if (split_video_.video_.empty()) std::cerr<<"The main video track was not found: " << video_ptr_->Title() <<std::endl;
}



void dtv::MergeVideoFile::InitVoice() {
    for (const auto& entry:
         std::filesystem::directory_iterator(path_ptr_->GetPathToTemp())) {
        if (entry.path().extension().string() == ".mp3" &&
            entry.path().filename().string().contains(video_ptr_->Id())) {
            split_video_.voice_ = entry.path().filename();
            break;
        }
    }
    if (split_video_.voice_.empty()) std::cerr<<"The voice translation could not be downloaded: " << video_ptr_->Title() <<std::endl;
}

void dtv::MergeVideoFile::InitAudio() { // FIXME
    if (video_ptr_->Extractor() == "youtube"){
        for (const auto& entry:
             std::filesystem::directory_iterator(path_ptr_->GetPathToTemp())) {
            if (std::string::size_type pos;
                entry.path().filename().string().contains(".___youtube___") &&
                entry.path().filename().string().contains(video_ptr_->Id()) ) {

                pos = entry.path().filename().string().find(".___youtube___");

                switch (static_cast<dtv::FormatAudio> (stoi(entry.path().filename().string().substr(pos + 14, 3)))) {
                case dtv::FormatAudio::MP4_233:
                    split_video_.audio_ = entry.path().filename();
                    break;
                case dtv::FormatAudio::MP4_234:
                    split_video_.audio_ = entry.path().filename();
                    break;
                case dtv::FormatAudio::M4A_2_599:
                    split_video_.audio_ = entry.path().filename();
                    break;
                case dtv::FormatAudio::WEBM_2_600:
                    split_video_.audio_ = entry.path().filename();
                    break;
                case dtv::FormatAudio::M4A_2_139:
                    split_video_.audio_ = entry.path().filename();
                    break;
                case dtv::FormatAudio::WEBM_2_249:
                    split_video_.audio_ = entry.path().filename();
                    break;
                case dtv::FormatAudio::WEBM_2_250:
                    split_video_.audio_ = entry.path().filename();
                    break;
                case dtv::FormatAudio::M4A_2_140:
                    split_video_.audio_ = entry.path().filename();
                    break;
                case dtv::FormatAudio::WEBM_2_251:
                    split_video_.audio_ = entry.path().filename();
                    break;
                default:
                    break;
                }
                if(! split_video_.audio_.empty()) break;
            }
        }
    }else if (video_ptr_->Extractor() == "9gag"){
        for (const auto& entry:
             std::filesystem::directory_iterator(path_ptr_->GetPathToTemp())) {
            if (entry.path().filename().string().contains(".___9gag___") &&
                entry.path().filename().string().contains(".___audio___") &&
                entry.path().filename().string().contains(video_ptr_->Id())
                ) {
                split_video_.audio_ = entry.path().filename();
                break;
            }
        }
        
    }else if (video_ptr_->Extractor() == "vimeo"){}

    if (split_video_.audio_.empty()) std::cerr<<"The main audio track was not found: " << video_ptr_->Title() <<std::endl;
}

void dtv::MergeVideoFile::InitOutput() {
    const std::string str_tmp{"/@#$%^&*()+={}[]\\|;'\",<>/?| `~"};
    
    std::string new_title{video_ptr_->Title()};

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
// TODO чистить доп символы, включая точку
    split_video_.output_ = new_title /*+ split_video_.output_*/;
}

dtv::MergeVideoFile::~MergeVideoFile() {
    if (std::filesystem::exists(split_video_.video_)) {
        std::filesystem::remove(split_video_.video_);
    }
    if (std::filesystem::exists(split_video_.voice_)) {
        std::filesystem::remove(split_video_.voice_);
    }
    if (std::filesystem::exists(split_video_.audio_)) {
        std::filesystem::remove(split_video_.audio_);
    }
    if (std::filesystem::exists(split_video_.output_)) {
        std::filesystem::remove(split_video_.output_);
    }
}
