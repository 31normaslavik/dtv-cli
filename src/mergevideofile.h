#pragma once


#include "fs_directories.h"
#include "interface/interface.h"

#include <memory>

namespace dtv {


class MergeVideoFile {
public:
    explicit MergeVideoFile(std::shared_ptr<dtv::Video> video, std::shared_ptr<dtv::FsDirectories> path);

    // ~MergeVideoFile();

private:
    /**
         * \brief Merges all thre audio tracks of a video
         * \param video video file
         * \param voice voice file
         * \param audio audio file
         * \param output output file
        * \return if the files are merged successfully, 0 is returned,
         *           otherwise 1
         */
    int MergeFfmpeg(const std::string& video, const std::string& voice,
                    const std::string& audio, const std::string& output);

    void InitVideo();
    void InitVoice();
    void InitAudio();
    void InitOutput();

    std::shared_ptr<dtv::Video> video_;
    std::shared_ptr<dtv::FsDirectories> path_;

    struct SplitVideoData {
        std::string video_;
        std::string voice_;
        std::string audio_;
        std::string output_;
    } split_video_;
};

} // namespace dtv
