#pragma once
#include <string>

struct Helper{
    const static std::string exampes;
    const static std::string codes_country;
    const static std::string subtitles_langs;

};

const std::string Helper::exampes = "If the specified path does not exist, the program will try to create "
    "the missing directories\n"
    "For 4320p video resolution, only mp4 format is supported\n\n"
    "#Format mp4, 1080p, path current\n"
    "dtv-cli -u \"url1\"\n\n"
    "#Format mp4, 480p, fps 30, path ./playlist4\n"
    "dtv-cli --output ./playlist4 --format mp4 --resolution 480 --urls "
    "\"url1\" \"url2\"\n\n"
    "#Format mp4, 1080p, fps 60, path ./playlist1\n"
    "dtv-cli --output ./playlist1 --format mp4 --resolution 1080 --fps "
    "--urls \"url\"\n\n"
    "#Format mp4, 2160p, fps 60, HDR, path ./playlist4\n"
    "dtv-cli --output ./playlist4 --format mp4 --resolution 2160 --fps --hdr "
    "--urls \"url1\" \"url2\"\n\n"
    "#Format webm, 2160p, fps 60, HDR, path /home/user/Videos\n"
    "dtv-cli -o /home/user/Videos -f webm -r 2160 --fps --hdr -u \"url1\" "
    "\"url2\" \"url3\"\n\n"
    "#Format mp4, 4320p, fps 60, HDR, path ./myvideos\n"
    "dtv-cli -o ./myvideos -f mp4 -r 7680x4320 --fps --hdr -u \"url1\" "
    "\"url2\" \"url3\"\n\n"
    "#Format webm, 1080p, fps 30, path current\n"
    "dtv-cli -f webm -u \"url1\"\n";

const std::string Helper::codes_country =
    "Video language\n"
    "These languages are used as languages that are installed as the language of the video (video translation will be performed from this language):\n"
    "By default: en\n"
        "ru - Russian\n"
        "en - English\n"
        "zh - Chinese\n"
        "ko - Korean\n"
        "ar - Arabic\n"
        "fr - French\n"
        "it - Italian\n"
        "es - Spanish\n"
        "de - German\n"
        "ja - Japanese\n"
        "Translation Language (TTS)\n"
    "These languages are used to generate an audio translation file (the translation will be performed in one of these languages):\n"
    "By default: ru\n"
        "ru - Russian\n"
        "en - English\n"
        "kk - Kazakh\n"
    ;

const std::string Helper::subtitles_langs = "Subtitles langs [ru en kk]";
