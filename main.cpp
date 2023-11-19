#include <filesystem>
#include <iostream>
#include <fstream>
#include <boost/json.hpp>
#include <map>
#include <random>

using namespace boost::json;
using namespace std::literals;

struct video_info {
    std::string original_url, display_id, title, playlist_title;
    std::int64_t playlist_index;
};

struct Info{
    virtual ~Info() = 0;
};

struct Video_info: Info{
    std::string* original_url, display_id, title;
};

struct Playlist_info: Video_info {
    std::string* playlist_title;
};

std::ostream& operator<<(std::ostream& os, video_info const& v){
    return os << "Title: " << v.title << "\n"
              << "Display_id: " << v.display_id << " "
              << "Original_url: " << v.original_url<< " "
              << "Playlist_index: " << v.playlist_index;
}

std::string temp_dir_generate(const std::string& dir){
    std::random_device rd;

    std::string chars{"qwertyuiopasdfghjklzxcvbnm"};
    std::uniform_int_distribution<int> dist(0, chars.size() - 1);

    std::string temp{dir + "-"};
    for (int n = 0; n < 10; ++n)
        temp.push_back(chars[dist(rd)]);

    return temp;
}

/*

135 mp4   854x480     30    │   47.45MiB 1053k https │ avc1.4D401F   1053k video only          480p, mp4_dash
606 mp4   854x480     30    │ ~ 44.48MiB  964k m3u8  │ vp09.00.30.08  964k video only
244 webm  854x480     30    │   31.03MiB  688k https │ vp09.00.30.08  688k video only          480p, webm_dash
22  mp4   1280x720    30  2 │ ≈101.66MiB 2203k https │ avc1.64001F         mp4a.40.2       44k [ru] 720p
232 mp4   1280x720    30    │ ~118.88MiB 2576k m3u8  │ avc1.4D401F   2576k video only
136 mp4   1280x720    30    │   93.51MiB 2074k https │ avc1.4D401F   2074k video only          720p, mp4_dash
609 mp4   1280x720    30    │ ~ 85.02MiB 1843k m3u8  │ vp09.00.31.08 1843k video only
247 webm  1280x720    30    │   63.24MiB 1403k https │ vp09.00.31.08 1403k video only          720p, webm_dash
270 mp4   1920x1080   30    │ ~217.68MiB 4718k m3u8  │ avc1.640028   4718k video only
137 mp4   1920x1080   30    │  174.62MiB 3873k https │ avc1.640028   3873k video only          1080p, mp4_dash
614 mp4   1920x1080   30    │ ~155.56MiB 3371k m3u8  │ vp09.00.40.08 3371k video only
248 webm  1920x1080   30    │  111.74MiB 2479k https │ vp09.00.40.08 2479k video only          1080p, webm_dash

*/

enum FORMAT_VIDEO{WEBM_1920x1080 = 248, MP4_1920x1080 = 137,
                    WEBM_1280x720 = 247, MP4_1280x720 = 136,
                    WEBM_854x480 = 244, MP4_854x480 = 135 , UNKNOWN = -1};


enum class EXTENSION{MP4, MKV, WEBM, MP3, UNKNOWN};

const EXTENSION extension(const std::string& ext){
    std::map<std::string, EXTENSION> exts{
        {".mp3", EXTENSION::MP3},
        {".mp4", EXTENSION::MP4},
        {".mkv", EXTENSION::MKV},
        {".webm", EXTENSION::WEBM}
    };

    if (exts.contains(ext))
        return exts.at(ext);
    else
        return EXTENSION::UNKNOWN;

}

const FORMAT_VIDEO format(const std::string& form){
    std::map<std::string, FORMAT_VIDEO> exts{
        {"mp41080", FORMAT_VIDEO::MP4_1920x1080},
        {"mp4720", FORMAT_VIDEO::MP4_1280x720},
        {"mp4480", FORMAT_VIDEO::MP4_854x480},
        {"webm1080", FORMAT_VIDEO::WEBM_1920x1080},
        {"webm720", FORMAT_VIDEO::WEBM_1280x720},
        {"webm480", FORMAT_VIDEO::WEBM_854x480},
    };

    if (exts.contains(form))
        return exts.at(form);
    else
        return FORMAT_VIDEO::UNKNOWN;

}

// dtv-cli --output ./ --format [ mp4[1080,720,480], webm[1080,720,480] ]  urls
int main(int argc, char** argv) try {
    using std::cout;
    using std::endl;
    namespace fs = std::filesystem;

    if(argc < 5){
        std::cerr<<"dtv-cli --output ./ "
                     "--format [ mp4[1080,720,480], "
                     "webm[1080,720,480] ]  urls"<<endl;
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

    if(format(std::string(argv[4])) == FORMAT_VIDEO::UNKNOWN){
        std::cerr<<"arg4 format incorrect"<<endl;
        return 0;
    }

    std::string urls;

    for(size_t i{5}; i < argc; ++i)
        urls.append(argv[i]).append(" ");

    urls.erase(urls.size() -1);

    std::string file_json{"info.json"};
    //std::string temp_dir{temp_dir_generate("dtv-cli")};
    std::string temp_dir{"dtv-cli"};

    std::string vot_cli_command{"vot-cli --output=\".\" "};
    std::string yt_dlp_info{"yt-dlp " + urls + " -J > " + file_json};
    std::string yt_dlp{"yt-dlp " + urls + " -f " + std::to_string(format(argv[4]))};
    std::string ffmpeg_command{"ffmpeg -i input.mp4 -itsoffset 00:00:03.0 -i input.mp4 "
                               "-vcodec copy -acodec copy -map 0:1 -map 1:0 output_shift3s.mp4"};

    cout <<urls<<endl;

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

    if(std::system(yt_dlp_info.c_str()) != 0){
        throw std::runtime_error("yt-dlp launched incorrectly");
    }

    fs::directory_entry json;
    for (const auto &entry : fs::directory_iterator(tmp)) {
        if (entry.is_regular_file() &&
            entry.path().string().find(file_json) != std::string::npos) {
            cout<<entry.path().filename() << " " << entry.file_size() / 1024 << " KiB"<<endl;
            cout<<entry.path() <<endl;
            json = entry;
        }
    }


    std::ifstream file(json.path().filename());
    if(!file) throw std::runtime_error("File: " + json.path().filename().string() + " can't be open");

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

    for(const auto& i: playlist)
        vot_cli_command.append(i.original_url).append(" ");

    cout<<vot_cli_command<<endl;
    if(std::system(std::string(vot_cli_command).c_str()) != 0){ // скачивание аудио
        throw std::runtime_error("vot-cli launched incorrectly");
    }

    cout<<yt_dlp + urls<<endl;
    if(std::system(yt_dlp.c_str()) != 0){ // скачивание видео
        throw std::runtime_error("yt-dlp launched incorrectly");
    }

    cout<<endl;
    cout<<endl;

    for(auto&i : playlist){
        std::string audio, video;

        for (const auto &entry : fs::directory_iterator(tmp)) {
            if (entry.is_regular_file() && entry.path().string().find(i.display_id) != std::string::npos) {

                switch (extension(entry.path().extension())) {
                case EXTENSION::MP4:
                case EXTENSION::WEBM:
                    video = entry.path().filename();
                    break;
                case EXTENSION::MP3:
                    audio = entry.path().filename();
                    break;
                default:
                    break;
                }
            }
        }

        if(std::system(std::string("ffmpeg -i \"" + video + "\" -i " + audio +
                                    " -vcodec copy -acodec copy \"" + i.display_id + ".mkv\"").c_str()) != 0)
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

        if(fs::exists(i.display_id + ".mkv")) {

            cout<< tmp.string() << " " << path_to_save.string() << endl;

            if(fs::copy_file(tmp / std::string(i.display_id + ".mkv"), path_to_save / std::string(i.title + ".mkv"),
                              fs::copy_options::update_existing)){

                cout<< "file: " << i.display_id + ".mkv" << " sussed copy to: " << path_to_save.relative_path() << endl;

                for (const auto &entry : fs::directory_iterator(tmp)) {
                    if (entry.is_regular_file() && entry.path().string().find(i.display_id) != std::string::npos) {

                        switch (extension(entry.path().extension())) {
                        case EXTENSION::MP4:
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

    cout<<fs::remove_all(tmp)<<": files is remove in "<< tmp <<endl;

    return ec.value();

} catch (const std::exception& e){
    std::cerr<<e.what()<<std::endl;
}

