#pragma once
#include "../video/video.h"
#include "commandline.h"

namespace dtv {


class ReadJson
{
public:
    ReadJson();

    std::optional<Video> JsonToVideo(const CommandLine& line) const;
};

} // namespace dtv
