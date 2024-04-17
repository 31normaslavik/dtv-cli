#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace dtv{

/**
 * @brief The CommandLine class
 */
class CommandLine{
public:
    explicit CommandLine(const std::vector<std::string>& urls,
                         const std::filesystem::path& path_to_save, const std::string& format);
    /**
     * @brief Path
     * @return
     */
    std::filesystem::path Path() const;

    /**
     * @brief Format
     * @return
     */
    [[nodiscard]] std::string Format() const;

    /**
     * @brief Urls
     * @return
     */
    [[nodiscard]] std::vector< std::string > Urls() const;

private:
    std::filesystem::path path_to_save_;
    std::vector< std::string > urls_;
    std::string format_;
};

/**
 * @brief resources
 */
const std::string resources[] {"youtube", "youtube-nocookie","youtu","rutube",
                              "vk","twitch","twitter","9gag","bilibili",
                              "mail","vimeo","pornhub","xvideos","tiktok",
                              "rumble","eporner","pabloferreiro","piped","vern"};

} // namespace dtv
