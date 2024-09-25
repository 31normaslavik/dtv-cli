#pragma once
#include "commandline.h"
#include "video.h"
#include <any>

namespace dtv {

enum class FORMAT: std::uint8_t {Format, FirstClosestVideo, FirstClosestAudio};

class Formater
{
public:
    explicit Formater(Video const& video, CommandLine const& line);
    [[nodiscard]] std::any GetFormat(const FORMAT eformat = FORMAT::Format) const;
private:
    [[nodiscard]] int64_t getClosest(int64_t val1, int64_t val2, int64_t target) const;
    [[nodiscard]] int64_t findClosest(int64_t target) const;

    Video const& _video;
    CommandLine const& _line;
};

} // namespace dtv
