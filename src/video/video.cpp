#include "video.h"

namespace dtv {

void VectorPtrVideos::PushBack(std::shared_ptr<Video> video_ptr) {
    videos_ptr_.emplace_back(video_ptr);
}

std::vector<std::shared_ptr<Video>> VectorPtrVideos::GetAllData() const {
    return videos_ptr_;
}

} // namespace dtv
