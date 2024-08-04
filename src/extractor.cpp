#include "extractor.h"
#include <fstream>
#include <iostream>

namespace dtv {

Extractor::Extractor() {}

std::optional<Video> Extractor::JsonToVideo(const CommandLine &line)
{
    fs::path json;
    std::ifstream ifs;
    for(auto const& de: fs::directory_iterator(line.Temp_dir())){
        if(de.is_regular_file() && de.path().filename().has_extension()
            && de.path().filename().extension().string() == ".json"){
            json = de.path();
            if(!json.empty()){
                ifs.open(json);
                if(!ifs){
                    std::cerr << "Can't open file: " << json.filename().string() << "\n";
                    continue;
                }

                bj::value const v = bj::parse(ifs);
                Video video = bj::value_to<Video>(std::move(v));
                return video;
            }
        }
    }

    return std::nullopt;
}

} // namespace dtv
