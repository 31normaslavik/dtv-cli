#pragma once

#include "commandline.h"
#include "video.h"

namespace dtv {

/**
     * \brief Download part of one video.
     */
class DownloadingMedia {
public:

    explicit DownloadingMedia(Video &video, CommandLine const& line);

    void Download();

private:
    /**
        * \brief Using yt_dlp to download a specific video and audio
        *         file to disk with the selected quality.
        *         The video and audio tracks will be
        *         downloaded to the disk separately.
         */
    void DownloaderYtDlp();

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
         * \param source
         * \param language language of the audio track
         * \param subtitles subtitle of the audio track
         * \return if the files are downloaded
         *           successfully, 0 is returned,
         *           otherwise 1
         */
    void DownloaderVotCli();

    Video& _video;
    CommandLine const& _line;
};

} // namespace dtv
