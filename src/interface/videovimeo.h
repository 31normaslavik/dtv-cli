#pragma once
#include "interface.h"

namespace dtv {


/**
 * \brief Video youtube
 */
class VideoVimeo final : public dtv::Video {
public:
    explicit VideoVimeo( std::string id,
                          std::string title,  std::string webpage_url,  std::string extractor,
                          int64_t playlist_index, int64_t playlist_count, int64_t duration, int64_t age_limit);

    [[nodiscard]] std::string Id() const override;
    [[nodiscard]] std::string Title() const override;
    [[nodiscard]] std::string WebpageUrl() const override;
    [[nodiscard]] std::string Extractor() const override;
    [[nodiscard]] int64_t PlaylistIndex() const override;
    [[nodiscard]] int64_t PlaylistCount() const override;
    [[nodiscard]] int64_t Duration() const override;
    [[nodiscard]] int64_t AgeLimit() const override;

private:
    std::string id_;
    std::string title_;
    std::string webpage_url_;
    std::string extractor_;
    int64_t playlist_index_;
    int64_t playlist_count_;
    int64_t duration_;
    int64_t age_limit_;
};

} // namespace dtv
