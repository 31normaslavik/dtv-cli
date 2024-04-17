#include "presentation.h"
#include <map>
#include <stdexcept>
#include <utility>
#include <string>
#include <sstream>

dtv::FormatVideo dtv::Format::FormatVideoFromString(const std::string &format) {
    std::map<std::string, FormatVideo> exts{
        {"format_134", FormatVideo::MP4_640x360_30},
        {"format_243", FormatVideo::WEBM_640x360_30},
        {"format_696", FormatVideo::MP4_640x360_60_10},
        {"format_332", FormatVideo::WEBM_640x360_60_10},
        {"format_135", FormatVideo::MP4_854x480_30},
        {"format_244", FormatVideo::WEBM_854x480_30},
        {"format_697", FormatVideo::MP4_854x480_60_10},
        {"format_333", FormatVideo::WEBM_854x480_60_10},
        {"format_136", FormatVideo::MP4_1280x720_30},
        {"format_247", FormatVideo::WEBM_1280x720_30},
        {"format_298", FormatVideo::MP4_1280x720_60},
        {"format_302", FormatVideo::WEBM_1280x720_60},
        {"format_698", FormatVideo::MP4_1280x720_60_10},
        {"format_334", FormatVideo::WEBM_1280x720_60_10},
        {"format_137", FormatVideo::MP4_1920x1080_30},
        {"format_248", FormatVideo::WEBM_1920x1080_30},
        {"format_299", FormatVideo::MP4_1920x1080_60},
        {"format_303", FormatVideo::WEBM_1920x1080_60},
        {"format_699", FormatVideo::MP4_1920x1080_60_10},
        {"format_335", FormatVideo::WEBM_1920x1080_60_10},
        {"format_400", FormatVideo::MP4_2560x1440_30},
        {"format_271", FormatVideo::WEBM_2560x1440_30},
        {"format_308", FormatVideo::WEBM_2560x1440_60},
        {"format_700", FormatVideo::MP4_2560x1440_60_10},
        {"format_336", FormatVideo::WEBM_2560x1440_60_10},
        {"format_401", FormatVideo::MP4_3840x2160_30},
        {"format_313", FormatVideo::WEBM_3840x2160_30},
        {"format_315", FormatVideo::WEBM_3840x2160_60},
        {"format_701", FormatVideo::MP4_3840x2160_60_10},
        {"format_337", FormatVideo::WEBM_3840x2160_60_10},
        {"format_702", FormatVideo::MP4_7680x4320_60_10},
        {"460sv",      FormatVideo::MP4_460x816_460sv},
        {"460sv-vp8",  FormatVideo::WEBM_460x816_460sv_vp8},
        {"460sv-h265", FormatVideo::MP4_460x816_460sv_h265},
        {"460sv-vp9",  FormatVideo::WEBM_460x816_460sv_vp9},
        };

    if (exts.contains(format)) {
        return exts.at(format);
    }

    return FormatVideo::UNKNOWNV;
}

dtv::FormatVideo dtv::Format::FormatVideoArgv(const std::string& format, const std::string& resource) {

    /* YOUTUBE format resolution fps HDR*/
    if(resource == "youtube"){
        if (const std::map<std::string, dtv::FormatVideo> exts{
            {"mp4_4320_60_10", FormatVideo::MP4_7680x4320_60_10},
            {"mp4_2160_60_10", FormatVideo::MP4_3840x2160_60_10},
            {"mp4_2160_30", FormatVideo::MP4_3840x2160_30},
            {"mp4_1440_60_10", FormatVideo::MP4_2560x1440_60_10},
            {"mp4_1440_30", FormatVideo::MP4_2560x1440_30},
            {"mp4_1080_60_10", FormatVideo::MP4_1920x1080_60_10},
            {"mp4_1080_60", FormatVideo::MP4_1920x1080_60},
            {"mp4_1080_30", FormatVideo::MP4_1920x1080_30},
            {"mp4_720_60_10", FormatVideo::MP4_1280x720_60_10},
            {"mp4_720_60", FormatVideo::MP4_1280x720_60},
            {"mp4_720_30", FormatVideo::MP4_1280x720_30},
            {"mp4_480_60_10", FormatVideo::MP4_854x480_60_10},
            {"mp4_480_30", FormatVideo::MP4_854x480_30},
            {"mp4_360_60_10", FormatVideo::MP4_640x360_60_10},
            {"mp4_360_30", FormatVideo::MP4_640x360_30},
            {"webm_2160_60_10", FormatVideo::WEBM_3840x2160_60_10},
            {"webm_2160_60", FormatVideo::WEBM_3840x2160_60},
            {"webm_2160_30", FormatVideo::WEBM_3840x2160_30},
            {"webm_1440_60_10", FormatVideo::WEBM_2560x1440_60_10},
            {"webm_1440_60", FormatVideo::WEBM_2560x1440_60},
            {"webm_1440_30", FormatVideo::WEBM_2560x1440_30},
            {"webm_1080_60_10", FormatVideo::WEBM_1920x1080_60_10},
            {"webm_1080_60", FormatVideo::WEBM_1920x1080_60},
            {"webm_1080_30", FormatVideo::WEBM_1920x1080_30},
            {"webm_720_60_10", FormatVideo::WEBM_1280x720_60_10},
            {"webm_720_60", FormatVideo::WEBM_1280x720_60},
            {"webm_720_30", FormatVideo::WEBM_1280x720_30},
            {"webm_480_60_10", FormatVideo::WEBM_854x480_60_10},
            {"webm_480_30", FormatVideo::WEBM_854x480_30},
            {"webm_360_60_10", FormatVideo::WEBM_640x360_60_10},
            {"webm_360_30", FormatVideo::WEBM_640x360_30},
            }; exts.contains(format))
            return exts.at(format);
    } else

    /*9GAG format resolution ID*/
    if (resource == "9gag") {
        const std::map<std::string, dtv::FormatVideo> exts{
            {"mp4_460_460sv", FormatVideo::MP4_460x816_460sv},
            {"mp4_460_460sv_h265", FormatVideo::MP4_460x816_460sv_h265},
            {"webm_460_460sv_vp8", FormatVideo::WEBM_460x816_460sv_vp8},
            {"webm_460_460sv_vp9", FormatVideo::WEBM_460x816_460sv_vp9},
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

    return FormatVideo::UNKNOWNV;
}

std::string dtv::Format::CombinateFormat(FormatVideo format, const std::string &resource) { // FIXME Для каждого ресурса сделать ветку
    std::ostringstream format_to_string;

    if (resource == "youtube"){
        switch (format) { /* YOUTUBE */
            case dtv::FormatVideo::MP4_7680x4320_60_10:
                format_to_string << std::to_underlying(FormatVideo::MP4_7680x4320_60_10) << "/";
                [[fallthrough]];
            case dtv::FormatVideo::MP4_3840x2160_60_10:
                format_to_string << std::to_underlying(FormatVideo::MP4_3840x2160_60_10) << "/";
                [[fallthrough]];
            case dtv::FormatVideo::MP4_3840x2160_30:
                format_to_string << std::to_underlying(FormatVideo::MP4_3840x2160_30)    << "/";
                [[fallthrough]];
            case dtv::FormatVideo::MP4_2560x1440_60_10:
                format_to_string << std::to_underlying(FormatVideo::MP4_2560x1440_60_10) << "/";
                [[fallthrough]];
            case dtv::FormatVideo::MP4_2560x1440_30:
                format_to_string << std::to_underlying(FormatVideo::MP4_2560x1440_30)    << "/";
                [[fallthrough]];
            case dtv::FormatVideo::MP4_1920x1080_60_10:
                format_to_string << std::to_underlying(FormatVideo::MP4_1920x1080_60_10) << "/";
                [[fallthrough]];
            case dtv::FormatVideo::MP4_1920x1080_60:
                format_to_string << std::to_underlying(FormatVideo::MP4_1920x1080_60)    << "/";
                [[fallthrough]];
            case dtv::FormatVideo::MP4_1920x1080_30:
                format_to_string << std::to_underlying(FormatVideo::MP4_1920x1080_30)    << "/";
                [[fallthrough]];
            case dtv::FormatVideo::MP4_1280x720_30:
                format_to_string << std::to_underlying(FormatVideo::MP4_1280x720_30)     << "/";
                [[fallthrough]];
            case dtv::FormatVideo::MP4_854x480_30: {
                format_to_string << std::to_underlying(FormatVideo::MP4_854x480_30)      << "/bestvideo,";
                format_to_string << "140/139/599/bestaudio";
                break;
            }

            case FormatVideo::WEBM_3840x2160_60_10:
                format_to_string << std::to_underlying(FormatVideo::WEBM_3840x2160_60_10) << "/";
                [[fallthrough]];
            case FormatVideo::WEBM_3840x2160_60:
                format_to_string << std::to_underlying(FormatVideo::WEBM_3840x2160_60)    << "/";
                [[fallthrough]];
            case FormatVideo::WEBM_3840x2160_30:
                format_to_string << std::to_underlying(FormatVideo::WEBM_3840x2160_30)    << "/";
                [[fallthrough]];
            case FormatVideo::WEBM_2560x1440_60_10:
                format_to_string << std::to_underlying(FormatVideo::WEBM_2560x1440_60_10) << "/";
                [[fallthrough]];
            case FormatVideo::WEBM_2560x1440_60:
                format_to_string << std::to_underlying(FormatVideo::WEBM_2560x1440_60)    << "/";
                [[fallthrough]];
            case FormatVideo::WEBM_2560x1440_30:
                format_to_string << std::to_underlying(FormatVideo::WEBM_2560x1440_30)    << "/";
                [[fallthrough]];
            case FormatVideo::WEBM_1920x1080_60_10:
                format_to_string << std::to_underlying(FormatVideo::WEBM_1920x1080_60_10) << "/";
                [[fallthrough]];
            case FormatVideo::WEBM_1920x1080_60:
                format_to_string << std::to_underlying(FormatVideo::WEBM_1920x1080_60)    << "/";
                [[fallthrough]];
            case FormatVideo::WEBM_1920x1080_30:
                format_to_string << std::to_underlying(FormatVideo::WEBM_1920x1080_30)    << "/";
                [[fallthrough]];
            case FormatVideo::WEBM_1280x720_30:
                format_to_string << std::to_underlying(FormatVideo::WEBM_1280x720_30)     << "/";
                [[fallthrough]];
            case FormatVideo::WEBM_854x480_30: {
                format_to_string << std::to_underlying(FormatVideo::WEBM_854x480_30)      << "/bestvideo,";
                format_to_string << "251/250/249/600/bestaudio";
                break;
            }

            default: throw std::runtime_error("[combinate_format] Wrong video format!");
                break;
        }

    } else if (resource == "9gag"){ /* 9GAG */

        switch (format) {
            case FormatVideo::MP4_460x816_460sv_h265:
                format_to_string << "460sv-h265"    << "/";
                [[fallthrough]];
            case FormatVideo::MP4_460x816_460sv:
                format_to_string << "460sv"         <<  "/";
                [[fallthrough]];
            case FormatVideo::WEBM_460x816_460sv_vp9:
                format_to_string << "460sv-vp9"     << "/";
                [[fallthrough]];
            case FormatVideo::WEBM_460x816_460sv_vp8:
                format_to_string << "460sv-vp8"     << "/b*";
            break;

            default: throw std::runtime_error("[combinate_format] Wrong video format!");
            break;
        }
    }


    if(format_to_string.str().empty())
        throw std::runtime_error("[combinate_format] Empty \"format_to_string\"!");
    return format_to_string.str();
}
