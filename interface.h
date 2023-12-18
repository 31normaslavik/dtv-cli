#pragma once

#include <boost/json.hpp>
#include <memory>
#include <string>
#include <vector>
#include <filesystem>

class Video {
public:
    [[nodiscard]] virtual std::string get_id() const = 0;
    [[nodiscard]] virtual std::string get_title() const = 0;
    [[nodiscard]] virtual std::string get_webpage_url() const = 0;
    [[nodiscard]] virtual std::string get_extractor() const = 0;
    [[nodiscard]] virtual int64_t get_playlist_index() const = 0;
    [[nodiscard]] virtual int64_t get_playlist_count() const = 0;
    [[nodiscard]] virtual int64_t get_duration() const = 0;
    [[nodiscard]] virtual int64_t get_age_limit() const = 0;

    virtual ~Video() = default;
};


/**
 * \brief Video youtube
 */
class VideoYoutube final : public Video {
public:
    explicit VideoYoutube( std::string id,
                           std::string title,  std::string webpage_url,  std::string extractor,
                          int64_t playlist_index, int64_t playlist_count, int64_t duration, int64_t age_limit);

    [[nodiscard]] std::string get_id() const override;
    [[nodiscard]] std::string get_title() const override;
    [[nodiscard]] std::string get_webpage_url() const override;
    [[nodiscard]] std::string get_extractor() const override;
    [[nodiscard]] int64_t get_playlist_index() const override;
    [[nodiscard]] int64_t get_playlist_count() const override;
    [[nodiscard]] int64_t get_duration() const override;
    [[nodiscard]] int64_t get_age_limit() const override;
    ~VideoYoutube() override = default;

private:
    std::string id;
    std::string title;
    std::string webpage_url;
    std::string extractor;
    int64_t playlist_index;
    int64_t playlist_count;
    int64_t duration;
    int64_t age_limit;
};


/**
 * \brief Vector videos
 */
class VideoData final {
public:
    void add(std::shared_ptr<Video> video);

    [[nodiscard]] std::vector<std::shared_ptr<Video>> getAllData() const;

private:
    std::vector<std::shared_ptr<Video>> videos;
};


class JsonData {
public:
    explicit JsonData(const boost::json::value& value);

    explicit JsonData(const std::filesystem::directory_entry& entry);

    [[nodiscard]] std::string get_id() const;
    [[nodiscard]] std::string get_title() const;
    [[nodiscard]] std::string webpage_url() const;
    [[nodiscard]] std::string get_extractor() const;
    [[nodiscard]] int64_t get_playlist_index() const;
    [[nodiscard]] int64_t get_playlist_count() const;
    [[nodiscard]] int64_t get_duration() const;
    [[nodiscard]] int64_t get_age_limit() const;

private:
    boost::json::object obj;
};
