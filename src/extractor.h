#pragma once
#include "video.h"
#include "commandline.h"

namespace dtv {

class Extractor
{
public:
    Extractor();

    static std::optional<Video> JsonToVideo(const CommandLine& line);
};

} // namespace dtv
