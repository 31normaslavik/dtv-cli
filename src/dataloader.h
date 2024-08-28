#pragma once
#include <boost/url.hpp>

namespace dtv {

class DataLoader {
public:
    explicit DataLoader(boost::urls::url_view const& url);
    void DownloadJsonsToDisk();
private:
    boost::urls::url_view const& _url;
};


} // namespace dtv
