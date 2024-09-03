#pragma once
#include <string>

struct Helper{
    const static std::string exampes;
    const static std::string codes_country;
    const static std::string subtitles_langs;

};

const std::string Helper::exampes = "If the specified path does not exist, the program will try to create "
    "the missing directories\n\n"
    "Usage: dtv-cli [Options] urls\n"
    "#Format mp4, 1080p, path current\n"
    "dtv-cli -u \"url1\"\n\n"
    "#Format mp4, 480p, fps 30, path ./playlist4\n"
    "dtv-cli --output ./playlist4 --extension mp4 --height 480 --urls "
    "\"url1\" \"url2\"\n\n"
    "#Format mp4, 1080p, fps 60, path ./playlist1\n"
    "dtv-cli --output ./playlist1 --extension mp4 --height 1080 --fps 60 "
    "--urls \"url\"\n\n"
    "#Format mp4, 2160p, fps 60, path ./playlist4\n"
    "dtv-cli --output ./playlist4 --extension mp4 --height 2160 --fps 60 "
    "--urls \"url1\" \"url2\"\n\n"
    "#Format webm, 2160p, fps 60, path /home/user/Videos\n"
    "dtv-cli -o /home/user/Videos -e webm -H 2160 --fps 60 -u \"url1\" "
    "\"url2\" \"url3\"\n\n"
    "#Format mp4, 4320p, fps 60, path ./myvideos\n"
    "dtv-cli -o ./myvideos -e mp4 -H 4320 --fps 60 -u \"url1\" "
    "\"url2\" \"url3\"\n\n"
    "#Format webm, 1080p, fps 30, path current\n"
    "dtv-cli -f webm -u \"url1\"\n\n"
    "#Format mp4, 1080p, fps 30, ru subtitles, path current\n"
    "dtv-cli write-subs -u \"url1\"\n\n"
    "#Format mp4, 1080p, fps 30, en subtitles, path current\n"
    "dtv-cli --write-subs --sub-lang \"en\" -u \"url1\"\n\n"
    "#Format mp4, 1080p, fps 30, translate audio from ru to en, path current\n"
    "dtv-cli --translate-from-lang \"ru\" --translate-to-lang\"en\" -u \"url1\"\n\n"
    "#Format mp4, 1080p, fps 30, translate audio from ru to kk, ru subtitles, path current\n"
    "dtv-cli --translate-from-lang \"en\" --translate-to-lang\"kk\" --write-subs --sub-lang \"ru\" -u \"url1\"\n\n"
    ;

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
    "\nTranslation language (TTS)\n"
    "These languages are used to generate an audio translation file (the translation will be performed in one of these languages):\n"
    "By default: ru\n"
        "ru - Russian\n"
        "en - English\n"
        "kk - Kazakh\n"
    ;

const std::string Helper::subtitles_langs = "Subtitles langs [ru en kk]";
