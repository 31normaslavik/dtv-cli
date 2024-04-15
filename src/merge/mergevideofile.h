#pragma once


#include "fs_directories.h"
#include "video.h"

#include <memory>

namespace dtv {

class Source;


class MergeVideoFile {
public:
    explicit MergeVideoFile(std::shared_ptr<dtv::Video> video_ptr, std::shared_ptr<dtv::FsDirectories> path_ptr);

    ~MergeVideoFile();


    /**
     * @brief Init
     */
    void Init();

private:

    // NOTE Создавать папку при скачивании плейлиста
    /**
     * @brief MoveOnDisk
     */
    void MoveOnDisk();

    /**
     * @brief Merges all thre audio tracks of a video
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

    std::shared_ptr<dtv::Video> video_ptr_;
    std::shared_ptr<dtv::FsDirectories> path_ptr_;
    std::shared_ptr<std::vector<Source>> resources_ptr_;

    // FIXME Поменять string на filesystem?
    struct SplitVideoData {
        std::string video_;
        std::string voice_;
        std::string audio_;
        std::string output_;
        std::string extension_;
        std::string tempf_;
    } split_video_;
};

} // namespace dtv
