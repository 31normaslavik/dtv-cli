//
// Created by pancake on 12/14/23.
//
#include "presentation.h"
#include <map>
#include <stdexcept>

dtv::Format::FORMAT_VIDEO dtv::Format::format_video_argv(const std::string& format, const std::string& resource) {
    using FORMAT_VIDEO = dtv::Format::FORMAT_VIDEO;

    /* YOUTUBE format resolution fps HDR*/
    if(resource == "youtube"){
        if (const std::map<std::string, dtv::Format::FORMAT_VIDEO> exts{
            {"mp4_4320_60_10", FORMAT_VIDEO::MP4_7680x4320_60_10},
            {"mp4_2160_60_10", FORMAT_VIDEO::MP4_3840x2160_60_10},
            {"mp4_2160_30", FORMAT_VIDEO::MP4_3840x2160_30},
            {"mp4_1440_60_10", FORMAT_VIDEO::MP4_2560x1440_60_10},
            {"mp4_1440_30", FORMAT_VIDEO::MP4_2560x1440_30},
            {"mp4_1080_60_10", FORMAT_VIDEO::MP4_1920x1080_60_10},
            {"mp4_1080_60", FORMAT_VIDEO::MP4_1920x1080_60},
            {"mp4_1080_30", FORMAT_VIDEO::MP4_1920x1080_30},
            {"mp4_720_60_10", FORMAT_VIDEO::MP4_1280x720_60_10},
            {"mp4_720_60", FORMAT_VIDEO::MP4_1280x720_60},
            {"mp4_720_30", FORMAT_VIDEO::MP4_1280x720_30},
            {"mp4_480_60_10", FORMAT_VIDEO::MP4_854x480_60_10},
            {"mp4_480_30", FORMAT_VIDEO::MP4_854x480_30},
            {"mp4_360_60_10", FORMAT_VIDEO::MP4_640x360_60_10},
            {"mp4_360_30", FORMAT_VIDEO::MP4_640x360_30},
            {"webm_2160_60_10", FORMAT_VIDEO::WEBM_3840x2160_60_10},
            {"webm_2160_60", FORMAT_VIDEO::WEBM_3840x2160_60},
            {"webm_2160_30", FORMAT_VIDEO::WEBM_3840x2160_30},
            {"webm_1440_60_10", FORMAT_VIDEO::WEBM_2560x1440_60_10},
            {"webm_1440_60", FORMAT_VIDEO::WEBM_2560x1440_60},
            {"webm_1440_30", FORMAT_VIDEO::WEBM_2560x1440_30},
            {"webm_1080_60_10", FORMAT_VIDEO::WEBM_1920x1080_60_10},
            {"webm_1080_60", FORMAT_VIDEO::WEBM_1920x1080_60},
            {"webm_1080_30", FORMAT_VIDEO::WEBM_1920x1080_30},
            {"webm_720_60_10", FORMAT_VIDEO::WEBM_1280x720_60_10},
            {"webm_720_60", FORMAT_VIDEO::WEBM_1280x720_60},
            {"webm_720_30", FORMAT_VIDEO::WEBM_1280x720_30},
            {"webm_480_60_10", FORMAT_VIDEO::WEBM_854x480_60_10},
            {"webm_480_30", FORMAT_VIDEO::WEBM_854x480_30},
            {"webm_360_60_10", FORMAT_VIDEO::WEBM_640x360_60_10},
            {"webm_360_30", FORMAT_VIDEO::WEBM_640x360_30},
            }; exts.contains(format))
            return exts.at(format);
    } else

    /*9GAG format resolution ID*/
    if (resource == "9gag") {
        const std::map<std::string, dtv::Format::FORMAT_VIDEO> exts{
            {"mp4_460_460sv", FORMAT_VIDEO::MP4_460x816_460sv},
            {"mp4_460_460sv_h265", FORMAT_VIDEO::MP4_460x816_460sv_h265},
            {"webm_460_460sv_vp8", FORMAT_VIDEO::WEBM_460x816_460sv_vp8},
            {"webm_460_460sv_vp9", FORMAT_VIDEO::WEBM_460x816_460sv_vp9},
            };
        std::string frmt;
        if(format.find("mp4") != std::string::npos){
             frmt = "mp4_460_460sv_h265";
        }else if (format.find("webm") != std::string::npos){
             frmt = "webm_460_460sv_vp9";
        }

        if(exts.contains(frmt))
            return exts.at(frmt);
    }

    return FORMAT_VIDEO::UNKNOWNV;
}

std::string dtv::Format::combinate_format(const dtv::Format::FORMAT_VIDEO& format) {
    using FORMAT_VIDEO = dtv::Format::FORMAT_VIDEO;
    std::string format_to_string;
    bool is_mp4 = false;

    switch (format) {
    /* YOUTUBE */
    case FORMAT_VIDEO::MP4_7680x4320_60_10: format_to_string.
            append(std::to_string(static_cast<int>(FORMAT_VIDEO::MP4_7680x4320_60_10)).append("/"));
    case FORMAT_VIDEO::MP4_3840x2160_60_10: format_to_string.
            append(std::to_string(static_cast<int>(FORMAT_VIDEO::MP4_3840x2160_60_10)).append("/"));
    case FORMAT_VIDEO::MP4_3840x2160_30: format_to_string.
            append(std::to_string(static_cast<int>(FORMAT_VIDEO::MP4_3840x2160_30)).append("/"));
    case FORMAT_VIDEO::MP4_2560x1440_60_10: format_to_string.
            append(std::to_string(static_cast<int>(FORMAT_VIDEO::MP4_2560x1440_60_10)).append("/"));
    case FORMAT_VIDEO::MP4_2560x1440_30: format_to_string.
            append(std::to_string(static_cast<int>(FORMAT_VIDEO::MP4_2560x1440_30)).append("/"));
    case FORMAT_VIDEO::MP4_1920x1080_60_10: format_to_string.
            append(std::to_string(static_cast<int>(FORMAT_VIDEO::MP4_1920x1080_60_10)).append("/"));
    case FORMAT_VIDEO::MP4_1920x1080_60: format_to_string.
            append(std::to_string(static_cast<int>(FORMAT_VIDEO::MP4_1920x1080_60)).append("/"));
    case FORMAT_VIDEO::MP4_1920x1080_30: format_to_string.
            append(std::to_string(static_cast<int>(FORMAT_VIDEO::MP4_1920x1080_30)).append("/"));
    case FORMAT_VIDEO::MP4_1280x720_30: format_to_string.
            append(std::to_string(static_cast<int>(FORMAT_VIDEO::MP4_1280x720_30)).append("/"));
    case FORMAT_VIDEO::MP4_854x480_30: format_to_string.
            append(std::to_string(static_cast<int>(FORMAT_VIDEO::MP4_854x480_30)).append("/bestvideo,"));


        is_mp4 = true;

    /* YOUTUBE */
    case FORMAT_VIDEO::WEBM_3840x2160_60_10: format_to_string.
            append(std::to_string(static_cast<int>(FORMAT_VIDEO::WEBM_3840x2160_60_10)).append("/"));
    case FORMAT_VIDEO::WEBM_3840x2160_60: format_to_string.
            append(std::to_string(static_cast<int>(FORMAT_VIDEO::WEBM_3840x2160_60)).append("/"));
    case FORMAT_VIDEO::WEBM_3840x2160_30: format_to_string.
            append(std::to_string(static_cast<int>(FORMAT_VIDEO::WEBM_3840x2160_30)).append("/"));
    case FORMAT_VIDEO::WEBM_2560x1440_60_10: format_to_string.
            append(std::to_string(static_cast<int>(FORMAT_VIDEO::WEBM_2560x1440_60_10)).append("/"));
    case FORMAT_VIDEO::WEBM_2560x1440_60: format_to_string.
            append(std::to_string(static_cast<int>(FORMAT_VIDEO::WEBM_2560x1440_60)).append("/"));
    case FORMAT_VIDEO::WEBM_2560x1440_30: format_to_string.
            append(std::to_string(static_cast<int>(FORMAT_VIDEO::WEBM_2560x1440_30)).append("/"));
    case FORMAT_VIDEO::WEBM_1920x1080_60_10: format_to_string.
            append(std::to_string(static_cast<int>(FORMAT_VIDEO::WEBM_1920x1080_60_10)).append("/"));
    case FORMAT_VIDEO::WEBM_1920x1080_60: format_to_string.
            append(std::to_string(static_cast<int>(FORMAT_VIDEO::WEBM_1920x1080_60)).append("/"));
    case FORMAT_VIDEO::WEBM_1920x1080_30: format_to_string.
            append(std::to_string(static_cast<int>(FORMAT_VIDEO::WEBM_1920x1080_30)).append("/"));
    case FORMAT_VIDEO::WEBM_1280x720_30: format_to_string.
            append(std::to_string(static_cast<int>(FORMAT_VIDEO::WEBM_1280x720_30)).append("/"));
    case FORMAT_VIDEO::WEBM_854x480_30: {
        format_to_string.
            append(std::to_string(static_cast<int>(FORMAT_VIDEO::WEBM_854x480_30)).append("/bestvideo,"));
        if (is_mp4) format_to_string.append("140/139/599/bestaudio");
        else format_to_string.append("251/250/249/600/bestaudio");
        break;
    }

    /* 9GAG */
    case FORMAT_VIDEO::MP4_460x816_460sv_h265: format_to_string.append("460sv-h265").append("/");
    case FORMAT_VIDEO::MP4_460x816_460sv: format_to_string.append("460sv").append("/");
    case FORMAT_VIDEO::WEBM_460x816_460sv_vp9: format_to_string.append("460sv-vp9").append("/");
    case FORMAT_VIDEO::WEBM_460x816_460sv_vp8: format_to_string.append("460sv-vp8").append("/b*");
        break;

    default: throw std::runtime_error("[combinate_format] Wrong video format!");
        break;
    }

    if(format_to_string.empty())
        throw std::runtime_error("[combinate_format] Empty \"format_to_string\"!");
    return format_to_string;
}
