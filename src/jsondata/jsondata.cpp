#include "jsondata.h"
#include <fstream>


JsonData::JsonData(const boost::json::value& value) {
    obj_ = value.as_object();
}

JsonData::JsonData(const std::filesystem::directory_entry& entry) {
    std::ifstream file(entry.path().filename());
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + entry.path().filename().string());
    }
    obj_ = boost::json::parse(file).as_object();
    //std::cout << obj_ << std::endl;
}

std::string JsonData::get_id() const {
    if (obj_.contains("id"))
        return obj_.at("id").as_string().c_str();
    return "";
}

std::string JsonData::get_title() const {
    if (obj_.contains("title"))
        return obj_.at("title").as_string().c_str();
    return "";
}

std::string JsonData::webpage_url() const {
    if (obj_.contains("webpage_url"))
        return obj_.at("webpage_url").as_string().c_str();
    return "";
}

std::string JsonData::get_extractor() const {
    if (obj_.contains("extractor"))
        return obj_.at("extractor").as_string().c_str();
    return "";
}

int64_t JsonData::get_playlist_index() const {
    if (obj_.contains("playlist_index"))
        return obj_.at("playlist_index").as_int64();
    return 0;
}

int64_t JsonData::get_playlist_count() const {
    if (obj_.contains("playlist_count"))
        return obj_.at("playlist_count").as_int64();
    return 0;
}

int64_t JsonData::get_duration() const {
    if (obj_.contains("duration"))
        return obj_.at("duration").as_int64();
    return 0;
}

int64_t JsonData::get_age_limit() const {
    if (obj_.contains("age_limit"))
        return obj_.at("age_limit").as_int64();
    return 0;
}


JsonExtractorInfo::JsonExtractorInfo(const std::filesystem::__cxx11::directory_entry &entry)
{
    std::ifstream file(entry.path().filename());
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + entry.path().filename().string());
    }
    obj_ = boost::json::parse(file).as_object();
    //std::cout << obj_ << std::endl;
}

std::shared_ptr<JsonData> JsonExtractorInfo::get_json_data() const
{
    if (obj_.contains("extractor")){

        if(obj_.at("extractor").as_string() == "youtube")
            return std::make_shared<JsonDataYoutube>(obj_);

        if(obj_.at("extractor").as_string() == "vimeo")
            return std::make_shared<JsonDataVimeo>(obj_);

        if(obj_.at("extractor").as_string() == "9gag")
            return std::make_shared<JsonDataNineGag>(obj_);
    }

    throw std::runtime_error("extractor not found");
}
