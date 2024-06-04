#pragma once
#include <boost/url.hpp>

namespace dtv {

class DataLoader {
public:
    explicit DataLoader(boost::urls::url_view const& url);

    // [[nodiscard]] std::shared_ptr<dtv::VectorPtrVideos> VideoData();

    void DownloadJsonsToDisk();
private:
    // [[nodiscard]] std::vector<std::filesystem::directory_entry> CreateListJsonFromDisk() const;

    // void FillingInVideoData();
    // std::string createFormatForUrl(const std::string & url);

    // std::shared_ptr<FsDirectories> path_ptr_;
    // std::shared_ptr<dtv::VectorPtrVideos> video_data_ptr_;
    // std::string format_;
    boost::urls::url_view const& _url;
};


} // namespace dtv
