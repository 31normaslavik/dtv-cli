#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace dtv {

// TODO Сделать главным классом хранения данных видео
// А в наследуемых классах перегружать только методы, которые дают сбой при выполнении
// TODO --parse-metadata \"video::(?P<automatic_captions>)\" Добавить методы для субтитров
class Video {
public:

    [[nodiscard]] std::string Id() const;
    void Id(const std::string &id);
    [[nodiscard]] std::string Title() const;
    void Title(const std::string &title);
    [[nodiscard]] std::string Fulltitle() const;
    void Fulltitle(const std::string &fulltitle);
    [[nodiscard]] std::string Description() const;
    void Description(const std::string &description);

    [[nodiscard]] std::map<std::string, std::string> WebpageUrlFormat() const;
    void WebpageUrlFormat(const std::string &webpage_url, const std::string &format);

    [[nodiscard]] std::string WebpageUrl() const;
    void WebpageUrl(const std::string &webpage_url);

    [[nodiscard]] std::string Extractor() const;
    void Extractor(const std::string &extractor);
    [[nodiscard]] std::string Channel() const;
    void Channel(const std::string &channel);
    [[nodiscard]] std::string Upload_date() const;
    void Upload_date(const std::string &upload_date);
    [[nodiscard]] std::string Availability() const;
    void Availability(const std::string &availability);
    [[nodiscard]] std::string Playlist_id() const;
    void Playlist_id(const std::string &playlist_id);
    [[nodiscard]] std::string Playlist_title() const;
    void Playlist_title(const std::string &playlist_title);
    [[nodiscard]] std::string Duration_string() const;
    void Duration_string(const std::string &duration_string);
    [[nodiscard]] std::string Format() const;
    void Format(const std::string &format);
    [[nodiscard]] std::string Format_id() const;
    void Format_id(const std::string &format_id);
    [[nodiscard]] std::string Ext() const;
    void Ext(const std::string &ext);
    [[nodiscard]] std::string Video_ext() const;
    void Video_ext(const std::string &video_ext);
    [[nodiscard]] std::string Audio_ext() const;
    void Audio_ext(const std::string &audio_ext);
    [[nodiscard]] std::string Language() const;
    void Language(const std::string &language);
    [[nodiscard]] std::string Format_note() const;
    void Format_note(const std::string &format_note);
    [[nodiscard]] std::string Resolution() const;
    void Resolution(const std::string &resolution);
    [[nodiscard]] std::string Dynamic_range() const;
    void Dynamic_range(const std::string &dynamic_range);
    [[nodiscard]] std::string Vcodec() const;
    void Vcodec(const std::string &vcodec);
    [[nodiscard]] std::string Acodec() const;
    void Acodec(const std::string &acodec);
    [[nodiscard]] std::string _type() const;
    void _type(const std::string &_type);
    [[nodiscard]] std::vector<std::string> Categories() const;
    void Categories(const std::vector<std::string> &categories);
    [[nodiscard]] int64_t Playlist_index() const;
    void Playlist_index(int64_t playlist_index);
    [[nodiscard]] int64_t Vbr() const;
    void Vbr(int64_t vbr);
    [[nodiscard]] int64_t Asr() const;
    void Asr(int64_t asr);
    [[nodiscard]] int64_t Audio_channels() const;
    void Audio_channels(int64_t audio_channels);
    [[nodiscard]] int64_t Width() const;
    void Width(int64_t width);
    [[nodiscard]] int64_t Height() const;
    void Height(int64_t height);
    [[nodiscard]] int64_t Fps() const;
    void Fps(int64_t fps);
    [[nodiscard]] int64_t Playlist_count() const;
    void Playlist_count(int64_t playlist_count);
    [[nodiscard]] int64_t N_entries() const;
    void N_entries(int64_t n_entries);
    [[nodiscard]] int64_t Duration() const;
    void Duration(int64_t duration);
    [[nodiscard]] int64_t Age_limit() const;
    void Age_limit(int64_t age_limit);
    [[nodiscard]] std::string Playlist() const;
    void Playlist(const std::string &playlist);

protected:
    std::string id_;
    std::string title_;
    std::string fulltitle_;
    std::string description_;
    std::map< std::string, std::string > webpage_url_format_;
    std::string webpage_url_;
    std::string extractor_;
    std::string channel_;
    std::string upload_date_;
    std::string availability_;
    std::string playlist_;
    std::string playlist_id_;
    std::string playlist_title_;
    std::string duration_string_;
    std::string format_;
    std::string format_id_;
    std::string ext_;
    std::string video_ext_;
    std::string audio_ext_;
    std::string language_;
    std::string format_note_;
    std::string resolution_;
    std::string dynamic_range_;
    std::string vcodec_;
    std::string acodec_;
    std::string _type_;
    std::vector<std::string> categories_;
    int64_t playlist_index_;
    int64_t vbr_;
    int64_t asr_;
    int64_t audio_channels_;
    int64_t width_;
    int64_t height_;
    int64_t fps_;
    int64_t playlist_count_;
    int64_t n_entries_;
    int64_t duration_;
    int64_t age_limit_;
};

/**
 * \brief Vector videos
 */
class VectorPtrVideos final {
public:
    void PushBack(std::shared_ptr<Video> video_ptr);

    [[nodiscard]] std::vector<std::shared_ptr<Video>> GetAllData() const;

private:
    std::vector<std::shared_ptr<Video>> videos_ptr_;
};


} // namespace dtv
