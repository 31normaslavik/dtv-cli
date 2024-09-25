#include "engine.h"
#include "debug.h"
#include "formater.h"

dtv::Engine::Engine(const Video &video, const CommandLine &line) {
    _pYtdlpEngine = std::make_unique<YtdlpEngine>(video, line);
    _pVotcliEngine = std::make_unique<VotcliEngine>(video, line);
    _pFfmpegEngine = std::make_unique<FfmpegEngine>(video, line);
    _pCmd = std::make_unique<Cmd>(line);
}

void dtv::Engine::DownloadJson(boost::urls::url_view url) {
    // TODO желательно тут менять url на работающий
    std::string const command{
        std::format("yt-dlp \"{}\" --write-info-json "
                    "--no-write-playlist-metafiles --skip-download",
                    std::string(url.buffer()))};

    debugln("Func: {}\nCommand: {}", __func__, command);
    int result = system(command.c_str());
    debugln("Result: {}", result);
}

void dtv::Engine::DownloadVideo() { _pYtdlpEngine->DownloadVideo(); }

void dtv::Engine::DownloadSubtitles() { _pVotcliEngine->DownloadSubtitles(); }

void dtv::Engine::DownloadVoice() { _pVotcliEngine->DownloadVoice(); }

void dtv::Engine::DownloadAnotation() { debugln("Func: {}", __func__); }

void dtv::Engine::Merge() { _pFfmpegEngine->Merge(); }

dtv::YtdlpEngine::YtdlpEngine(const Video &video, const CommandLine &line)
    : _video{video}, _line{line} {
    debugln("Func: {}", __func__);
}

void dtv::YtdlpEngine::DownloadVideo() {
    debugln("Func: {}", __func__);

    if (_line.TranslationOnly())
        return;

    std::string commandVideo = std::format(
                "yt-dlp -f "
                "\"(bv*[fps<={0}]/bv*)[height<={1}]+ba/(b[fps<={0}]/b)[height<={1}]\" "
                "\"{2}\" -o \"%(id)s.___{3}___.___Video___.%(format_id)s.%(ext)s\"",
                _line.Fps(), _line.Height(), _video.webpage_url, _video.extractor_key);

    std::cout << std::flush;
    debugln("Video cmd: {}", commandVideo);
    int result = std::system(commandVideo.c_str());
    debugln("Video result: {}", result);
}

void dtv::YtdlpEngine::DownloadSubtitles() { debugln("Func: {}", __func__); }

dtv::VotcliEngine::VotcliEngine(const Video &video, const CommandLine &line)
    : _video{video}, _line{line} {
    debugln("Func: {}", __func__);
}

void dtv::VotcliEngine::DownloadVoice() {
    if (!_line.WithoutTranslation()) {
        std::cout << std::flush;
        std::string const commandVoice{
            std::format("vot-cli --lang \"{}\" --reslang \"{}\" --output=\".\" "
                        "--output-file=\"{}.___Voice___.\" \"{}\"",
                        _line.TranslateFromLang(), _line.TranslateToLang(),
                        _video.id, _video.webpage_url)};

        debugln("Voice cmd: {}", commandVoice);
        int result = system(commandVoice.c_str());
        debugln("Voice result: {}", result);
    }
}

void dtv::VotcliEngine::DownloadSubtitles() {
    if (_line.Write_subs()) {
        std::cout << std::flush;
        std::string const commandSub{std::format(
                        "vot-cli --lang \"{}\" --reslang \"{}\" --subs --subs-srt "
                        "--output=\".\" --output-file=\"{}.___Subtitles___.\" \"{}\"",
                        _line.TranslateFromLang(), _line.Sub_lang(), _video.id,
                        _video.webpage_url)};
        debugln("Func: {}", __func__);
        debugln("Subtitles cmd: {}", commandSub);
        int result = system(commandSub.c_str());
        debugln("Subtitles result: {}", result);
    }
}

dtv::FfmpegEngine::FfmpegEngine(const Video &video, const CommandLine &line)
    : _video{video}, _line{line} {
    debugln("Func: {}", __func__);
}

void dtv::FfmpegEngine::Merge() {
    namespace fs = std::filesystem;

    debugln("Func: {}", __func__);

    for (const auto &entry :
         fs::directory_iterator(_line.Output()->GetPathToTemp())) {
        if (entry.path().filename().string().contains(_video.id) &&
                entry.path().filename().string().contains(_video.extractor_key) &&
                entry.path().filename().string().contains(".___Video___.")) {
            _mediaParts.video = entry.path();
            debugln("video: {}", _mediaParts.video.filename().string());
        }

        if (entry.path().extension().string() == ".mp3" &&
                entry.path().filename().string().contains(_video.id) &&
                entry.path().filename().string().contains(".___Voice___.")) {
            _mediaParts.voice = entry.path();
            debugln("voice: {}", _mediaParts.voice.filename().string());
        }

        if (entry.path().extension().string() == ".srt" &&
                entry.path().filename().string().contains(_video.id) &&
                entry.path().filename().string().contains(".___Subtitles___.")) {
            _mediaParts.subtitles = entry.path();
            debugln("subtitles: {}", _mediaParts.subtitles.filename().string());
        }
    }

    if (!_line.ReplaceSound().empty()) {
        _mediaParts.audio = _line.ReplaceSound();
        debugln("audio: {}", _mediaParts.audio.filename().string());
    }

    if (_mediaParts.video.empty())
        debugln("The main video track was not found");

    if (_mediaParts.voice.empty())
        debugln("The voice translation was not found");

    if (_mediaParts.audio.empty())
        debugln("The replace audio track was not found");

    const std::string str_tmp{"/@#$%^&*()+={}[]\\|;'\",<>/?| `~"};

    std::string new_title{_video.title};
    for (char &ch : new_title) {
        for (std::string::size_type index = str_tmp.find_first_of(ch);
             index != std::string::npos; index = str_tmp.find_first_of(ch)) {
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
    if (new_title.length() > 100)
        new_title = new_title.substr(0, 100);
    // TODO чистить доп символы, включая точку
    _mediaParts.output = new_title /*+ split_video_.output_*/;

    //////////////////////////////////////////////////////////////////////////////
    /// MERGE ////////////////////////////////////////////////////////////////////
    /// //////////////////////////////////////////////////////////////////////////
    const std::string extensionVideo{!_line.MergeOutputExtension().empty() ? _line.MergeOutputExtension() : _line.Extension()};

    auto merge = [this, &extensionVideo]() {
        int result{};

        debugln("Func: {}", __func__);

        if (_line.TranslationOnly()) {
            if (_mediaParts.voice.empty())
                throw std::invalid_argument("The translation file was not found");
            return 0;
        }

        Formater format(_video, _line);
        std::any a = format.GetFormat(FORMAT::FirstClosestVideo);
        Format f;
        if (a.has_value())
            f = std::any_cast<Format>(a);

        const std::string subtitles{_line.Write_subs() && !_mediaParts.subtitles.filename().string().empty() ? "-b:v " +
            (a.has_value() ? std::format(std::locale("en_US.utf8"), "{}", f.size > 0 ? f.size * 8 : f.tbr * 8) : "2M") +
            " -vf subtitles=" + _mediaParts.subtitles.filename().string() : "-c:v copy"};

        if (_line.WithoutTranslation()) {
            if (_mediaParts.video.empty())
                throw std::invalid_argument("The video file was not found");

            if (!_line.ReplaceSound().empty() && !_mediaParts.output.empty()) {
                std::string const command{
                    std::format(
                                "ffmpeg -i \"{0}\" -i \"{1}\" -map 0 -map -0:a -map 1:a {4} -b:a 180K -shortest -y \"{2}.{3}\"",
                                _mediaParts.video.string(),
                                _mediaParts.audio.string(),
                                _mediaParts.output.string(),
                                extensionVideo,
                                subtitles
                                )};

                debugln("Command merge [video + replace audio]: {}", command);
                result = std::system(command.c_str());
                debugln("Result: {}", result);

                if(!result){
                    if (fs::remove(_mediaParts.video))
                        _mediaParts.video.clear();
                    if (fs::remove(_mediaParts.subtitles))
                        _mediaParts.subtitles.clear();
                }
            }
            return 0;
        }

        if (!_mediaParts.video.empty() && !_mediaParts.voice.empty() &&
                !_mediaParts.output.empty() && _line.ReplaceSound().empty() &&
                !_line.Save_translation_no_merge()) {
            std::string const command{
                std::format(
                            "ffmpeg -i \"{0}\" -i \"{1}\" {5} -filter_complex "
                            "amix=inputs=2:duration=first:dropout_transition=0:weights=\"{2}\":"
                            "normalize=1 -y \"{3}.{4}\"",
                            _mediaParts.video.string(),
                            !_line.ReplaceTranslate().empty() ? _line.ReplaceTranslate().string() : _mediaParts.voice.string(),
                            std::format(std::locale("en_US.utf8"), "{} {}", _line.Vol_audio(), _line.Vol_translate()),
                            _mediaParts.output.string(),
                            extensionVideo,
                            subtitles
                            )};

            debugln("Command merge [video + voice + subtitles]: {}", command);
            result = std::system(command.c_str());
            debugln("Result: {}", result);

            if(!result){
                if (fs::remove(_mediaParts.video))
                    _mediaParts.video.clear();
                if ((!_line.Save_translation() || !_line.Save_translation_no_merge()) && fs::remove(_mediaParts.voice))
                    _mediaParts.voice.clear();
                if (fs::remove(_mediaParts.subtitles))
                    _mediaParts.subtitles.clear();
            }
        }

        if (!_mediaParts.video.empty() && !_mediaParts.voice.empty() &&
                !_mediaParts.output.empty() && !_line.ReplaceSound().empty() &&
                !_line.Save_translation_no_merge()) {
            std::string const command{
                std::format(
                            "ffmpeg -i \"{0}\" -i \"{1}\" -i \"{2}\" -filter_complex \"[1:a]volume={4}[a1]; [2:a]volume={3}[a2]; "
                            "[a1][a2]amix=inputs=2:duration=first:dropout_transition=0:normalize=1[a]\" -map 0:v -map \"[a]\" {7} -y \"{5}.{6}\"",
                            _mediaParts.video.string(),
                            !_line.ReplaceTranslate().empty() ? _line.ReplaceTranslate().string() : _mediaParts.voice.string(),
                            _line.ReplaceSound().string(),
                            std::format(std::locale("en_US.utf8"), "{}", _line.Vol_audio()),
                            std::format(std::locale("en_US.utf8"), "{}", _line.Vol_translate()),
                            _mediaParts.output.string(),
                            extensionVideo,
                            subtitles
                            )};

            debugln("Command merge [video + voice + replace audio + subtitles]: {}", command);
            result = std::system(command.c_str());
            debugln("Result: {}", result);

            if(!result){
                if (fs::remove(_mediaParts.video))
                    _mediaParts.video.clear();
                if ((!_line.Save_translation() || !_line.Save_translation_no_merge()) && fs::remove(_mediaParts.voice))
                    _mediaParts.voice.clear();
                if (fs::remove(_mediaParts.subtitles))
                    _mediaParts.subtitles.clear();
            }
        }

        if (!_mediaParts.video.empty() && !_mediaParts.output.empty() &&
                !_line.ReplaceSound().empty() && _line.Save_translation_no_merge()) {
            std::string const command{
                std::format(
                            "ffmpeg -i \"{0}\" -i \"{1}\" -map 0:v -map 1:a -filter:a \"volume={2}\" {5} -shortest -y \"{3}.{4}\"",
                            _mediaParts.video.string(),
                            _line.ReplaceSound().string(),
                            std::format(std::locale("en_US.utf8"), "{}", _line.Vol_audio()),
                            _mediaParts.output.string(),
                            extensionVideo,
                            subtitles
                            )};

            debugln("Command merge [video + replace audio + subtitles + save translation without merge]: {}", command);
            result = std::system(command.c_str());
            debugln("Result: {}", result);

            if(!result){
                if (fs::remove(_mediaParts.video))
                    _mediaParts.video.clear();
                if (!_line.Save_translation() && !_line.Save_translation_no_merge() && fs::remove(_mediaParts.voice))
                    _mediaParts.voice.clear();
                if (fs::remove(_mediaParts.subtitles))
                    _mediaParts.subtitles.clear();
            }
        }

        if (!_mediaParts.video.empty() && !_mediaParts.output.empty() &&
                !_mediaParts.subtitles.empty() && !_line.ReplaceSound().empty() &&
                _line.Save_translation_no_merge()) {
            std::string const command{
                std::format(
                            "ffmpeg -i \"{0}\" {3} -y \"{1}.{2}\"",
                            _mediaParts.video.string(),
                            _mediaParts.output.string(),
                            extensionVideo,
                            _line.Write_subs() && !_mediaParts.subtitles.filename().string().empty() ? "-b:v " +
                                (a.has_value() ? std::format(std::locale("en_US.utf8"), "{}", f.size > 0 ? f.size * 8 : f.tbr * 8) : "2M") +
                              " -vf subtitles=" + _mediaParts.subtitles.filename().string() : "-c copy"
                            )};

            debugln("Command merge [video + subtitles + save translation without merge]: {}", command);
            result = std::system(command.c_str());
            debugln("Result: {}", result);

            if(!result){
                if (fs::remove(_mediaParts.video))
                    _mediaParts.video.clear();
                if (!_line.Save_translation() && !_line.Save_translation_no_merge() && fs::remove(_mediaParts.voice))
                    _mediaParts.voice.clear();
                if (fs::remove(_mediaParts.subtitles))
                    _mediaParts.subtitles.clear();
            }
        }

        if(!_line.Save_translation_contaner().empty() && !_mediaParts.voice.empty()
                && _mediaParts.voice.filename().extension() != "." + _line.Save_translation_contaner()){

            std::string const command{
                std::format(
                            "ffmpeg -i \"{0}\" -map 0:a -b:a 180K -y \"{1}_translate_.{2}\"",
                            _mediaParts.voice.string(),
                            _mediaParts.output.string(),
                            _line.Save_translation_contaner()
                            )};

            debugln("Command merge [change translation contaner]: {}", command);
            result = std::system(command.c_str());
            debugln("Result: {}", result);

            if(!result){
                _mediaParts.voice = _mediaParts.output.string() + "_translate_." + _line.Save_translation_contaner();
            }

        }

        return result;
    };

    // TODO Указать дополнительные ключи
    ///////////////////////////////////////////////////////////////////////
    /// Drop if exist
    /// ///////////////////////////////////////////////////////////////////
    if(_line.NoOverwrites() && !_line.TranslationOnly() && !_mediaParts.video.empty() && fs::exists(_line.Output()->GetPathToSave() / (_mediaParts.output.string() + "." + extensionVideo))){
        std::cout << "The [" << _mediaParts.output.filename().string() + "." + extensionVideo << "] file already exists. Drop operation\n";
        return;
    }
    if(_line.NoOverwrites() && !_mediaParts.voice.empty() && fs::exists(_line.Output()->GetPathToSave() / (_mediaParts.output.string() + "_translate_.." +
                    (!_line.Save_translation_contaner().empty() ? _line.Save_translation_contaner() : "mp3")))){
        std::cout << "The [" << _mediaParts.output.string() + "_translate_.." +
                                 (!_line.Save_translation_contaner().empty() ? _line.Save_translation_contaner() : "mp3") << "] file already exists. Drop operation\n";
        return;
    }
    if(_line.NoOverwrites() && _line.Write_subs() && !_mediaParts.subtitles.empty() && fs::exists(_line.Output()->GetPathToSave() / (_mediaParts.output.string() + "_subtitles_..srt"))){
        std::cout << "The [" << _mediaParts.output.string() + "_translate_..srt" << "] file already exists. Drop operation\n";
        return;
    }

    if( !merge() ) return;

    ///////////////////////////////////////////////////////////////////////////
    /// MOVE //////////////////////////////////////////////////////////////////
    /// ///////////////////////////////////////////////////////////////////////
    for (const auto &entry :
         fs::directory_iterator(_line.Output()->GetPathToTemp())) {
        if (entry.path().filename().string().contains(_mediaParts.output.string()) &&
                entry.path().filename().extension().string() == "." + (!_line.MergeOutputExtension().empty()
                       ? _line.MergeOutputExtension() : _line.Extension()) && !entry.path().string().contains("_translate_")) {
            _mediaParts.video = entry.path();
            debugln("video: {}", _mediaParts.video.filename().string());
        }
    }

    if (_line.TranslationOnly())
        _mediaParts.video = _mediaParts.voice;

    if (_mediaParts.video.empty())
        throw std::runtime_error("Not inicialiset video object");

    std::error_code ec;
    if (!_line.NoOverwrites()) {
        fs::rename(_mediaParts.video, _line.Output()->GetPathToSave() /
                   (_mediaParts.output.filename().string() + _mediaParts.video.filename().extension().string()),
                   ec);

        if (_line.Save_translation() || _line.Save_translation_no_merge()) {
            fs::rename(_mediaParts.voice, _line.Output()->GetPathToSave() /
                       (_mediaParts.output.filename().string() + "_translate_" + _mediaParts.voice.filename().extension().string()),
                       ec);
        }
    }

    if (ec) {
        std::cerr << ec.message() << " : " << ec.value() << "\n";
        if (!_line.NoOverwrites()) {
            fs::copy_file(_mediaParts.video, _line.Output()->GetPathToSave() /
                          (_mediaParts.output.filename().string() + _mediaParts.video.filename().extension().string()),
                          fs::copy_options::overwrite_existing);

            if (_line.Save_translation() || _line.Save_translation_no_merge()) {
                fs::rename(_mediaParts.voice, _line.Output()->GetPathToSave() /
                           (_mediaParts.output.filename().string() + "_translate_" + _mediaParts.voice.filename().extension().string()),
                           ec);
            } else {
                fs::copy_file(_mediaParts.video, _line.Output()->GetPathToSave() /
                              (_mediaParts.output.filename().string() + _mediaParts.video.filename().extension().string()),
                              fs::copy_options::skip_existing);

                if (_line.Save_translation() || _line.Save_translation_no_merge()) {
                    fs::rename(_mediaParts.voice, _line.Output()->GetPathToSave() /
                               (_mediaParts.output.filename().string() + "_translate_" + _mediaParts.voice.filename().extension().string()),
                               ec);
                }
            }
            if (fs::remove(_mediaParts.video)) {
                debugln("File: {} successfully deleted after copying", _mediaParts.video.string());
            } else {
                debugln("File: {}  not removed", _mediaParts.video.string());
            }
            if (fs::remove(_mediaParts.voice)) {
                debugln("File: {} successfully deleted after copying", _mediaParts.output.string() + _mediaParts.voice.extension().string());
            } else {
                debugln("File: {} not removed", _mediaParts.output.string() + _mediaParts.voice.extension().string());
            }
        }
    }

    std::cout << "The [" + _mediaParts.video.filename().string() + "] file has been successfully created\n";
    std::cout << "The [" + _mediaParts.output.filename().string() + "_translate_" + _mediaParts.voice.filename().extension().string() + "] file has been successfully created\n";
}

dtv::Cmd::Cmd(const CommandLine &line) : _line{line} {}

bool dtv::Cmd::ExecAfter() {
    debugln("Func: {}", __func__);
    if (!_line.Exec_after().empty()) {
        int result{-1};
        debugln("ExecAfter cmd: {}", _line.Exec_after());
        result = system(_line.Exec_after().c_str());
        debugln("ExecAfter result: {}", result);

        if (result == 0)
            return true;
        else
            return false;
    }
    return bool(false);
}

bool dtv::Cmd::ExecBefore() {
    debugln("Func: {}", __func__);
    if (!_line.Exec_before().empty()) {
        int result{-1};
        debugln("ExecBefore cmd: {}", _line.Exec_before());
        result = system(_line.Exec_before().c_str());
        debugln("ExecBefore result: {}", result);

        if (result == 0)
            return true;
        else
            return false;
    }
    return bool(false);
}
