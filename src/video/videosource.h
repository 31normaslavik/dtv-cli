#pragma once
#include "video.h"

namespace dtv {

/**
 * \brief Video 9gag
 */
class VideoNineGag final : public Video {
public:
    explicit VideoNineGag();
};


/**
 * \brief Video vimeo
 */
class VideoVimeo final : public Video {
public:
    explicit VideoVimeo();
};


/**
 * \brief Video youtube
 */
class VideoYoutube final : public Video {
public:
    explicit VideoYoutube();
};


} // namespace dtv
