#pragma once

#include <boost/json.hpp>
#include <filesystem>


class JsonData {
public:
    explicit JsonData(const boost::json::value& value);

    explicit JsonData(const std::filesystem::directory_entry& entry);

    [[nodiscard]] virtual std::string get_id()         const;
    [[nodiscard]] virtual std::string get_title()      const;
    [[nodiscard]] virtual std::string webpage_url()    const;
    [[nodiscard]] virtual std::string get_extractor()  const;
    [[nodiscard]] virtual int64_t get_playlist_index() const;
    [[nodiscard]] virtual int64_t get_playlist_count() const;
    [[nodiscard]] virtual int64_t get_duration()       const;
    [[nodiscard]] virtual int64_t get_age_limit()      const;

private:
    boost::json::object obj_;
};


class JsonDataYoutube: public JsonData{
public:
    explicit JsonDataYoutube(const boost::json::value& value): JsonData(value){

    }
    explicit JsonDataYoutube(const std::filesystem::directory_entry& entry): JsonData(entry){

    }
};

class JsonDataVimeo: public JsonData{
public:
    explicit JsonDataVimeo(const boost::json::value& value): JsonData(value){

    }
    explicit JsonDataVimeo(const std::filesystem::directory_entry& entry): JsonData(entry){

    }

    [[nodiscard]] int64_t get_playlist_index() const override {return 0;}
    [[nodiscard]] int64_t get_playlist_count() const override {return 0;}
    [[nodiscard]] int64_t get_age_limit()      const override {return 0;}

};

class JsonDataNineGag: public JsonData{
public:
    explicit JsonDataNineGag(const boost::json::value& value): JsonData(value){

    }
    explicit JsonDataNineGag(const std::filesystem::directory_entry& entry): JsonData(entry){

    }

    [[nodiscard]] int64_t get_playlist_index() const override {return 0;}
    [[nodiscard]] int64_t get_playlist_count() const override {return 0;}
    [[nodiscard]] int64_t get_age_limit()      const override {return 0;}

};

class JsonExtractorInfo{
public:
    explicit JsonExtractorInfo(const boost::json::value& value): obj_{value.as_object()}{}
    explicit JsonExtractorInfo(const std::filesystem::directory_entry& entry);
    [[nodiscard]] virtual std::shared_ptr<JsonData> get_json_data()  const;
private:
    boost::json::object obj_;
};

