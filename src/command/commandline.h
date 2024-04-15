#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace dtv{

class CommandLine{
public:
    explicit CommandLine(const std::vector<std::string>& urls,
                         const std::filesystem::path& path_to_save, const std::string& format);

    std::filesystem::path Path() const;

    [[nodiscard]] std::string Format() const;

    [[nodiscard]] std::vector< std::string > Urls() const;

private:
    std::filesystem::path path_to_save_;
    std::vector< std::string > urls_;
    std::string format_;
};


const std::string resources[] {"youtube", "youtube-nocookie","youtu","rutube",
                              "vk","twitch","twitter","9gag","bilibili",
                              "mail","vimeo","pornhub","xvideos","tiktok",
                              "rumble","eporner","pabloferreiro","piped","vern"};

} // namespace dtv
