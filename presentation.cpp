//
// Created by pancake on 12/14/23.
//
#include "presentation.h"
#include <map>
#include <stdexcept>

FORMAT_VIDEO format_video_argv(const std::string& format) {
	if (const std::map<std::string, FORMAT_VIDEO> exts{
		{"mp4_4320_60_10", FORMAT_VIDEO::MP4_7680x4320_60_10},
		{"mp4_2160_60_10", FORMAT_VIDEO::MP4_3840x2160_60_10},
		{"mp4_2160_30", FORMAT_VIDEO::MP4_3840x2160_30},
		{"mp4_1440_60_10", FORMAT_VIDEO::MP4_2560x1440_60_10},
		{"mp4_1440_30", FORMAT_VIDEO::MP4_2560x1440_30},
		{"mp4_1080_60_10", FORMAT_VIDEO::MP4_1920x1080_60_10},
		{"mp4_1080_60", FORMAT_VIDEO::MP4_1920x1080_60},
		{"mp4_1080_30", FORMAT_VIDEO::MP4_1920x1080_30},
		{"mp4_720_60_10", FORMAT_VIDEO::MP4_1280x720_60_10},
		{"mp4_720_60", FORMAT_VIDEO::MP4_1280x720_60},
		{"mp4_720_30", FORMAT_VIDEO::MP4_1280x720_30},
		{"mp4_480_60_10", FORMAT_VIDEO::MP4_854x480_60_10},
		{"mp4_480_30", FORMAT_VIDEO::MP4_854x480_30},
		{"mp4_360_60_10", FORMAT_VIDEO::MP4_640x360_60_10},
		{"mp4_360_30", FORMAT_VIDEO::MP4_640x360_30},
		{"webm_2160_60_10", FORMAT_VIDEO::WEBM_3840x2160_60_10},
		{"webm_2160_60", FORMAT_VIDEO::WEBM_3840x2160_60},
		{"webm_2160_30", FORMAT_VIDEO::WEBM_3840x2160_30},
		{"webm_1440_60_10", FORMAT_VIDEO::WEBM_2560x1440_60_10},
		{"webm_1440_60", FORMAT_VIDEO::WEBM_2560x1440_60},
		{"webm_1440_30", FORMAT_VIDEO::WEBM_2560x1440_30},
		{"webm_1080_60_10", FORMAT_VIDEO::WEBM_1920x1080_60_10},
		{"webm_1080_60", FORMAT_VIDEO::WEBM_1920x1080_60},
		{"webm_1080_30", FORMAT_VIDEO::WEBM_1920x1080_30},
		{"webm_720_60_10", FORMAT_VIDEO::WEBM_1280x720_60_10},
		{"webm_720_60", FORMAT_VIDEO::WEBM_1280x720_60},
		{"webm_720_30", FORMAT_VIDEO::WEBM_1280x720_30},
		{"webm_480_60_10", FORMAT_VIDEO::WEBM_854x480_60_10},
		{"webm_480_30", FORMAT_VIDEO::WEBM_854x480_30},
		{"webm_360_60_10", FORMAT_VIDEO::WEBM_640x360_60_10},
		{"webm_360_30", FORMAT_VIDEO::WEBM_640x360_30}
	}; exts.contains(format))
		return exts.at(format);
	return FORMAT_VIDEO::UNKNOWNV;
}

std::string combinate_format(const FORMAT_VIDEO& format) {
	std::string format_to_string;
	bool is_mp4 = false;

	switch (format) {
		case FORMAT_VIDEO::MP4_7680x4320_60_10: format_to_string.
					append(std::to_string(static_cast<int>(FORMAT_VIDEO::MP4_7680x4320_60_10)).append("/"));
		case FORMAT_VIDEO::MP4_3840x2160_60_10: format_to_string.
					append(std::to_string(static_cast<int>(FORMAT_VIDEO::MP4_3840x2160_60_10)).append("/"));
		case FORMAT_VIDEO::MP4_3840x2160_30: format_to_string.
					append(std::to_string(static_cast<int>(FORMAT_VIDEO::MP4_3840x2160_30)).append("/"));
		case FORMAT_VIDEO::MP4_2560x1440_60_10: format_to_string.
					append(std::to_string(static_cast<int>(FORMAT_VIDEO::MP4_2560x1440_60_10)).append("/"));
		case FORMAT_VIDEO::MP4_2560x1440_30: format_to_string.
					append(std::to_string(static_cast<int>(FORMAT_VIDEO::MP4_2560x1440_30)).append("/"));
		case FORMAT_VIDEO::MP4_1920x1080_60_10: format_to_string.
					append(std::to_string(static_cast<int>(FORMAT_VIDEO::MP4_1920x1080_60_10)).append("/"));
		case FORMAT_VIDEO::MP4_1920x1080_60: format_to_string.
					append(std::to_string(static_cast<int>(FORMAT_VIDEO::MP4_1920x1080_60)).append("/"));
		case FORMAT_VIDEO::MP4_1920x1080_30: format_to_string.
					append(std::to_string(static_cast<int>(FORMAT_VIDEO::MP4_1920x1080_30)).append("/"));
		case FORMAT_VIDEO::MP4_1280x720_30: format_to_string.
					append(std::to_string(static_cast<int>(FORMAT_VIDEO::MP4_1280x720_30)).append("/"));
		case FORMAT_VIDEO::MP4_854x480_30: format_to_string.
					append(std::to_string(static_cast<int>(FORMAT_VIDEO::MP4_854x480_30)).append("/bestvideo,"));
			is_mp4 = true;
			break;

		case FORMAT_VIDEO::WEBM_3840x2160_60_10: format_to_string.
					append(std::to_string(static_cast<int>(FORMAT_VIDEO::WEBM_3840x2160_60_10)).append("/"));
		case FORMAT_VIDEO::WEBM_3840x2160_60: format_to_string.
					append(std::to_string(static_cast<int>(FORMAT_VIDEO::WEBM_3840x2160_60)).append("/"));
		case FORMAT_VIDEO::WEBM_3840x2160_30: format_to_string.
					append(std::to_string(static_cast<int>(FORMAT_VIDEO::WEBM_3840x2160_30)).append("/"));
		case FORMAT_VIDEO::WEBM_2560x1440_60_10: format_to_string.
					append(std::to_string(static_cast<int>(FORMAT_VIDEO::WEBM_2560x1440_60_10)).append("/"));
		case FORMAT_VIDEO::WEBM_2560x1440_60: format_to_string.
					append(std::to_string(static_cast<int>(FORMAT_VIDEO::WEBM_2560x1440_60)).append("/"));
		case FORMAT_VIDEO::WEBM_2560x1440_30: format_to_string.
					append(std::to_string(static_cast<int>(FORMAT_VIDEO::WEBM_2560x1440_30)).append("/"));
		case FORMAT_VIDEO::WEBM_1920x1080_60_10: format_to_string.
					append(std::to_string(static_cast<int>(FORMAT_VIDEO::WEBM_1920x1080_60_10)).append("/"));
		case FORMAT_VIDEO::WEBM_1920x1080_60: format_to_string.
					append(std::to_string(static_cast<int>(FORMAT_VIDEO::WEBM_1920x1080_60)).append("/"));
		case FORMAT_VIDEO::WEBM_1920x1080_30: format_to_string.
					append(std::to_string(static_cast<int>(FORMAT_VIDEO::WEBM_1920x1080_30)).append("/"));
		case FORMAT_VIDEO::WEBM_1280x720_30: format_to_string.
					append(std::to_string(static_cast<int>(FORMAT_VIDEO::WEBM_1280x720_30)).append("/"));
		case FORMAT_VIDEO::WEBM_854x480_30: format_to_string.
					append(std::to_string(static_cast<int>(FORMAT_VIDEO::WEBM_854x480_30)).append("/bestvideo,"));
			break;

		default: throw std::runtime_error("wrong video format");
			break;
	}

	if (is_mp4) format_to_string.append("140/139/599/bestaudio");
	else format_to_string.append("251/250/249/600/bestaudio");

	return format_to_string;
}
