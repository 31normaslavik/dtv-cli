#pragma once

#include <string>

// TODO Добавить новые форматы youtube
/*

YOUTUBE

ID  EXT   RESOLUTION FPS HDR CH │    FILESIZE    TBR PROTO │ VCODEC           VBR ACODEC      ABR ASR MORE INFO
────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
599 m4a   audio only          2 │     2.70MiB    31k https │ audio only           mp4a.40.5   31k 22k ultralow, m4a_dash
600 webm  audio only          2 │     3.20MiB    36k https │ audio only           opus        36k 48k ultralow, webm_dash
599-drc m4a   audio only      2 │  593.58KiB   31k   https │ audio only          mp4a.40.5   31k 22k [ru] ultralow, DRC, m4a_dash
600-drc webm  audio only      2 │  648.85KiB   34k   https │ audio only          opus        34k 48k [ru] ultralow, DRC, webm_dash
139 m4a   audio only          2 │     4.28MiB    49k https │ audio only           mp4a.40.5   49k 22k low, m4a_dash
249 webm  audio only          2 │     4.65MiB    53k https │ audio only           opus        53k 48k low, webm_dash
250 webm  audio only          2 │     6.20MiB    71k https │ audio only           opus        71k 48k low, webm_dash
249-drc webm  audio only      2 │  955.45KiB   50k   https │ audio only          opus        50k 48k [ru] low, DRC, webm_dash
250-drc webm  audio only      2 │    1.10MiB   59k   https │ audio only          opus        59k 48k [ru] low, DRC, webm_dash
139     m4a   audio only      2 │  939.46KiB   49k   https │ audio only          mp4a.40.5   49k 22k [ru] low, m4a_dash
140 m4a   audio only          2 │    11.36MiB   129k https │ audio only           mp4a.40.2  129k 44k medium, m4a_dash
251 webm  audio only          2 │    11.94MiB   136k https │ audio only           opus       136k 48k medium, webm_dash
140-drc m4a   audio only      2 │    2.43MiB  130k https   │ audio only          mp4a.40.2  130k 44k [ru] medium, DRC, m4a_dash
251-drc webm  audio only      2 │    2.17MiB  116k https   │ audio only          opus       116k 48k [ru] medium, DRC, webm_dash
233 mp4   audio only            │                  m3u8    │ audio only          unknown             [ru] Default
234 mp4   audio only            │                  m3u8    │ audio only          unknown             [ru] Default
597 mp4   256x144     15        │  698.31KiB   36k https   │ avc1.4d400b      36k video only          144p, mp4_dash
602 mp4   256x144     15        │ ~  2.23MiB  118k m3u8    │ vp09.00.10.08   118k video only
598 webm  256x144     15        │  556.46KiB   29k https   │ vp9              29k video only          144p, webm_dash
269 mp4   256x144     30        │ ~  3.61MiB  192k m3u8    │ avc1.4D400C     192k video only
160 mp4   256x144     30        │    2.23MiB  119k https   │ avc1.4D400C     119k video only          144p, mp4_dash
603 mp4   256x144     30        │ ~  3.60MiB  191k m3u8    │ vp09.00.11.08   191k video only
278 webm  256x144     30        │    1.68MiB   89k https   │ vp09.00.11.08    89k video only          144p, webm_dash
229 mp4   426x240     30        │ ~  6.72MiB  357k m3u8    │ avc1.4D4015     357k video only
133 mp4   426x240     30        │    4.93MiB  262k https   │ avc1.4D4015     262k video only          240p, mp4_dash
604 mp4   426x240     30        │ ~  7.32MiB  389k m3u8    │ vp09.00.20.08   389k video only
242 webm  426x240     30        │    3.60MiB  192k https   │ vp09.00.20.08   192k video only          240p, webm_dash
230 mp4   640x360     30        │ ~ 15.34MiB  814k m3u8    │ avc1.4D401E     814k video only
18  mp4   640x360     30  2     │   12.60MiB  671k https   │ avc1.42001E          mp4a.40.2       44k [ru] 360p
605 mp4   640x360     30        │ ~ 12.55MiB  666k m3u8    │ vp09.00.21.08   666k video only
134 mp4   640x360     30        │   40.44MiB     70k https │ avc1.4D401E      70k video only          360p, mp4_dash
396 mp4   640x360     30        │   45.76MiB     79k https │ av01.0.01M.08    79k video only          360p, mp4_dash
243 webm  640x360     30        │   72.03MiB    124k https │ vp09.00.21.08   124k video only          360p, webm_dash
696 mp4   640x360     60 10     │    47.56MiB   542k https │ av01.0.04M.10   542k video only          360p60 HDR, mp4_dash
332 webm  640x360     60 10     │    84.98MiB   969k https │ vp09.02.30.10   969k video only          360p60 HDR, webm_dash
231     mp4   854x480     30    │ ~ 26.35MiB 1399k m3u8  │ avc1.4D401F   1399k video only
606     mp4   854x480     30    │ ~ 20.73MiB 1100k m3u8  │ vp09.00.30.08 1100k video only
397 mp4   854x480     30        │   78.83MiB    136k https │ av01.0.04M.08   136k video only          480p, mp4_dash
244 webm  854x480     30        │  119.23MiB    205k https │ vp09.00.30.08   205k video only          480p, webm_dash
135 mp4   854x480     30        │    52.05MiB   593k https │ avc1.4D401F     593k video only          480p, mp4_dash
697 mp4   854x480     60 10     │    91.93MiB  1048k https │ av01.0.05M.10  1048k video only          480p60 HDR, mp4_dash
333 webm  854x480     60 10     │   165.11MiB  1882k https │ vp09.02.31.10  1882k video only          480p60 HDR, webm_dash
232     mp4   1280x720    30    │ ~ 46.14MiB 2450k m3u8  │ avc1.64001F   2450k video only
609     mp4   1280x720    30    │ ~ 35.89MiB 1905k m3u8  │ vp09.00.31.08 1905k video only
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

/*
 *
 *
9gag.com

ID         EXT  RESOLUTION │ PROTO │ VCODEC  ACODEC
────────────────────────────────────────────────────
460sv      mp4  460x816    │ https │ unknown unknown
460sv-vp8  webm 460x816    │ https │ vp8     unknown
460sv-h265 mp4  460x816    │ https │ h265    unknown
460sv-vp9  webm 460x816    │ https │ vp9     unknown

*/

namespace dtv{


// const EXTENSION extension(const std::string& ext) {
//     if (const std::map<std::string, EXTENSION> exts{
//             {".mp3", EXTENSION::MP3},
//             {".mp4", EXTENSION::MP4},
//             {".mkv", EXTENSION::MKV},
//             {".webm", EXTENSION::WEBM},
//             {".json", EXTENSION::JSON},
//             {".m4a", EXTENSION::M4A}
//         };
//         exts.contains(ext))
//         return exts.at(ext);
//     return EXTENSION::UNKNOWN;
// }

// const std::string extension(const EXTENSION& ext) {
//     if (std::map<EXTENSION, std::string> exts{
//             {EXTENSION::MP3, ".mp3"},
//             {EXTENSION::MP4, ".mp4"},
//             {EXTENSION::MKV, ".mkv"},
//             {EXTENSION::WEBM, ".webm"},
//             {EXTENSION::JSON, ".json"},
//             {EXTENSION::M4A, ".m4a"}
//         };
//         exts.contains(ext))
//         return exts.at(ext);
//     return {};
// }

// const FORMAT_AUDIO format_audio_from_string(const std::string& format) {
//     std::map<std::string, FORMAT_AUDIO> exts{
//         {"format_233", FORMAT_AUDIO::MP4_233},
//         {"format_234", FORMAT_AUDIO::MP4_234},
//         {"format_599", FORMAT_AUDIO::M4A_2_599},
//         {"format_600", FORMAT_AUDIO::WEBM_2_600},
//         {"format_139", FORMAT_AUDIO::M4A_2_139},
//         {"format_249", FORMAT_AUDIO::WEBM_2_249},
//         {"format_250", FORMAT_AUDIO::WEBM_2_250},
//         {"format_140", FORMAT_AUDIO::M4A_2_140},
//         {"format_251", FORMAT_AUDIO::WEBM_2_251}
//     };
//
//     if (exts.contains(format))
//         return exts.at(format);
//     return FORMAT_AUDIO::UNKNOWNA;
// }

enum class Extension: int32_t { MP4, M4A, MKV, WEBM, MP3, JSON, UNKNOWN };

enum class FormatVideo: int32_t {
    /*9GAG*/
    MP4_460x816_460sv      = 1000,
    WEBM_460x816_460sv_vp8 = 1001,
    MP4_460x816_460sv_h265 = 1002,
    WEBM_460x816_460sv_vp9 = 1003,

    /*YOUTUBE*/
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
    UNKNOWNV             = -1
};

enum class FormatAudio: int32_t {
    MP4_233    = 233, // │                  m3u8   │ audio only unknown             Default
    MP4_234    = 234, // │                  m3u8   │ audio only unknown             Default
    M4A_2_599  = 599, // │  2.70MiB    31k  https  │ audio only mp4a.40.5   31k 22k ultralow, m4a_dash
    WEBM_2_600 = 600, // │  3.20MiB    36k  https  │ audio only opus        36k 48k ultralow, webm_dash
    M4A_2_139  = 139, // │  4.28MiB    49k  https  │ audio only mp4a.40.5   49k
    WEBM_2_249 = 249, // │  4.65MiB    53k  https  │ audio only opus        53k
    WEBM_2_250 = 250, // │  6.20MiB    71k  https  │ audio only opus        71k
    M4A_2_140  = 140, // │  11.36MiB   129k https  │ audio only mp4a.40.2  129k
    WEBM_2_251 = 251, // │  11.94MiB   136k https  │ audio only opus       136k
    UNKNOWNA   = -1
};

struct Format{

    static FormatVideo FormatVideoFromString(const std::string& format);

    static FormatVideo FormatVideoArgv(const std::string& format, const std::string& resource);

    static std::string CombinateFormat(FormatVideo format, const std::string &resource);

};

} // namespace dtv
