#pragma once

#include <filesystem>
#include <set>
#include <string>
#include <vector>

namespace dtv{

struct Source{
    explicit Source(const std::string& resource, const std::string& url, const std::string& format);
    std::string resource_;
    std::string url_;
    std::string format_;
    bool unavailable_ = false;

};

struct cmpSource{
    bool operator()(const Source& ls, const Source& rs) const{
        return (ls.resource_ != rs.resource_ || ls.url_ != rs.url_ || ls.format_ != rs.format_);
    }
};

class CommandLine{
public:
    explicit CommandLine(const std::vector<std::string>& urls,
                         const std::filesystem::path& pathToSave, const std::string& format);

    std::filesystem::path Path() const;
    //std::string getFormat();
    std::set<Source,cmpSource> Resources() const;

private:
    std::filesystem::path path_to_save_;
    // url resource
    std::set<Source,cmpSource> resources_list_;
};


const std::string resources[] {"youtube", "youtube-nocookie","youtu","rutube",
                              "vk","twitch","twitter","9gag","bilibili",
                              "mail","vimeo","pornhub","xvideos","tiktok",
                              "rumble","eporner","pabloferreiro","piped","vern"};

} // namespace dtv
