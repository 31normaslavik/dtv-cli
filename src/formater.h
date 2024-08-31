#pragma once
#include "commandline.h"
#include "video.h"
#include <any>
#include <map>
#include <string>
#include <vector>

namespace dtv {

enum class FORMAT{Format, FirstClosestVideo, FirstClosestAudio};

class Formater
{
public:
    explicit Formater(Video const& video, CommandLine const& line);
    std::any GetFormat(const FORMAT eformat = FORMAT::Format) const;
private:
    // std::vector<Format> _formats;

    int getClosest(int val1, int val2, int target) const;
    int findClosest(int target) const;

    Video const& _video;
    CommandLine const& _line;
};

} // namespace dtv
