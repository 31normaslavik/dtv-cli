#include <string>

#pragma once

struct video_info {
    std::string original_url, display_id, title, playlist_title;
    int64_t playlist_index;
};

struct Info{
    virtual ~Info() = 0;
};

struct Video_info: Info{
    std::string* original_url, display_id, title;
};

struct Playlist_info: Video_info {
    std::string* playlist_title;
};

// std::ostream& operator<<(std::ostream& os, video_info const& v){
//     return os << "Title: " << v.title << "\n"
//               << "Display_id: " << v.display_id << " "
//               << "Original_url: " << v.original_url<< " "
//               << "Playlist_index: " << v.playlist_index;
// }

