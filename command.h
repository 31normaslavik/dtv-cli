#pragma once

#include "presentation.h"
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <random>
#include <string>

std::string temp_dir_generate(const std::string& dir){
    std::random_device rd;

    std::string chars{"qwertyuiopasdfghjklzxcvbnm"};
    std::uniform_int_distribution<int> dist(0, chars.size() - 1);

    std::string temp{dir + "-"};
    for (int n = 0; n < 10; ++n)
        temp.push_back(chars[dist(rd)]);

    return temp;
}


int ffmpeg_command_run(const std::string& video,
                       const std::string& voice,
                       const std::string& audio,
                       const std::string& output){
    return std::system(std::string("ffmpeg -i \"" + video + "\" -i \"" + voice + "\" -i \""
                                   + audio + "\" -c:v copy "
                                   "-filter_complex "
                                   "amix=inputs=2:duration=longest:dropout_transition=0:weights="
                                   "\"1 0.20 2 1.0\":normalize=1 -y \"" + output + "\"").c_str());
}

int yt_dlp_command_run(const std::string& url, const FORMAT_VIDEO& format){
    return std::system(std::string("yt-dlp " + url + " -f " + combinate_format(format) +
                                   " -o \"%(title)s.f%(format_id)s.%(display_id)s.%(ext)s\"").c_str());
}

int vot_cli_command_run(const std::string& url){
    return std::system(std::string("vot-cli --output=\".\" \"" + url+ "\"").c_str());

}

void create_json(const std::vector<std::string>& urls){

    for(size_t i{}; i < urls.size(); ++i){
        std::system(std::string("yt-dlp \"" + urls[i] + "\" -J > " + std::to_string(i) + "_file.json").c_str());
    }
}

std::vector<std::filesystem::directory_entry> read_json(std::filesystem::path& path){
    std::vector<std::filesystem::directory_entry> v;

    for(const auto& entry: std::filesystem::directory_iterator(path)){
        std::cout<<entry.path().filename()<< " "
                  << std::filesystem::file_size(entry.path().filename()) / 1024 << " KiB" <<std::endl;
        if(entry.path().filename().string().find(".json") != std::string::npos){
            v.emplace_back(entry);
        }
    }

    std::sort(v.begin(),v.end());

    std::cout<<"Find json files in temp directory: ";
    for(const auto& i : v)
        std::cout<<i<< " ";
    std::cout<<std::endl;

    return v;
}
