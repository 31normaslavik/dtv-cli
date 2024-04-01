#include "videoyoutube.h"

dtv::VideoYoutube::VideoYoutube(std::string id, std::string title, std::string webpage_url, std::string extractor, int64_t playlist_index, int64_t playlist_count, int64_t duration, int64_t age_limit): id_{std::move(id)},
    title_{std::move(title)},
    webpage_url_{std::move(webpage_url)},
    extractor_{std::move(extractor)},
    playlist_index_{playlist_index},
    playlist_count_{playlist_count},
    duration_{duration},
    age_limit_{age_limit} {
}

std::string dtv::VideoYoutube::Id() const {
    return id_;
}

std::string dtv::VideoYoutube::Title() const {
    return title_;
}

std::string dtv::VideoYoutube::WebpageUrl() const {
    return webpage_url_;
}

std::string dtv::VideoYoutube::Extractor() const {
    return extractor_;
}

int64_t dtv::VideoYoutube::PlaylistIndex() const {
    return playlist_index_;
}

int64_t dtv::VideoYoutube::PlaylistCount() const {
    return playlist_count_;
}

int64_t dtv::VideoYoutube::Duration() const {
    return duration_;
}

int64_t dtv::VideoYoutube::AgeLimit() const {
    return age_limit_;
}



