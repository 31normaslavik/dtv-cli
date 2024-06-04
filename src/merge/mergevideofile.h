#pragma once


#include "video.h"
#include "../command/commandline.h"

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

    // NOTE Создавать папку при скачивании плейлиста
    /**
     * @brief Moving the finished video from the temporary folder to the
     * one initially specified by the user when launching the program
     */
    void MoveOnDisk();

    /**
     * @brief Merge all available media files into one
     */
    void MergeFfmpeg();



    /**
     * @brief InitVideo
     */
    void InitVideo();

    /**
     * @brief InitVoice
     */
    void InitVoice();

    /**
     * @brief InitAudio
     */
    void InitAudio();

    /**
     * @brief InitOutput
     */
    void InitOutput();

    Video& _video;
    CommandLine const& _line;

    struct SplitVideoData {
        fs::path video_;
        fs::path voice_;
        fs::path audio_;
        fs::path output_;
        fs::path extension_;
        fs::path tempf_;
    } split_video_;
};

} // namespace dtv
