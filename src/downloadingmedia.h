#include "commandline.h"
#include "fs_directories.h"

#include <string>
#include <vector>

#pragma once


namespace dtv {



/**
     * \brief Download part of one video.
     */
class DownloadingMedia {
public:
    explicit DownloadingMedia(std::vector<Source> resources);

    void Download();

private:
    /**
        * \brief Using yt_dlp to download a specific video and audio
        *         file to disk with the selected quality.
                  The video and audio tracks will be
                  downloaded to the disk separately.
         * \param url link to specific video
         * \param format format for selecting the quality
         *              and format of video and audio
         * \return if the files are downloaded
         *          successfully, 0 is returned,
         *          otherwise 1
         */
    int DownloaderYtDlp(const Source &source);

    /**
         * \brief Using the Yandex api to download a translation
         *          of an audio track into:
         * ru - Russian,
         * en - English,
         * zh - Chinese,
         * ko - Korean,
         * ar - Arabic,
         * fr - French,
         * it - Italian,
         * es - Spanish,
         * de - German,
         * ja - Japanese
         *
         * Translation language:
         * ru - Russian,
         * en - English,
         * kk - Kazakh
         *
         * \param url link to specific video
         * \param language language of the audio track
         * \param subtitles subtitle of the audio track
         * \return if the files are downloaded
         *           successfully, 0 is returned,
         *           otherwise 1
         */
    int DownloaderVotCli(const Source &source, const std::string& language = "ru", bool subtitles = false);

    std::shared_ptr<FsDirectories> path_;
    std::vector<Source> resources_;
};

} // namespace dtv
