#include "engine.h"
#include "debug.h"
#include "formater.h"

dtv::Engine::Engine(const Video &video, const CommandLine &line)
{
    _pYtdlpEngine =  std::make_unique<YtdlpEngine >(video, line);
    _pVotcliEngine = std::make_unique<VotcliEngine>(video, line);
    _pFfmpegEngine = std::make_unique<FfmpegEngine>(video, line);
}

void dtv::Engine::DownloadJson(boost::urls::url_view url)
{
    // TODO желательно тут менять url на работающий
    std::string const command{std::format("yt-dlp \"{}\" --write-info-json --no-write-playlist-metafiles --skip-download",
                                          std::string(url.buffer()))};

    debugln("Func: {}\nCommand: {}", __func__, command);
    int result = system(command.c_str());
    debugln("Result: {}", result);
}

void dtv::Engine::DownloadVideo()
{
    _pYtdlpEngine->DownloadVideo();
}

void dtv::Engine::DownloadSubtitles()
{
    _pVotcliEngine->DownloadSubtitles();
}

void dtv::Engine::DownloadVoice()
{
    _pVotcliEngine->DownloadVoice();
}

void dtv::Engine::DownloadAnotation()
{
    debugln("Func: {}", __func__);
}

void dtv::Engine::Merge()
{
    _pFfmpegEngine->Merge();
}

dtv::YtdlpEngine::YtdlpEngine(const Video &video, const CommandLine &line): _video{video}, _line{line}
{
    debugln("Func: {}", __func__);
}

void dtv::YtdlpEngine::DownloadVideo()
{
    debugln("Func: {}", __func__);

    if(_line.Only_translate())
        return;

    std::string commandVideo = std::format("yt-dlp -f \"(bv*[fps<={0}]/bv*)[height<={1}]+ba/(b[fps<={0}]/b)[height<={1}]\" \"{2}\" -o \"%(id)s.___{3}___.___Video___.%(format_id)s.%(ext)s\"", _line.Fps(), _line.Height(), _video.webpage_url, _video.extractor_key);

    std::cout << std::flush;
    debugln("Video cmd: {}", commandVideo);
    int result = std::system(commandVideo.c_str());
    debugln("Video result: {}", result);
}

void dtv::YtdlpEngine::DownloadSubtitles()
{
    debugln("Func: {}", __func__);
}

dtv::VotcliEngine::VotcliEngine(const Video &video, const CommandLine &line): _video{video}, _line{line}
{
    debugln("Func: {}", __func__);
}

void dtv::VotcliEngine::DownloadVoice()
{
    if(!_line.No_translate()){
        std::cout << std::flush;
        std::string const commandVoice{std::format("vot-cli --lang \"{}\" --reslang \"{}\" --output=\".\" --output-file=\"{}.___Voice___.\" \"{}\"",
                                                   _line.Translate_from_lang(), _line.Translate_to_lang(), _video.id, _video.webpage_url)};

        debugln("Voice cmd: {}", commandVoice);
        int result = system(commandVoice.c_str());
        debugln("Voice result: {}", result);
    }
}

void dtv::VotcliEngine::DownloadSubtitles()
{
    if (_line.Write_subs()) {
        std::cout << std::flush;
        std::string const commandSub{std::format("vot-cli --lang \"{}\" --reslang \"{}\" --subs --subs-srt --output=\".\" --output-file=\"{}.___Subtitles___.\" \"{}\"",
                                                 _line.Translate_from_lang(), _line.Sub_lang(), _video.id, _video.webpage_url)};
        debugln("Func: {}", __func__);
        debugln("Subtitles cmd: {}", commandSub);
        int result = system(commandSub.c_str());
        debugln("Subtitles result: {}", result);
    }
}

dtv::FfmpegEngine::FfmpegEngine(const Video &video, const CommandLine &line): _video{video}, _line{line}
{
    debugln("Func: {}", __func__);
}

void dtv::FfmpegEngine::Merge()
{
    namespace fs = std::filesystem;

    debugln("Func: {}", __func__);

    for (const auto& entry: fs::directory_iterator(_line.Output()->GetPathToTemp())) {
        if (entry.path().filename().string().contains(_video.id) &&
            entry.path().filename().string().contains(_video.extractor_key) &&
            entry.path().filename().string().contains(".___Video___.")) {
            _split_video.video = entry.path();
            debugln("video: {}", _split_video.video.filename().string());
        }

        if (entry.path().extension().string() == ".mp3" &&
            entry.path().filename().string().contains(_video.id) &&
            entry.path().filename().string().contains(".___Voice___.")) {
            _split_video.voice = entry.path();
            debugln("voice: {}", _split_video.voice.filename().string());
        }

        if (entry.path().extension().string() == ".srt" &&
            entry.path().filename().string().contains(_video.id) &&
            entry.path().filename().string().contains(".___Subtitles___.")) {
            _split_video.subtitles = entry.path();
            debugln("subtitles: {}", _split_video.subtitles.filename().string());
        }
    }

    if(!_line.Replace_audio().empty()){
        _split_video.audio = _line.Replace_audio();
        debugln("audio: {}", _split_video.audio.filename().string());
    }

    if (_split_video.video.empty())
        messageln("The main video track was not found");

    if (_split_video.voice.empty())
        messageln("The voice translation could not be downloaded");

    if (_split_video.audio.empty())
        messageln("The replace audio track was not found");

    const std::string str_tmp{"/@#$%^&*()+={}[]\\|;'\",<>/?| `~"};

    std::string new_title{_video.title};
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
    while (new_title.contains("__")) {
        new_title.replace(new_title.find("__"), 2, "_");
    }
    if(new_title.length() > 100)
        new_title = new_title.substr(0, 100);
    // TODO чистить доп символы, включая точку
    _split_video.output = new_title /*+ split_video_.output_*/;

    //////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////
    /// //////////////////////////////////////////////////////////////////////////
    int result{};
    //Don't translate videos and simply download video
    bool no_translate = _line.No_translate();
    // Replace the audio in the video with your own
    bool custom_audio = !_line.Replace_audio().empty();
    // Replace the audio-to-video translation with your own
    bool custom_voice_audio = !_line.Replace_translate().empty();

    auto merge = [this, &result](){

        if(_line.No_translate())
            return;
        if(_line.Only_translate())
            return;

        Formater format(_video, _line);
        std::any a = format.GetFormat(FORMAT::FirstClosestVideo);
        Format f;
        if(a.has_value())
            f = std::any_cast<Format>(a);

        if(!_split_video.video.empty() && !_split_video.voice.empty() &&
            !_split_video.output.empty()){
            std::string command = std::format("ffmpeg -i \"{0}\" -i \"{1}\" {5} -filter_complex amix=inputs=2:duration=first:dropout_transition=0:weights=\"{2}\":normalize=1 -y \"{3}.{4}\"",
                _split_video.video.string(), _split_video.voice.string(),
                std::format(std::locale("en_US.utf8"), "{} {}", _line.Vol_audio(), _line.Vol_translate()),
                _split_video.output.string(), !_line.Merge_output_extension().empty() ? _line.Merge_output_extension() : _line.Extension(),
                _line.Write_subs() && !_split_video.subtitles.filename().string().empty() ? "-b:v "
                  + (a.has_value() ? std::format(std::locale("en_US.utf8"),"{}", f.size > 0 ? f.size * 8 : f.tbr * 8) : "2M")
                  + " -vf subtitles=" + _split_video.subtitles.filename().string() : "-c:v copy"
                );

            debugln("Command merge video+audio+subtitles: {}", command);
            result = std::system(command.c_str());
            debugln("Result: {}", result);

            if(fs::remove(_split_video.video))
                _split_video.video.clear();
            if(fs::remove(_split_video.voice))
                _split_video.voice.clear();
            if(fs::remove(_split_video.subtitles))
                _split_video.subtitles.clear();
        }

        if (result != 0)
            throw std::runtime_error("Operate merge end with error");
    };

    merge();

    ///////////////////////////////////////////////////////////////////////////
    /// ///////////////////////////////////////////////////////////////////////
    /// ///////////////////////////////////////////////////////////////////////


    for (const auto& entry: fs::directory_iterator(_line.Output()->GetPathToTemp())) {
        if (entry.path().filename().string().contains(_split_video.output.string()) &&
            entry.path().filename().extension().string() == "." + (!_line.Merge_output_extension().empty() ? _line.Merge_output_extension() : _line.Extension())) {
            _split_video.video = entry.path();
            debugln("video: {}", _split_video.video.filename().string());
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