#pragma once
#include "commandline.h"
#include "video.h"
#include <map>
#include <string>
#include <vector>

namespace dtv {

class Formater
{
public:
    explicit Formater(Video &video, const CommandLine &line);
    std::string GetFormat() const;
private:
    // std::vector<Format> _formats;

    int getClosest(int val1, int val2, int target) const;
    int findClosest(int target) const;

    Video& _video;
    const CommandLine& _line;
};

} // namespace dtv
