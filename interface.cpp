#include "interface.h"

#include <fstream>
#include <utility>

VideoYoutube::VideoYoutube(std::string id, std::string title,
                           std::string webpage_url, std::string extractor,
                           int64_t playlist_index, int64_t playlist_count,
                           int64_t duration, int64_t age_limit): id{std::move(id)},
                                                                 title{std::move(title)},
                                                                 webpage_url{std::move(webpage_url)},
                                                                 extractor{std::move(extractor)},
                                                                 playlist_index{playlist_index},
                                                                 playlist_count{playlist_count},
                                                                 duration{duration},
                                                                 age_limit{age_limit} {
}

std::string VideoYoutube::get_id() const {
	return id;
}

std::string VideoYoutube::get_title() const {
	return title;
}

std::string VideoYoutube::get_webpage_url() const {
	return webpage_url;
}

std::string VideoYoutube::get_extractor() const {
	return extractor;
}

int64_t VideoYoutube::get_playlist_index() const {
	return playlist_index;
}

int64_t VideoYoutube::get_playlist_count() const {
	return playlist_count;
}

int64_t VideoYoutube::get_duration() const {
	return duration;
}

int64_t VideoYoutube::get_age_limit() const {
	return age_limit;
}

void VideoData::add(std::shared_ptr<Video> video) {
	videos.emplace_back(std::move(video));
}

std::vector<std::shared_ptr<Video>> VideoData::getAllData() const {
	return videos;
}

JsonData::JsonData(const boost::json::value& value) {
	obj = value.as_object();
}

JsonData::JsonData(const std::filesystem::directory_entry& entry) {
	std::ifstream file(entry.path().filename());
	if (!file.is_open()) {
		throw std::runtime_error("Could not open file: " + entry.path().filename().string());
	}
	obj = boost::json::parse(file).as_object();
	//std::cout << obj << std::endl;
}

std::string JsonData::get_id() const {
	if (obj.contains("id"))
		return obj.at("id").as_string().c_str();
	return "";
}

std::string JsonData::get_title() const {
	if (obj.contains("title"))
		return obj.at("title").as_string().c_str();
	return "";
}

std::string JsonData::webpage_url() const {
	if (obj.contains("webpage_url"))
		return obj.at("webpage_url").as_string().c_str();
	return "";
}

std::string JsonData::get_extractor() const {
	if (obj.contains("extractor"))
		return obj.at("extractor").as_string().c_str();
	return "";
}

int64_t JsonData::get_playlist_index() const {
	if (obj.contains("playlist_index"))
		return obj.at("playlist_index").as_int64();
	return 0;
}

int64_t JsonData::get_playlist_count() const {
	if (obj.contains("playlist_count"))
		return obj.at("playlist_count").as_int64();
	return 0;
}

int64_t JsonData::get_duration() const {
	if (obj.contains("duration"))
		return obj.at("duration").as_int64();
	return 0;
}

int64_t JsonData::get_age_limit() const {
	if (obj.contains("age_limit"))
		return obj.at("age_limit").as_int64();
	return 0;
}
