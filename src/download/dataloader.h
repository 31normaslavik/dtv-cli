#pragma once

#include "fs_directories.h"
#include "video.h"

namespace dtv {

class DataLoader {
public:
    explicit DataLoader(const std::vector< std::string > &urls,
                        std::shared_ptr<FsDirectories> path_ptr, const std::string &format);

    /**
         * \brief
         * \return Info aboout all videos.
         */
    [[nodiscard]] std::shared_ptr<dtv::VectorPtrVideos> VideoData();

private:
    /**
        * \brief Generating json files for each video.
                 If the link leads to a playlist, a separate
                 json file will be created for each video

         * \param urls creates a set of urls to download
         */
    void DownloadJsonsToDisk(const std::vector<std::string> &urls) const;

    /**
         * \brief
         * \return read vector of path to json files on disk
         */
    [[nodiscard]] std::vector<std::filesystem::directory_entry> CreateListJsonFromDisk() const;

    /**
        * \brief Populates a VideoData object from json
        *         files on disk, which stores information
        *         about each video from json files on disk
        */
    void FillingInVideoData();

    std::string createFormatForUrl(const std::string & url);


    std::shared_ptr<FsDirectories> path_ptr_;
    std::shared_ptr<dtv::VectorPtrVideos> video_data_ptr_;
    std::string format_;

};


} // namespace dtv
