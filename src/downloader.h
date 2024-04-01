//
// Created by pancake on 12/12/23.
//
#pragma once

#include "dataloader.h"
#include "fs_directories.h"
#include "interface/interface.h"
#include "commandline.h"

#include <set>

namespace dtv {

    class Downloader {
    public:
        Downloader(const Downloader &) = default;
        Downloader(Downloader &&) = delete;
        Downloader &operator=(const Downloader &) = default;
        Downloader &operator=(Downloader &&) = delete;
        explicit Downloader(const CommandLine &line);

        ~Downloader() = default;

        //void DownloadVideos();
        void DownloadVideosWithTranslate(const std::string &language = "ru", bool subtitles = false);

    private:
        std::shared_ptr<FsDirectories> path_;
        std::shared_ptr<DataLoader> data_loader_;
        std::vector<std::shared_ptr<Video>> videos_;
        std::vector<Source> resources_;
    };
} // dtv

