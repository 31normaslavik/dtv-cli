//
// Created by pancake on 12/12/23.
//
#pragma once

#include "fs_directories.h"
#include "interface.h"
#include "presentation.h"

#include <set>

namespace dtv {
    class DataLoader {
    public:
        explicit DataLoader(const std::set<std::string>& urls,
                            std::shared_ptr<FsDirectories> path);

        /**
         * \brief
         * \return Info aboout all videos.
         */
        std::shared_ptr<VideoData> get_video_data();

    private:
        /**
        * \brief Generating json files for each video.
                 If the link leads to a playlist, a separate
                 json file will be created for each video

         * \param urls creates a set of urls to download
         */
        void create_json(const std::set<std::string>& urls) const;

        /**
         * \brief
         * \return read vector of path to json files on disk
         */
        [[nodiscard]] std::vector<std::filesystem::directory_entry> read_json() const;

        /**
        * \brief Populates a VideoData object from json
        *         files on disk, which stores information
        *         about each video from json files on disk
        */
        void fill_video_data();

        std::shared_ptr<FsDirectories> path_;
        std::shared_ptr<VideoData> video_data_;
    };

    /**
     * \brief Download part of one video.
     */
    class SplitMediaFilesDownloader {
    public:
        explicit SplitMediaFilesDownloader(std::shared_ptr<Video> video,
            std::shared_ptr<FsDirectories> path,
            const FORMAT_VIDEO& format);

        void download_video();

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
        int yt_dlp_downloader(const std::string& url, const FORMAT_VIDEO& format);

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
        int vot_cli_downloader(const std::string& url, const std::string& language = "ru", bool subtitles = false);

        std::shared_ptr<FsDirectories> path_;
        std::shared_ptr<Video> video_;
        FORMAT_VIDEO format_;
    };



    class MergeVideoFile {
    public:
        explicit MergeVideoFile(std::shared_ptr<Video> video, std::shared_ptr<FsDirectories> path);

        ~MergeVideoFile();

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
        int ffmpeg_merge(const std::string& video, const std::string& voice,
                         const std::string& audio, const std::string& output);

        void init_video();
        void init_voice();
        void init_audio();
        void init_output();

        std::shared_ptr<Video> video_;
        std::shared_ptr<FsDirectories> path_;

        struct SplitVideoData {
            std::string video;
            std::string voice;
            std::string audio;
            std::string output;
        } split_video_;
    };

    class Downloader {
        public:
        explicit Downloader(const std::set<std::string>& urls, const std::filesystem::path& pathToSave,
        const std::string& format);

        ~Downloader() = default;

        void download_videos();
        void download_videos_with_translate(const std::string& language = "ru", bool subtitles = false);

    private:
        //std::shared_ptr<VideoData> video_data_;
        std::shared_ptr<FsDirectories> path_;
        std::shared_ptr<DataLoader> data_loader_;
        //std::shared_ptr<MergeVideoFile> merge_video_file_;
        //std::shared_ptr<SplitMediaFilesDownloader> split_media_files_downloader_;
        //std::shared_ptr<Video> video_;
        std::vector<std::shared_ptr<Video>> videos_;
        std::string format_;
    };
} // dtv

