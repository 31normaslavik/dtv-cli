#pragma once

#include "commandline.h"

namespace dtv {

/**
* @brief The Downloader class
*/
class Downloader {
public:
    explicit Downloader(const CommandLine &line);
    void Start();
private:
    CommandLine const& _line;
};

} // namespace dtv

