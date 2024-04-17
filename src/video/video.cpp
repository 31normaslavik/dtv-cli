#include "video.h"

void dtv::VectorPtrVideos::PushBack(std::shared_ptr<Video> video_ptr) {
    videos_ptr_.emplace_back(video_ptr);
}

std::vector<std::shared_ptr<dtv::Video>> dtv::VectorPtrVideos::GetAllData() const {
    return videos_ptr_;
}

namespace dtv {

std::string Video::Id() const
{
    return id_;
}

void Video::Id(const std::string &id)
{
    id_ = id;
}

std::string Video::Title() const
{
    return title_;
}

void Video::Title(const std::string &title)
{
    title_ = title;
}

std::string Video::Fulltitle() const
{
    return fulltitle_;
}

void Video::Fulltitle(const std::string &fulltitle)
{
    fulltitle_ = fulltitle;
}

std::string Video::Description() const
{
    return description_;
}

void Video::Description(const std::string &description)
{
    description_ = description;
}

std::map< std::string, std::string> Video::WebpageUrlFormat() const
{
    return webpage_url_format_;
}

void Video::WebpageUrlFormat(const std::string &webpage_url, const std::string &format)
{
    webpage_url_format_[webpage_url] = format;
}

std::string Video::WebpageUrl() const
{
    return webpage_url_;
}

void Video::WebpageUrl(const std::string &webpage_url)
{
    webpage_url_ = webpage_url;
}

std::string Video::Extractor() const
{
    return extractor_;
}

void Video::Extractor(const std::string &extractor)
{
    extractor_ = extractor;
}

std::string Video::Channel() const
{
    return channel_;
}

void Video::Channel(const std::string &channel)
{
    channel_ = channel;
}

std::string Video::Upload_date() const
{
    return upload_date_;
}

void Video::Upload_date(const std::string &upload_date)
{
    upload_date_ = upload_date;
}

std::string Video::Availability() const
{
    return availability_;
}

void Video::Availability(const std::string &availability)
{
    availability_ = availability;
}

std::string Video::Playlist_id() const
{
    return playlist_id_;
}

void Video::Playlist_id(const std::string &playlist_id)
{
    playlist_id_ = playlist_id;
}

std::string Video::Playlist_title() const
{
    return playlist_title_;
}

void Video::Playlist_title(const std::string &playlist_title)
{
    playlist_title_ = playlist_title;
}

std::string Video::Duration_string() const
{
    return duration_string_;
}

void Video::Duration_string(const std::string &duration_string)
{
    duration_string_ = duration_string;
}

std::string Video::Format() const
{
    return format_;
}

void Video::Format(const std::string &format)
{
    format_ = format;
}

std::string Video::Format_id() const
{
    return format_id_;
}

void Video::Format_id(const std::string &format_id)
{
    format_id_ = format_id;
}

std::string Video::Ext() const
{
    return ext_;
}

void Video::Ext(const std::string &ext)
{
    ext_ = ext;
}

std::string Video::Video_ext() const
{
    return video_ext_;
}

void Video::Video_ext(const std::string &video_ext)
{
    video_ext_ = video_ext;
}

std::string Video::Audio_ext() const
{
    return audio_ext_;
}

void Video::Audio_ext(const std::string &audio_ext)
{
    audio_ext_ = audio_ext;
}

std::string Video::Language() const
{
    return language_;
}

void Video::Language(const std::string &language)
{
    language_ = language;
}

std::string Video::Format_note() const
{
    return format_note_;
}

void Video::Format_note(const std::string &format_note)
{
    format_note_ = format_note;
}

std::string Video::Resolution() const
{
    return resolution_;
}

void Video::Resolution(const std::string &resolution)
{
    resolution_ = resolution;
}

std::string Video::Dynamic_range() const
{
    return dynamic_range_;
}

void Video::Dynamic_range(const std::string &dynamic_range)
{
    dynamic_range_ = dynamic_range;
}

std::string Video::Vcodec() const
{
    return vcodec_;
}

void Video::Vcodec(const std::string &vcodec)
{
    vcodec_ = vcodec;
}

std::string Video::Acodec() const
{
    return acodec_;
}

void Video::Acodec(const std::string &acodec)
{
    acodec_ = acodec;
}

std::string Video::_type() const
{
    return _type_;
}

void Video::_type(const std::string &_type)
{
    _type_ = _type;
}

std::vector<std::string> Video::Categories() const
{
    return categories_;
}

void Video::Categories(const std::vector<std::string> &categories)
{
    categories_ = categories;
}

int64_t Video::Playlist_index() const
{
    return playlist_index_;
}

void Video::Playlist_index(int64_t playlist_index)
{
    playlist_index_ = playlist_index;
}

int64_t Video::Vbr() const
{
    return vbr_;
}

void Video::Vbr(int64_t vbr)
{
    vbr_ = vbr;
}

int64_t Video::Asr() const
{
    return asr_;
}

void Video::Asr(int64_t asr)
{
    asr_ = asr;
}

int64_t Video::Audio_channels() const
{
    return audio_channels_;
}

void Video::Audio_channels(int64_t audio_channels)
{
    audio_channels_ = audio_channels;
}

int64_t Video::Width() const
{
    return width_;
}

void Video::Width(int64_t width)
{
    width_ = width;
}

int64_t Video::Height() const
{
    return height_;
}

void Video::Height(int64_t height)
{
    height_ = height;
}

int64_t Video::Fps() const
{
    return fps_;
}

void Video::Fps(int64_t fps)
{
    fps_ = fps;
}

int64_t Video::Playlist_count() const
{
    return playlist_count_;
}

void Video::Playlist_count(int64_t playlist_count)
{
    playlist_count_ = playlist_count;
}

int64_t Video::N_entries() const
{
    return n_entries_;
}

void Video::N_entries(int64_t n_entries)
{
    n_entries_ = n_entries;
}

int64_t Video::Duration() const
{
    return duration_;
}

void Video::Duration(int64_t duration)
{
    duration_ = duration;
}

int64_t Video::Age_limit() const
{
    return age_limit_;
}

void Video::Age_limit(int64_t age_limit)
{
    age_limit_ = age_limit;
}

std::string Video::Playlist() const
{
    return playlist_;
}

void Video::Playlist(const std::string &playlist)
{
    playlist_ = playlist;
}



} // namespace dtv
