#include "mergevideofile.h"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

dtv::MergeVideoFile::MergeVideoFile(Video& video, CommandLine const& line):
    _video{video},
    _line{line}
{
}

void dtv::MergeVideoFile::Processing()
{
        InitVideo();
        InitVoice();
        InitAudio();
        InitOutput();

        MergeFfmpeg();
        MoveOnDisk();
}

void dtv::MergeVideoFile::MoveOnDisk()
{
    namespace fs = std::filesystem;

    fs::copy_file(_line.Temp_dir() / _split_video.video,
                  _line.Output() / _split_video.output ,
                               fs::copy_options::overwrite_existing);

    std::cout << "The [" + _split_video.output.string() + "] file has been successfully created\n";
}

void dtv::MergeVideoFile::MergeFfmpeg() {
    std::cout << "\n";
    int result = 0;

    if(!_split_video.video.empty() &&
        !_split_video.voice.empty() &&
        !_split_video.output.empty()){

        std::string command(R"(ffmpeg -i ")" + _split_video.video.string() + R"(" -i ")"
                            + _split_video.voice.string()
                            + R"(" -c:v copy -filter_complex amix=inputs=2:duration=first:dropout_transition=0:weights=")"
                            + std::to_string(_line.Vol_audio()) + " " + std::to_string(_line.Vol_translate()) + R"(":normalize=1 -y ")" +
                            _split_video.output.string() + "\"");

        result = std::system(command.c_str());
    }

    if (result != 0)
        throw std::runtime_error("Operate merge end with error");
    return;
}

void dtv::MergeVideoFile::InitVideo() {
    
        for (const auto& entry: std::filesystem::directory_iterator(_line.Temp_dir())) {
        if (entry.path().filename().string().contains(_video.id)
                && entry.path().filename().extension().string() == _video.formats.rbegin()->ext) {

                _split_video.video = entry.path();

                if(!_split_video.video.empty()) break;
            }
        }

     if (_split_video.video.empty()) std::cerr << "The main video track was not found\n";
}

void dtv::MergeVideoFile::InitVoice() {
    for (const auto& entry:
         std::filesystem::directory_iterator(_line.Temp_dir())) {
        if (entry.path().extension().string() == ".mp3" &&
            entry.path().filename().string().contains(_video.id)) {
            _split_video.voice = entry.path().filename().string();
            break;
        }
    }
    if (_split_video.voice.empty()) std::cerr<<"The voice translation could not be downloaded\n";
}

void dtv::MergeVideoFile::InitAudio() { // FIXME
    _split_video.audio = _line.Replace_audio();
    if (_split_video.audio.empty()) std::cerr<<"The main audio track was not found\n";
}

void dtv::MergeVideoFile::InitOutput() {
    const std::string str_tmp{"/@#$%^&*()+={}[]\\|;'\",<>/?| `~"};
    
    std::string new_title/*{video_ptr_->Title()}*/;

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
    _split_video.output = new_title /*+ split_video_.output_*/;
}

// TODO убрать многочисленный вызов ->GetPathToTemp()
// сделать код более лакончиным
dtv::MergeVideoFile::~MergeVideoFile() {
    namespace fs = std::filesystem;

    // if(!(split_video_.output_ + split_video_.extension_).empty())
    //     fs::remove(path_ptr_->GetPathToTemp() / (split_video_.output_ + split_video_.extension_));

    // if(!split_video_.video_.empty())
    //     fs::remove(path_ptr_->GetPathToTemp() / (split_video_.video_));

    // if(!split_video_.audio_.empty())
    //     fs::remove(path_ptr_->GetPathToTemp() / (split_video_.audio_));

    // if(!split_video_.voice_.empty())
    //     fs::remove(path_ptr_->GetPathToTemp() / (split_video_.voice_));

    // if(!split_video_.tempf_.empty())
    //     fs::remove(path_ptr_->GetPathToTemp() / (split_video_.tempf_));

}
