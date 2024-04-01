#include "videovimeo.h"

dtv::VideoVimeo::VideoVimeo(std::string id, std::string title, std::string webpage_url, std::string extractor, int64_t playlist_index, int64_t playlist_count, int64_t duration, int64_t age_limit): id_{std::move(id)},
    title_{std::move(title)},
    webpage_url_{std::move(webpage_url)},
    extractor_{std::move(extractor)},
    playlist_index_{playlist_index},
    playlist_count_{playlist_count},
    duration_{duration},
    age_limit_{age_limit} {
}

std::string dtv::VideoVimeo::Id() const {
    return id_;
}

std::string dtv::VideoVimeo::Title() const {
    return title_;
}

std::string dtv::VideoVimeo::WebpageUrl() const {
    return webpage_url_;
}

std::string dtv::VideoVimeo::Extractor() const {
    return extractor_;
}

int64_t dtv::VideoVimeo::PlaylistIndex() const {
    return playlist_index_;
}

int64_t dtv::VideoVimeo::PlaylistCount() const {
    return playlist_count_;
}

int64_t dtv::VideoVimeo::Duration() const {
    return duration_;
}

int64_t dtv::VideoVimeo::AgeLimit() const {
    return age_limit_;
}


