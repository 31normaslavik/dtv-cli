#include "jsondata.h"
#include <boost/json/parse.hpp>
#include <fstream>


dtv::JsonData::JsonData(const boost::json::value& value) {
    obj_ = value.as_object();
}

dtv::JsonData::JsonData(const std::filesystem::directory_entry& entry) {
    std::ifstream file(entry.path().filename());
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + entry.path().filename().string());
    }
    obj_ = boost::json::parse(file).as_object();
    //std::cout << obj_ << std::endl;
}

std::string dtv::JsonData::Id() const {
    if (obj_.contains("id"))
        return obj_.at("id").as_string().c_str();
    return "";
}

std::string dtv::JsonData::Title() const {
    if (obj_.contains("title"))
        return obj_.at("title").as_string().c_str();
    return "";
}

std::string dtv::JsonData::Fulltitle() const
{
    if (obj_.contains("fulltitle"))
        return obj_.at("fulltitle").as_string().c_str();
    return "";
}

std::string dtv::JsonData::Description() const
{
    if (obj_.contains("description"))
        return obj_.at("description").as_string().c_str();
    return "";
}

std::string dtv::JsonData::Webpage_url() const {
    if (obj_.contains("webpage_url"))
        return obj_.at("webpage_url").as_string().c_str();
    return "";
}

std::string dtv::JsonData::Extractor() const {
    if (obj_.contains("extractor"))
        return obj_.at("extractor").as_string().c_str();
    return "";
}

std::string dtv::JsonData::Channel() const
{
    if (obj_.contains("channel"))
        return obj_.at("channel").as_string().c_str();
    return "";
}

std::string dtv::JsonData::Upload_date() const
{
    if (obj_.contains("upload_date"))
        return obj_.at("upload_date").as_string().c_str();
    return "";
}

std::string dtv::JsonData::Availability() const
{
    if (obj_.contains("availability"))
        return obj_.at("availability").as_string().c_str();
    return "";
}

std::string dtv::JsonData::Playlist() const
{
    if (obj_.contains("playlist"))
        return obj_.at("playlist").as_string().c_str();
    return "";
}

std::string dtv::JsonData::Playlist_id() const
{
    if (obj_.contains("playlist_id"))
        return obj_.at("playlist_id").as_string().c_str();
    return "";
}

std::string dtv::JsonData::Playlist_title() const
{
    if (obj_.contains("playlist_title"))
        return obj_.at("playlist_title").as_string().c_str();
    return "";
}

std::string dtv::JsonData::Duration_string() const
{
    if (obj_.contains("duration_string"))
        return obj_.at("duration_string").as_string().c_str();
    return "";
}

std::string dtv::JsonData::Format() const
{
    if (obj_.contains("format"))
        return obj_.at("format").as_string().c_str();
    return "";
}

std::string dtv::JsonData::Format_id() const
{
    if (obj_.contains("format_id"))
        return obj_.at("format_id").as_string().c_str();
    return "";
}

std::string dtv::JsonData::Ext() const
{
    if (obj_.contains("ext"))
        return obj_.at("ext").as_string().c_str();
    return "";
}

std::string dtv::JsonData::Video_ext() const
{
    if (obj_.contains("video_ext"))
        return obj_.at("video_ext").as_string().c_str();
    return "";
}

std::string dtv::JsonData::Audio_ext() const
{
    if (obj_.contains("audio_ext"))
        return obj_.at("audio_ext").as_string().c_str();
    return "";
}

std::string dtv::JsonData::Language() const
{
    if (obj_.contains("language"))
        return obj_.at("language").as_string().c_str();
    return "";
}

std::string dtv::JsonData::Format_note() const
{
    if (obj_.contains("format_note"))
        return obj_.at("format_note").as_string().c_str();
    return "";
}

std::string dtv::JsonData::Resolution() const
{
    if (obj_.contains("resolution"))
        return obj_.at("resolution").as_string().c_str();
    return "";
}

std::string dtv::JsonData::Dynamic_range() const
{
    if (obj_.contains("dynamic_range"))
        return obj_.at("dynamic_range").as_string().c_str();
    return "";
}

std::string dtv::JsonData::Vcodec() const
{
    if (obj_.contains("vcodec"))
        return obj_.at("vcodec").as_string().c_str();
    return "";
}

std::string dtv::JsonData::Acodec() const
{
    if (obj_.contains("acodec"))
        return obj_.at("acodec").as_string().c_str();
    return "";
}

std::string dtv::JsonData::_type() const
{
    if (obj_.contains("_type"))
        return obj_.at("_type").as_string().c_str();
    return "";
}

// std::vector<std::string> dtv::JsonData::Categories() const
// {
//     if (obj_.contains("categories") && obj_.at("categories").is_array()){
//         std::vector< std::string > v = value_to< std::vector< std::string > >( obj_.at("categories") );
//         return v;
//     }
//     return {};
// }

int64_t dtv::JsonData::Playlist_index() const {
    if (obj_.contains("playlist_index"))
        return obj_.at("playlist_index").as_int64();
    return 0;
}

int64_t dtv::JsonData::Vbr() const
{
    if (obj_.contains("vbr"))
        return obj_.at("vbr").as_int64();
    return 0;
}

int64_t dtv::JsonData::Asr() const
{
    if (obj_.contains("asr"))
        return obj_.at("asr").as_int64();
    return 0;
}

int64_t dtv::JsonData::Audio_channels() const
{
    if (obj_.contains("audio_channels"))
        return obj_.at("audio_channels").as_int64();
    return 0;
}

int64_t dtv::JsonData::Width() const
{
    if (obj_.contains("width"))
        return obj_.at("width").as_int64();
    return 0;
}

int64_t dtv::JsonData::Height() const
{
    if (obj_.contains("height"))
        return obj_.at("height").as_int64();
    return 0;
}

int64_t dtv::JsonData::Fps() const
{
    if (obj_.contains("fps"))
        return obj_.at("fps").as_int64();
    return 0;
}

int64_t dtv::JsonData::Playlist_count() const {
    if (obj_.contains("playlist_count"))
        return obj_.at("playlist_count").as_int64();
    return 0;
}

int64_t dtv::JsonData::N_entries() const
{
    if (obj_.contains("n_entries"))
        return obj_.at("n_entries").as_int64();
    return 0;
}

int64_t dtv::JsonData::Duration() const {
    if (obj_.contains("duration"))
        return obj_.at("duration").as_int64();
    return 0;
}

int64_t dtv::JsonData::Age_limit() const {
    if (obj_.contains("age_limit"))
        return obj_.at("age_limit").as_int64();
    return 0;
}




dtv::JsonExtractorInfo::JsonExtractorInfo(const boost::json::value &value): obj_{value.as_object()}{}

dtv::JsonExtractorInfo::JsonExtractorInfo(const std::filesystem::directory_entry &entry)
{
    std::ifstream file(entry.path().filename());
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + entry.path().filename().string());
    }
    obj_ = boost::json::parse(file).as_object();
    //std::cout << obj_ << std::endl;
}

std::shared_ptr<dtv::JsonData> dtv::JsonExtractorInfo::GetJsonData() const
{
    if (obj_.contains("extractor")){

        if(obj_.at("extractor").as_string() == "youtube")
            return std::make_shared<JsonDataYoutube>(obj_);

        if(obj_.at("extractor").as_string() == "vimeo")
            return std::make_shared<JsonDataVimeo>(obj_);

        if(obj_.at("extractor").as_string() == "9gag")
            return std::make_shared<JsonDataNineGag>(obj_);
    }

    throw std::runtime_error("Extractor not found");
}

dtv::JsonDataYoutube::JsonDataYoutube(const boost::json::value &value): JsonData(value){

}

dtv::JsonDataYoutube::JsonDataYoutube(const std::filesystem::directory_entry &entry): JsonData(entry){

}

dtv::JsonDataVimeo::JsonDataVimeo(const boost::json::value &value): JsonData(value){

}

dtv::JsonDataVimeo::JsonDataVimeo(const std::filesystem::directory_entry &entry): JsonData(entry){

}

dtv::JsonDataNineGag::JsonDataNineGag(const boost::json::value &value): JsonData(value){

}

dtv::JsonDataNineGag::JsonDataNineGag(const std::filesystem::directory_entry &entry): JsonData(entry){

}
