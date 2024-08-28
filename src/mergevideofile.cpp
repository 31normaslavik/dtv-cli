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

    for (const auto& entry: std::filesystem::directory_iterator(_line.Output()->GetPathToTemp())) {
        if (entry.path().filename().string().contains(_split_video.output.string()) &&
            entry.path().filename().extension().string() == "." + (!_line.Merge_output_extension().empty() ? _line.Merge_output_extension() : _line.Extension())) {

            _split_video.video = entry.path();
            if(!_split_video.video.empty()) break;
        }
    }

    if(_split_video.video.empty())
        throw std::runtime_error("Not inicialiset video object");

    std::error_code ec;
    if(!_line.No_overwrites()){
        fs::rename(_split_video.video,
            _line.Output()->GetPathToSave() / _split_video.video.filename(), ec);
    }

    if(ec){
        std::cerr << ec.message() << " : " << ec.value()<<"\n";
        if(!_line.No_overwrites()){
            fs::copy_file(_split_video.video,
                          _line.Output()->GetPathToSave() / _split_video.video.filename() ,
                          fs::copy_options::overwrite_existing);
        }else{
            fs::copy_file(_split_video.video,
                          _line.Output()->GetPathToSave() / _split_video.video.filename() ,
                          fs::copy_options::skip_existing);
        }
        if(fs::remove(_split_video.video)){
            std::cout << "File: " << _split_video.video << " sussefuly removed\n";
        }else{
            std::cout << "File: " << _split_video.video << " not removed\n";
        }
    }

    std::cout << "The [" + _split_video.video.filename().string() + "] file has been successfully created\n";
}

void dtv::MergeVideoFile::MergeFfmpeg() {

    int result{};

    if(!_split_video.video.empty() && !_split_video.voice.empty() &&
        !_split_video.output.empty()){

        std::string command(R"(ffmpeg -i ")" + _split_video.video.string() + R"(" -i ")"
                            + _split_video.voice.string()
                            + R"(" -c:v copy -filter_complex amix=inputs=2:duration=first:dropout_transition=0:weights=")"
                            + std::format(std::locale("en_US.utf8"), "{} {}", _line.Vol_audio(), _line.Vol_translate())
                            + R"(":normalize=1 -y ")" + _split_video.output.string() + "."
                            + (!_line.Merge_output_extension().empty() ? _line.Merge_output_extension() : _line.Extension()) + R"(")");
        std::cout << command << "\n";

        result = std::system(command.c_str());
        if(fs::remove(_split_video.video)) _split_video.video.clear();
        fs::remove(_split_video.voice);
        if(fs::remove(_split_video.voice)) _split_video.voice.clear();
    }

    if (result != 0)
        throw std::runtime_error("Operate merge end with error");
    return;
}

void dtv::MergeVideoFile::InitVideo() {
    
    for (const auto& entry: std::filesystem::directory_iterator(_line.Output()->GetPathToTemp())) {
        if (entry.path().filename().string().contains(_video.id) &&
            entry.path().filename().string().contains(_video.extractor_key) &&
            entry.path().filename().string().contains(".___Video___.")) {

            _split_video.video = entry.path();

            if(!_split_video.video.empty()) break;
        }
    }

    if (_split_video.video.empty()) std::cerr << "The main video track was not found\n";
}

void dtv::MergeVideoFile::InitVoice() {
    for (const auto& entry:
         std::filesystem::directory_iterator(_line.Output()->GetPathToTemp())) {
        if (entry.path().extension().string() == ".mp3" &&
            entry.path().filename().string().contains(_video.id) &&
            entry.path().filename().string().contains(".___Voice___.")) {
            _split_video.voice = entry.path().filename().string();
            break;
        }
    }
    if (_split_video.voice.empty()) std::cerr<<"The voice translation could not be downloaded\n";
}

void dtv::MergeVideoFile::InitAudio() {
    if(!_line.Replace_audio().empty())
        _split_video.audio = _line.Replace_audio();
    if (_split_video.audio.empty()) std::cerr<<"The replace audio track was not found\n";
}

void dtv::MergeVideoFile::InitOutput() {
    const std::string str_tmp{"/@#$%^&*()+={}[]\\|;'\",<>/?| `~"};
    
    std::string new_title{_video.title};

    for (char& ch: new_title) {
        for (std::string::size_type index = str_tmp.find_first_of(ch);
             index != std::string::npos;
             index = str_tmp.find_first_of(ch)) {
            ch = '_';
        }
    }

    if(new_title.length() > 100)
        new_title = new_title.substr(0, 100);

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
    // namespace fs = std::filesystem;

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
