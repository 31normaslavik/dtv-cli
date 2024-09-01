#include "extractor.h"
#include <fstream>
#include <iostream>

namespace dtv {

Extractor::Extractor() {}

std::optional<Video> Extractor::JsonToVideo(const CommandLine &line)
{
    std::ifstream ifs;
    for(auto const& de: fs::directory_iterator(line.Output()->GetPathToTemp())){
        if(de.is_regular_file() && de.path().filename().has_extension()
            && de.path().filename().extension().string() == ".json"){

            fs::path json{de.path()};
            if(!json.empty()){
                ifs.open(json);
                if(!ifs){
                    std::cerr << "Can't open file: " << json.filename().string() << "\n";
                    continue;
                }
                bj::value const v = bj::parse(ifs);
                ifs.close();
                std::error_code ec;
                std::filesystem::remove(json, ec);
                if(ec.value())
                    std::cerr << ec.message() << " : " << ec.value();

                Video video = bj::value_to<Video>(std::move(v));

                for(auto& format: video.formats){
                    if(format.tbr > 0)
                        format.size = format.tbr * 1000 * video.duration / 8;
                    else if(format.vbr > 0)
                        format.size = format.vbr * 1000 * video.duration / 8;
                    else if(format.abr > 0)
                        format.size = format.abr * 1000 * video.duration / 8;

                    if(format.size <= 0){
                        if(format.height >= 240)
                            format.tbr = 300000 / 8;
                        if(format.height >= 360)
                            format.tbr = 400000 / 8;
                        if(format.height >= 480)
                            format.tbr = 500000 / 8;
                        if(format.height >= 720)
                            format.tbr = 1500000 / 8;
                        if(format.height >= 720 && format.fps > 30)
                            format.tbr = 2250000 / 8;
                        if(format.height >= 1080)
                            format.tbr = 3000000 / 8;
                        if(format.height >= 1080 && format.fps > 30)
                            format.tbr = 4500000 / 8;
                        if(format.height >= 1440)
                            format.tbr = 6000000 / 8;
                        if(format.height >= 1440 && format.fps > 30)
                            format.tbr = 9000000 / 8;
                        if(format.height >= 2160)
                            format.tbr = 13000000 / 8;
                        if(format.height >= 2160 && format.fps > 30)
                            format.tbr = 20000000 / 8;
                        if(format.height >= 4320)
                            format.tbr = 80000000 / 8;
                        if(format.height >= 4320 && format.fps > 30)
                            format.tbr = 120000000 / 8;
                    }
                }
                return video;
            }
        }
    }

    return std::nullopt;
}

} // namespace dtv
