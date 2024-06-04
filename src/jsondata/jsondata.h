#pragma once
#include <boost/json/object.hpp>
#include <filesystem>

namespace dtv {


class JsonData {
public:
    explicit JsonData(const boost::json::value& value);

    explicit JsonData(const std::filesystem::directory_entry& entry);

    [[nodiscard]] virtual std::string Id() const;
    [[nodiscard]] virtual std::string Title() const;
    [[nodiscard]] virtual std::string Fulltitle() const;
    [[nodiscard]] virtual std::string Description() const;
    [[nodiscard]] virtual std::string Webpage_url() const;
    [[nodiscard]] virtual std::string Extractor() const;
    [[nodiscard]] virtual std::string Channel() const;
    [[nodiscard]] virtual std::string Upload_date() const;
    [[nodiscard]] virtual std::string Availability() const;
    [[nodiscard]] virtual std::string Playlist() const;
    [[nodiscard]] virtual std::string Playlist_id() const;
    [[nodiscard]] virtual std::string Playlist_title() const;
    [[nodiscard]] virtual std::string Duration_string() const;
    [[nodiscard]] virtual std::string Format() const;
    [[nodiscard]] virtual std::string Format_id() const;
    [[nodiscard]] virtual std::string Ext() const;
    [[nodiscard]] virtual std::string Video_ext() const;
    [[nodiscard]] virtual std::string Audio_ext() const;
    [[nodiscard]] virtual std::string Language() const;
    [[nodiscard]] virtual std::string Format_note() const;
    [[nodiscard]] virtual std::string Resolution() const;
    [[nodiscard]] virtual std::string Dynamic_range() const;
    [[nodiscard]] virtual std::string Vcodec() const;
    [[nodiscard]] virtual std::string Acodec() const;
    [[nodiscard]] virtual std::string _type() const;
    // [[nodiscard]] virtual std::vector<std::string> Categories() const;
    [[nodiscard]] virtual int64_t Playlist_index() const;
    [[nodiscard]] virtual int64_t Vbr() const;
    [[nodiscard]] virtual int64_t Asr() const;
    [[nodiscard]] virtual int64_t Audio_channels() const;
    [[nodiscard]] virtual int64_t Width() const;
    [[nodiscard]] virtual int64_t Height() const;
    [[nodiscard]] virtual int64_t Fps() const;
    [[nodiscard]] virtual int64_t Playlist_count() const;
    [[nodiscard]] virtual int64_t N_entries() const;
    [[nodiscard]] virtual int64_t Duration() const;
    [[nodiscard]] virtual int64_t Age_limit() const;
    virtual ~JsonData() = default;

private:
    boost::json::object obj_;
};


class JsonDataYoutube: public JsonData{
public:
    explicit JsonDataYoutube(const boost::json::value& value);
    explicit JsonDataYoutube(const std::filesystem::directory_entry& entry);
    virtual ~JsonDataYoutube() = default;
};

class JsonDataVimeo: public JsonData{
public:
    explicit JsonDataVimeo(const boost::json::value& value);
    explicit JsonDataVimeo(const std::filesystem::directory_entry& entry);
    virtual ~JsonDataVimeo() = default;
};

class JsonDataNineGag: public JsonData{
public:
    explicit JsonDataNineGag(const boost::json::value& value);
    explicit JsonDataNineGag(const std::filesystem::directory_entry &entry);
    virtual ~JsonDataNineGag() = default;
};

class JsonExtractorInfo{
public:
    explicit JsonExtractorInfo(const boost::json::value& value);
    explicit JsonExtractorInfo(const std::filesystem::directory_entry &entry);

    [[nodiscard]] virtual std::shared_ptr<JsonData> GetJsonData()  const;

    virtual ~JsonExtractorInfo() = default;
private:
    boost::json::object obj_;
};

} // namespace dtv
