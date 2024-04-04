#include "../command/commandline.h"
#include "../fs/fs_directories.h"
#include "../interface/video.h"

#pragma once


namespace dtv {



class DataLoader {
public:
    explicit DataLoader(const std::set<Source,cmpSource>& urls,
                        std::shared_ptr<FsDirectories> path);

    /**
         * \brief
         * \return Info aboout all videos.
         */
    std::shared_ptr<dtv::VideoData> VideoData();

private:
    /**
        * \brief Generating json files for each video.
                 If the link leads to a playlist, a separate
                 json file will be created for each video

         * \param urls creates a set of urls to download
         */
    void DownloadJsonsToDisk(const std::set<Source, cmpSource> &urls) const;

    /**
         * \brief
         * \return read vector of path to json files on disk
         */
    [[nodiscard]] std::vector<std::filesystem::directory_entry> JsonListOnDisk() const;

    /**
        * \brief Populates a VideoData object from json
        *         files on disk, which stores information
        *         about each video from json files on disk
        */
    void FillingInVideoData();

    std::shared_ptr<FsDirectories> path_;
    std::shared_ptr<dtv::VideoData> video_data_;
};


} // namespace dtv
