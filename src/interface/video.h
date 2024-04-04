#pragma once

#include <memory>
#include <string>
#include <vector>

namespace dtv {


class Video {
public:
    [[nodiscard]] virtual std::string Id()              const = 0;
    [[nodiscard]] virtual std::string Title()           const = 0;
    [[nodiscard]] virtual std::string WebpageUrl()     const = 0;
    [[nodiscard]] virtual std::string Extractor()       const = 0;
    [[nodiscard]] virtual int64_t     PlaylistIndex()  const = 0;
    [[nodiscard]] virtual int64_t     PlaylistCount()  const = 0;
    [[nodiscard]] virtual int64_t     Duration()        const = 0;
    [[nodiscard]] virtual int64_t     AgeLimit()       const = 0;
    //[[nodiscard]] virtual std::string i_am()                const = 0;
    virtual ~Video() = default;
};

/**
 * \brief Vector videos
 */
class VideoData final {
public:
    void PushBack(std::shared_ptr<Video> video);

    [[nodiscard]] std::vector<std::shared_ptr<Video>> GetAllData() const;

private:
    std::vector<std::shared_ptr<Video>> videos_;
};


} // namespace dtv
