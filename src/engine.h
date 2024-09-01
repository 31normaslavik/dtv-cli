#pragma once
#include "commandline.h"
#include "video.h"

namespace dtv {

class YtdlpEngine;
class VotcliEngine;
class FfmpegEngine;

class Engine
{
public:
    explicit Engine(const Video& video, const CommandLine &line);

    // Yt-dlp
    static void DownloadJson(boost::urls::url_view url);
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

    struct SplitVideoData {
        fs::path video;
        fs::path voice;
        fs::path audio;
        fs::path output;
        fs::path subtitles;
    } _split_video;
};

} // namespace dtv
