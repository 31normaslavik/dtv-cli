#include <filesystem>
#include <iostream>
#include <fstream>
#include <boost/json.hpp>
#include <random>
#include "presentation.h"
#include "command.h"
#include "interface.h"

using namespace boost::json;
using namespace std::literals;


// dtv-cli --output ./ --format [ mp4[1080,720,480], webm[1080,720,480] ]  urls
int main(int argc, char** argv) try {
    using std::cout;
    using std::endl;
    namespace fs = std::filesystem;


    if(argc < 5){
        std::cerr<<"dtv-cli --output ./ "
                     "--format [ mp4[1080,720,480,360], "
                     "webm[1080,720,480,360] ]  urls"<<endl;
        return 0;
    }

    if(std::string(argv[1]) != "--output"){
        std::cerr<<"arg1 --output"<<endl;
        return 0;
    }

    if(std::string(argv[2]).find("https://") != std::string::npos)
    {
        std::cerr<<"arg2 path incorrect"<<endl;
        return 0;
    }

    if(std::string(argv[3]) != "--format")
    {
        std::cerr<<"arg3 --format"<<endl;
        return 0;

    }

    if(format_video(argv[4]) == FORMAT_VIDEO::UNKNOWNV){
        std::cerr<<"arg4 format incorrect"<<endl;
        return 0;
    }

    std::vector<std::string> urls;

    for(size_t i{5}; i < argc; ++i)
        urls.emplace_back(argv[i]);

    std::string temp_dir{temp_dir_generate("dtv-cli")};
    //std::string temp_dir{"dtv-cli"};

    fs::path path_to_save{argv[2]};
    if(!fs::exists(path_to_save))
        fs::create_directories(path_to_save);

    fs::current_path(fs::temp_directory_path());

    if(!fs::exists(temp_dir)){
        fs::create_directories(temp_dir);
    }

    fs::path tmp {fs::temp_directory_path().append(temp_dir)};
    fs::current_path(tmp);
    cout<<fs::current_path()<<endl;

    create_json(urls);

    std::vector<fs::directory_entry> entrys_json{read_json(tmp)};

    if(entrys_json.empty()){
        throw std::runtime_error("json data not found");
    }

    for (const auto& entry_json : entrys_json) {


        std::ifstream file(entry_json.path().filename());
        if(!file) throw std::runtime_error("File: " + entry_json.path().filename().string() + " can't be open");

        error_code ec;
        value json_data = parse( file , ec);
        if(ec){
        throw std::runtime_error(std::to_string(ec.value()) + " " + ec.message());
    }

        std::vector<video_info> playlist;

        if(!json_data.is_object())
            throw std::runtime_error("incorrect file json");

        object p = json_data.as_object();

        if(p.at("_type").is_string() && p.at("_type").as_string() == "playlist"){

        std::int64_t playlist_count = json_data.if_object()->at("playlist_count").as_int64();

        cout<<"Videos in playlist: "<< playlist_count<<endl;

        for( std::int64_t i{} ; i < playlist_count ; ++i){
            video_info video {
                            p.at("entries").if_array()->at(i).at("original_url").as_string().c_str(),
                            p.at("entries").if_array()->at(i).at("display_id").as_string().c_str(),
                            p.at("entries").if_array()->at(i).at("title").as_string().c_str(),
                            p.at("title").as_string().c_str(),
                            p.at("entries").if_array()->at(i).at("playlist_index").as_int64()
            };

            playlist.emplace_back(std::move(video));
        }


        } else if(p.at("_type").is_string() && p.at("_type").as_string() == "video"){
        video_info video {
                        p.at("original_url").as_string().c_str(),
                        p.at("display_id").as_string().c_str(),
                        p.at("title").as_string().c_str(), "", 0
        };

        playlist.emplace_back(std::move(video));
    }
        else throw std::runtime_error("Non valide json file");

         for(auto&i : playlist){
             std::string audio, video, translated_audio;
           if(yt_dlp_command_run(i.original_url,format_video(argv[4])) != 0){ // скачивание видео
                 throw std::runtime_error("yt-dlp launched incorrectly");
             }
           if(vot_cli_command_run(i.original_url) != 0){ // скачивание аудио yandex api
                 throw std::runtime_error("vot-cli launched incorrectly");
             }
            for (const auto &entry : fs::directory_iterator(tmp)) {
                if (entry.is_regular_file() && entry.path().string().find(i.display_id) != std::string::npos) {

                    cout<<entry.path().filename() << " условие выполнено"<<endl;
                    switch (extension(entry.path().extension())) {
                      case EXTENSION::MP4:
                      case EXTENSION::WEBM:
                         video = entry.path().filename();
                         break;
                      case EXTENSION::MP3:
                         translated_audio = entry.path().filename();
                         break;
                      case EXTENSION::M4A:
                         audio = entry.path().filename();
                      default:
                         break;
                    }
                } else
                    cout<<entry.path().filename()<< " условие не выполнено"<<endl;

            }

           if(audio.empty() || video.empty() || translated_audio.empty())
                 throw std::runtime_error("one or more files needed for ffmpeg not found");

           if(ffmpeg_command_run(video, translated_audio, audio, i.display_id + ".mp4") != 0)
                 throw std::runtime_error("ffmpeg launched incorrectly");

           std::istringstream ss{i.title};
           for(std::string temp, newstring ; ss >> temp;){
               for(auto pos = temp.find_first_of("/.,\\"); pos != std::string::npos ; pos = temp.find_first_of("/.,\\") ){
                     temp.erase(pos,1);
                 }
               newstring += temp.append(" ");
                 i.title = newstring;
                 i.title.erase(i.title.size() - 1);
           }
           if(fs::exists(i.display_id + ".mp4")) {
               cout<< tmp.string() << " " << path_to_save.string() << endl;
               if(fs::copy_file(tmp / std::string(i.display_id + ".mp4"), path_to_save / std::string(i.title + ".mp4"),
                                   fs::copy_options::update_existing)){
                   cout<< "file: " << i.display_id + ".mp4" << " sussed copy to: " << path_to_save.relative_path() << endl;
                   for (const auto &entry : fs::directory_iterator(tmp)) {
                         if (entry.is_regular_file() && entry.path().string().find(i.display_id) != std::string::npos) {
                           switch (extension(entry.path().extension())) {
                             case EXTENSION::MP4:
                             case EXTENSION::M4A:
                             case EXTENSION::MKV:
                             case EXTENSION::WEBM:
                             case EXTENSION::MP3:
                                 fs::remove(entry.path().filename());
                                 cout<< entry.path().filename() << " was removed" << endl;
                                 break;
                             default:
                                 break;
                             }
                         }
                     }
                 }
             }
         }



    }

    cout<<fs::remove_all(tmp)<<": files is remove in "<< tmp <<endl;


} catch (const std::exception& e){
    std::cerr<<e.what()<<std::endl;
}

