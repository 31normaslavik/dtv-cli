#pragma once

#include <map>
#include <stdexcept>
#include <string>


/*

ID  EXT   RESOLUTION FPS HDR CH │    FILESIZE    TBR PROTO │ VCODEC           VBR ACODEC      ABR ASR MORE INFO
────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
599 m4a   audio only          2 │     2.70MiB    31k https │ audio only           mp4a.40.5   31k 22k ultralow, m4a_dash
600 webm  audio only          2 │     3.20MiB    36k https │ audio only           opus        36k 48k ultralow, webm_dash
139 m4a   audio only          2 │     4.28MiB    49k https │ audio only           mp4a.40.5   49k 22k low, m4a_dash
249 webm  audio only          2 │     4.65MiB    53k https │ audio only           opus        53k 48k low, webm_dash
250 webm  audio only          2 │     6.20MiB    71k https │ audio only           opus        71k 48k low, webm_dash
140 m4a   audio only          2 │    11.36MiB   129k https │ audio only           mp4a.40.2  129k 44k medium, m4a_dash
251 webm  audio only          2 │    11.94MiB   136k https │ audio only           opus       136k 48k medium, webm_dash
134 mp4   640x360     30        │   40.44MiB     70k https │ avc1.4D401E      70k video only          360p, mp4_dash
396 mp4   640x360     30        │   45.76MiB     79k https │ av01.0.01M.08    79k video only          360p, mp4_dash
243 webm  640x360     30        │   72.03MiB    124k https │ vp09.00.21.08   124k video only          360p, webm_dash
696 mp4   640x360     60 10     │    47.56MiB   542k https │ av01.0.04M.10   542k video only          360p60 HDR, mp4_dash
332 webm  640x360     60 10     │    84.98MiB   969k https │ vp09.02.30.10   969k video only          360p60 HDR, webm_dash
135 mp4   854x480     30        │   61.47MiB    106k https │ avc1.4D401F     106k video only          480p, mp4_dash
397 mp4   854x480     30        │   78.83MiB    136k https │ av01.0.04M.08   136k video only          480p, mp4_dash
244 webm  854x480     30        │  119.23MiB    205k https │ vp09.00.30.08   205k video only          480p, webm_dash
135 mp4   854x480     30        │    52.05MiB   593k https │ avc1.4D401F     593k video only          480p, mp4_dash
244 webm  854x480     30        │    57.15MiB   651k https │ vp09.00.30.08   651k video only          480p, webm_dash
697 mp4   854x480     60 10     │    91.93MiB  1048k https │ av01.0.05M.10  1048k video only          480p60 HDR, mp4_dash
333 webm  854x480     60 10     │   165.11MiB  1882k https │ vp09.02.31.10  1882k video only          480p60 HDR, webm_dash
22  mp4   1280x720    30      2 │ ≈ 164.85MiB  1835k https │ avc1.64001F          mp4a.40.2       44k 720p
136 mp4   1280x720    30        │   149.68MiB  1706k https │ avc1.4d401f    1706k video only          720p, mp4_dash
398 mp4   1280x720    30        │   159.65MiB   275k https │ av01.0.05M.08   275k video only          720p, mp4_dash
247 webm  1280x720    30        │   109.58MiB  1249k https │ vp9            1249k video only          720p, webm_dash
298 mp4   1280x720    60        │   244.76MiB  2790k https │ avc1.4D4020    2790k video only          720p60, mp4_dash
302 webm  1280x720    60        │   161.58MiB  1842k https │ vp09.00.40.08  1842k video only          720p60, webm_dash
698 mp4   1280x720    60 10     │   272.68MiB  3108k https │ av01.0.08M.10  3108k video only          720p60 HDR, mp4_dash
334 webm  1280x720    60 10     │   383.21MiB  4368k https │ vp09.02.40.10  4368k video only          720p60 HDR, webm_dash
399 mp4   1920x1080   30        │   326.38MiB   562k https │ av01.0.08M.08   562k video only          1080p, mp4_dash
137 mp4   1920x1080   30        │   404.57MiB   697k https │ avc1.640028     697k video only          1080p, mp4_dash
248 webm  1920x1080   30        │   449.39MiB   774k https │ vp09.00.40.08   774k video only          1080p, webm_dash
299 mp4   1920x1080   60        │   446.58MiB  5090k https │ avc1.64002A    5090k video only          1080p60, mp4_dash
303 webm  1920x1080   60        │   317.24MiB  3616k https │ vp09.00.41.08  3616k video only          1080p60, webm_dash
699 mp4   1920x1080   60 10     │   440.16MiB  5017k https │ av01.0.09M.10  5017k video only          1080p60 HDR, mp4_dash
335 webm  1920x1080   60 10     │   588.19MiB  6704k https │ vp09.02.41.10  6704k video only          1080p60 HDR, webm_dash
400 mp4   2560x1440   30        │     1.06GiB  1871k https │ av01.0.12M.08  1871k video only          1440p, mp4_dash
271 webm  2560x1440   30        │     1.48GiB  2619k https │ vp09.00.50.08  2619k video only          1440p, webm_dash
308 webm  2560x1440   60        │  1013.92MiB 11556k https │ vp09.00.50.08 11556k video only          1440p60, webm_dash
700 mp4   2560x1440   60 10     │     1.20GiB 13956k https │ av01.0.12M.10 13956k video only          1440p60 HDR, mp4_dash
336 webm  2560x1440   60 10     │     1.37GiB 15988k https │ vp09.02.50.10 15988k video only          1440p60 HDR, webm_dash
401 mp4   3840x2160   30        │     2.36GiB  4172k https │ av01.0.12M.08  4172k video only          2160p, mp4_dash
313 webm  3840x2160   30        │     5.23GiB  9231k https │ vp09.00.50.08  9231k video only          2160p, webm_dash
315 webm  3840x2160   60        │     2.20GiB 25726k https │ vp09.00.51.08 25726k video only          2160p60, webm_dash
701 mp4   3840x2160   60 10     │     2.11GiB 24647k https │ av01.0.13M.10 24647k video only          2160p60 HDR, mp4_dash
337 webm  3840x2160   60 10     │     2.44GiB 28451k https │ vp09.02.51.10 28451k video only          2160p60 HDR, webm_dash
702 mp4   7680x4320   60 10     │     4.22GiB 49272k https │ av01.0.17M.10 49272k video only          4320p60 HDR, mp4_dash



yt-dlp url -f 136/137,140/m4a/bestaudio

yt-dlp "https://www.youtube.com/playlist?list=PLgdqWDSMoLhHQKtf5zX9Jzb0Pje4GxTpR" -f
"bv,ba" -o "%(title)s.f%(format_id)s.%(display_id)s.%(ext)s"

*/

enum class EXTENSION{MP4, M4A, MKV, WEBM, MP3, JSON, UNKNOWN};

enum FORMAT_VIDEO{
     MP4_640x360_30       = 134, //    │    30.40MiB   347k https │ avc1.4D401E     347k video only 360p, mp4_dash
     WEBM_640x360_30      = 243, //    │    30.35MiB   346k https │ vp09.00.21.08   346k video only 360p, webm_dash
     MP4_640x360_60_10    = 696, //    │    47.56MiB   542k https │ av01.0.04M.10   542k video only 360p60 HDR, mp4_dash
     WEBM_640x360_60_10   = 332, //    │    84.98MiB   969k https │ vp09.02.30.10   969k video only 360p60 HDR, webm_dash
     MP4_854x480_30       = 135, //    │    52.05MiB   593k https │ avc1.4D401F     593k video only 480p, mp4_dash
     WEBM_854x480_30      = 244, //    │    57.15MiB   651k https │ vp09.00.30.08   651k video only 480p, webm_dash
     MP4_854x480_60_10    = 697, //    │    91.93MiB  1048k https │ av01.0.05M.10  1048k video only 480p60 HDR, mp4_dash
     WEBM_854x480_60_10   = 333, //    │   165.11MiB  1882k https │ vp09.02.31.10  1882k video only 480p60 HDR, webm_dash
     MP4_1280x720_30      = 136, //    │   149.68MiB  1706k https │ avc1.4d401f    1706k video only 720p, mp4_dash
     WEBM_1280x720_30     = 247, //    │   109.58MiB  1249k https │ vp9            1249k video only 720p, webm_dash
     MP4_1280x720_60      = 298, //    │   244.76MiB  2790k https │ avc1.4D4020    2790k video only 720p60, mp4_dash
     WEBM_1280x720_60     = 302, //    │   161.58MiB  1842k https │ vp09.00.40.08  1842k video only 720p60, webm_dash
     MP4_1280x720_60_10   = 698, //    │   272.68MiB  3108k https │ av01.0.08M.10  3108k video only 720p60 HDR, mp4_dash
     WEBM_1280x720_60_10  = 334, //    │   383.21MiB  4368k https │ vp09.02.40.10  4368k video only 720p60 HDR, webm_dash
     MP4_1920x1080_30     = 137, //    │   404.57MiB   697k https │ avc1.640028     697k video only 1080p, mp4_dash
     WEBM_1920x1080_30    = 248, //    │   449.39MiB   774k https │ vp09.00.40.08   774k video only 1080p, webm_dash
     MP4_1920x1080_60     = 299, //    │   446.58MiB  5090k https │ avc1.64002A    5090k video only 1080p60, mp4_dash
     WEBM_1920x1080_60    = 303, //    │   317.24MiB  3616k https │ vp09.00.41.08  3616k video only 1080p60, webm_dash
     MP4_1920x1080_60_10  = 699, //    │   440.16MiB  5017k https │ av01.0.09M.10  5017k video only 1080p60 HDR, mp4_dash
     WEBM_1920x1080_60_10 = 335, //    │   588.19MiB  6704k https │ vp09.02.41.10  6704k video only 1080p60 HDR, webm_dash
     MP4_2560x1440_30     = 400, //    │     1.06GiB  1871k https │ av01.0.12M.08  1871k video only 1440p, mp4_dash
     WEBM_2560x1440_30    = 271, //    │     1.48GiB  2619k https │ vp09.00.50.08  2619k video only 1440p, webm_dash
     WEBM_2560x1440_60    = 308, //    │  1013.92MiB 11556k https │ vp09.00.50.08 11556k video only 1440p60, webm_dash
     MP4_2560x1440_60_10  = 700, //    │     1.20GiB 13956k https │ av01.0.12M.10 13956k video only 1440p60 HDR, mp4_dash
     WEBM_2560x1440_60_10 = 336, //    │     1.37GiB 15988k https │ vp09.02.50.10 15988k video only 1440p60 HDR, webm_dash
     MP4_3840x2160_30     = 401, //    │     2.36GiB  4172k https │ av01.0.12M.08  4172k video only 2160p, mp4_dash
     WEBM_3840x2160_30    = 313, //    │     5.23GiB  9231k https │ vp09.00.50.08  9231k video only 2160p, webm_dash
     WEBM_3840x2160_60    = 315, //    │     2.20GiB 25726k https │ vp09.00.51.08 25726k video only 2160p60, webm_dash
     MP4_3840x2160_60_10  = 701, //    │     2.11GiB 24647k https │ av01.0.13M.10 24647k video only 2160p60 HDR, mp4_dash
     WEBM_3840x2160_60_10 = 337, //    │     2.44GiB 28451k https │ vp09.02.51.10 28451k video only 2160p60 HDR, webm_dash
     MP4_7680x4320_60_10  = 702, //    │     4.22GiB 49272k https │ av01.0.17M.10 49272k video only 4320p60 HDR, mp4_dash
     UNKNOWNV             = -1 };

enum FORMAT_AUDIO{
     MP4_233    = 233, // │                    m3u8  │ audio only unknown             Default
     MP4_234    = 234, // │                    m3u8  │ audio only unknown             Default
     M4A_2_599  = 599, // │     2.70MiB    31k https │ audio only mp4a.40.5   31k 22k ultralow, m4a_dash
     WEBM_2_600 = 600, // │     3.20MiB    36k https │ audio only opus        36k 48k ultralow, webm_dash
     M4A_2_139  = 139, // │     4.28MiB    49k https │ audio only mp4a.40.5   49k 22k low, m4a_dash
     WEBM_2_249 = 249, // │     4.65MiB    53k https │ audio only opus        53k 48k low, webm_dash
     WEBM_2_250 = 250, // │     6.20MiB    71k https │ audio only opus        71k 48k low, webm_dash
     M4A_2_140  = 140, // │    11.36MiB   129k https │ audio only mp4a.40.2  129k 44k medium, m4a_dash
     WEBM_2_251 = 251, // │    11.94MiB   136k https │ audio only opus       136k 48k medium, webm_dash
     UNKNOWNA   = -1};

const EXTENSION extension(const std::string& ext){
    std::map<std::string, EXTENSION> exts{
        {".mp3", EXTENSION::MP3},
        {".mp4", EXTENSION::MP4},
        {".mkv", EXTENSION::MKV},
        {".webm", EXTENSION::WEBM},
        {".json", EXTENSION::JSON},
        {".m4a", EXTENSION::M4A}
    };

    if (exts.contains(ext))
        return exts.at(ext);
    else
        return EXTENSION::UNKNOWN;

}

const FORMAT_VIDEO format_video(const std::string& form){
    std::map<std::string  , FORMAT_VIDEO> exts{
        {"mp4_4320_60_10" , FORMAT_VIDEO::MP4_7680x4320_60_10},
        {"mp4_2160_60_10" , FORMAT_VIDEO::MP4_3840x2160_60_10},
        {"mp4_2160_30"    , FORMAT_VIDEO::MP4_3840x2160_30},
        {"mp4_1440_60_10" , FORMAT_VIDEO::MP4_2560x1440_60_10},
        {"mp4_1440_30"    , FORMAT_VIDEO::MP4_2560x1440_30},
        {"mp4_1080_60_10" , FORMAT_VIDEO::MP4_1920x1080_60_10},
        {"mp4_1080_60"    , FORMAT_VIDEO::MP4_1920x1080_60},
        {"mp4_1080_30"    , FORMAT_VIDEO::MP4_1920x1080_30},
        {"mp4_720_60_10"  , FORMAT_VIDEO::MP4_1280x720_60_10},
        {"mp4_720_60"     , FORMAT_VIDEO::MP4_1280x720_60},
        {"mp4_720_30"     , FORMAT_VIDEO::MP4_1280x720_30},
        {"mp4_480_60_10"  , FORMAT_VIDEO::MP4_854x480_60_10},
        {"mp4_480_30"     , FORMAT_VIDEO::MP4_854x480_30},
        {"mp4_360_60_10"  , FORMAT_VIDEO::MP4_640x360_60_10},
        {"mp4_360_30"     , FORMAT_VIDEO::MP4_640x360_30},
        {"webm_2160_60_10", FORMAT_VIDEO::WEBM_3840x2160_60_10},
        {"webm_2160_60"   , FORMAT_VIDEO::WEBM_3840x2160_60},
        {"webm_2160_30"   , FORMAT_VIDEO::WEBM_3840x2160_30},
        {"webm_1440_60_10", FORMAT_VIDEO::WEBM_2560x1440_60_10},
        {"webm_1440_60"   , FORMAT_VIDEO::WEBM_2560x1440_60},
        {"webm_1440_30"   , FORMAT_VIDEO::WEBM_2560x1440_30},
        {"webm_1080_60_10", FORMAT_VIDEO::WEBM_1920x1080_60_10},
        {"webm_1080_60"   , FORMAT_VIDEO::WEBM_1920x1080_60},
        {"webm_1080_30"   , FORMAT_VIDEO::WEBM_1920x1080_30},
        {"webm_720_60_10" , FORMAT_VIDEO::WEBM_1280x720_60_10},
        {"webm_720_60"    , FORMAT_VIDEO::WEBM_1280x720_60},
        {"webm_720_30"    , FORMAT_VIDEO::WEBM_1280x720_30},
        {"webm_480_60_10" , FORMAT_VIDEO::WEBM_854x480_60_10},
        {"webm_480_30"    , FORMAT_VIDEO::WEBM_854x480_30},
        {"webm_360_60_10" , FORMAT_VIDEO::WEBM_640x360_60_10},
        {"webm_360_30"    , FORMAT_VIDEO::WEBM_640x360_30}
    };

    if (exts.contains(form))
        return exts.at(form);
    else
        return FORMAT_VIDEO::UNKNOWNV;

}

std::string combinate_format(const FORMAT_VIDEO& format){

    std::string format_to_string;
    bool is_mp4 = false;

    switch (format) {
    case FORMAT_VIDEO::MP4_7680x4320_60_10:
        format_to_string.append(std::to_string(FORMAT_VIDEO::MP4_7680x4320_60_10).append("/"));
    case FORMAT_VIDEO::MP4_3840x2160_60_10:
        format_to_string.append(std::to_string(FORMAT_VIDEO::MP4_3840x2160_60_10).append("/"));
    case FORMAT_VIDEO::MP4_3840x2160_30:
        format_to_string.append(std::to_string(FORMAT_VIDEO::MP4_3840x2160_30).append("/"));
    case FORMAT_VIDEO::MP4_2560x1440_60_10:
        format_to_string.append(std::to_string(FORMAT_VIDEO::MP4_2560x1440_60_10).append("/"));
    case FORMAT_VIDEO::MP4_2560x1440_30:
        format_to_string.append(std::to_string(FORMAT_VIDEO::MP4_2560x1440_30).append("/"));
    case FORMAT_VIDEO::MP4_1920x1080_60_10:
        format_to_string.append(std::to_string(FORMAT_VIDEO::MP4_1920x1080_60_10).append("/"));
    case FORMAT_VIDEO::MP4_1920x1080_60:
        format_to_string.append(std::to_string(FORMAT_VIDEO::MP4_1920x1080_60).append("/"));
    case FORMAT_VIDEO::MP4_1920x1080_30:
        format_to_string.append(std::to_string(FORMAT_VIDEO::MP4_1920x1080_30).append("/"));
    case FORMAT_VIDEO::MP4_1280x720_30:
        format_to_string.append(std::to_string(FORMAT_VIDEO::MP4_1280x720_30).append("/"));
    case FORMAT_VIDEO::MP4_854x480_30:
        format_to_string.append(std::to_string(FORMAT_VIDEO::MP4_854x480_30).append("/bestvideo,"));
        is_mp4 = true;
        break;

    case FORMAT_VIDEO::WEBM_3840x2160_60_10:
        format_to_string.append(std::to_string(FORMAT_VIDEO::WEBM_3840x2160_60_10).append("/"));
    case FORMAT_VIDEO::WEBM_3840x2160_60:
        format_to_string.append(std::to_string(FORMAT_VIDEO::WEBM_3840x2160_60).append("/"));
    case FORMAT_VIDEO::WEBM_3840x2160_30:
        format_to_string.append(std::to_string(FORMAT_VIDEO::WEBM_3840x2160_30).append("/"));
    case FORMAT_VIDEO::WEBM_2560x1440_60_10:
        format_to_string.append(std::to_string(FORMAT_VIDEO::WEBM_2560x1440_60_10).append("/"));
    case FORMAT_VIDEO::WEBM_2560x1440_60:
        format_to_string.append(std::to_string(FORMAT_VIDEO::WEBM_2560x1440_60).append("/"));
    case FORMAT_VIDEO::WEBM_2560x1440_30:
        format_to_string.append(std::to_string(FORMAT_VIDEO::WEBM_2560x1440_30).append("/"));
    case FORMAT_VIDEO::WEBM_1920x1080_60_10:
        format_to_string.append(std::to_string(FORMAT_VIDEO::WEBM_1920x1080_60_10).append("/"));
    case FORMAT_VIDEO::WEBM_1920x1080_60:
        format_to_string.append(std::to_string(FORMAT_VIDEO::WEBM_1920x1080_60).append("/"));
    case FORMAT_VIDEO::WEBM_1920x1080_30:
        format_to_string.append(std::to_string(FORMAT_VIDEO::WEBM_1920x1080_30).append("/"));
    case FORMAT_VIDEO::WEBM_1280x720_30:
        format_to_string.append(std::to_string(FORMAT_VIDEO::WEBM_1280x720_30).append("/"));
    case FORMAT_VIDEO::WEBM_854x480_30:
        format_to_string.append(std::to_string(FORMAT_VIDEO::WEBM_854x480_30).append("/bestvideo,"));
        break;

    default:
        throw std::runtime_error("wrong video format");
        break;
    }


    if(is_mp4)
        format_to_string.append("140/139/599/bestaudio");
    else
        format_to_string.append("251/250/249/600/bestaudio");

    return format_to_string;
}
