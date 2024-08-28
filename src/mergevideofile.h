#pragma once


#include "video.h"
#include "commandline.h"

namespace dtv {

class Source;


class MergeVideoFile {
public:
    explicit MergeVideoFile(Video& video, CommandLine const& line);

    ~MergeVideoFile();

    /**
     * @brief A video file, an audio file, and an audio translation file are initialized.
     * A name is formed for the resulting media file.
     * Then the procedure for merging files is started and moving the result to the specified
     * directory by the user
     */
    void Processing();

private:

    // TODO Создавать папку при скачивании плейлиста
    /**
     * @brief Moving the finished video from the temporary folder to the
     * one initially specified by the user when launching the program
     */
    void MoveOnDisk();

    /**
     * @brief Merge all available media files into one
     */
    void MergeFfmpeg();

    void InitVideo();
    void InitVoice();
    void InitAudio();
    void InitOutput();
    void InitSubtitles();

    Video& _video;
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
