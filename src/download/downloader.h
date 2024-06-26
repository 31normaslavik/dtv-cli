#pragma once

#include "commandline.h"
#include "dataloader.h"
#include "fs_directories.h"
#include "video.h"

namespace dtv {

    /**
     * @brief The Downloader class
     */
    class Downloader {
    public:
        explicit Downloader(const CommandLine &line);

        //~Downloader() = default;

        void DownloadVideosWithTranslate(const std::string &language = "ru", bool subtitles = false);

    private:
        std::shared_ptr<FsDirectories> path_ptr_;
        std::shared_ptr<DataLoader> data_loader_ptr_;
        std::vector<std::shared_ptr<Video>> videos_ptr_;
        CommandLine line_;
    };

} // namespace dtv

