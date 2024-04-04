#include "video.h"
#include <utility>

void dtv::VideoData::PushBack(std::shared_ptr<Video> video) {
	videos_.emplace_back(std::move(video));
}

std::vector<std::shared_ptr<dtv::Video>> dtv::VideoData::GetAllData() const {
	return videos_;
}

