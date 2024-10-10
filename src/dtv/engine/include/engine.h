#pragma once
#include "commandline.h"
#include "video.h"
#include <boost/url.hpp>

namespace dtv {

class YtdlpEngine;
class VotcliEngine;
class FfmpegEngine;
class Cmd;

class Engine
{
public:
    explicit Engine(const Video& video, const CommandLine &line);

    // Yt-dlp
    static void DownloadJson(const boost::urls::url_view url);
    void DownloadVideo();
    void DownloadSubtitles();
    // vot-cli
    void DownloadVoice();
    void DownloadAnotation();
    // Ffmpeg
    void Merge();

private:
    std::unique_ptr<YtdlpEngine > _pYtdlpEngine;
    std::unique_ptr<VotcliEngine> _pVotcliEngine;
    std::unique_ptr<FfmpegEngine> _pFfmpegEngine;
    std::unique_ptr<Cmd>          _pCmd;

};

class YtdlpEngine final{
public:
    explicit YtdlpEngine(const Video &video, const CommandLine &line);
    void DownloadVideo();
    void DownloadSubtitles();
private:
    Video       const& _video;
    CommandLine const& _line;
};

class VotcliEngine final{
public:
    explicit VotcliEngine(const Video &video, const CommandLine &line);
    void DownloadVoice();
    void DownloadSubtitles();
private:
    Video       const& _video;
    CommandLine const& _line;
};

class FfmpegEngine final{
public:
    explicit FfmpegEngine(const Video &video, const CommandLine &line);
    void Merge();
private:
    Video       const& _video;
    CommandLine const& _line;

    struct MediaParts {
        fs::path video;
        fs::path voice;
        fs::path audio;
        fs::path output;
        fs::path subtitles;
    } _mediaParts;
};

class Cmd final{
public:
    explicit Cmd(const CommandLine &line);
    bool ExecAfter();
    bool ExecBefore();
private:
    CommandLine const& _line;
};
} // namespace dtv
