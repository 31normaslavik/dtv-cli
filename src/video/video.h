#pragma once

#include <memory>
#include <string>
#include <vector>

namespace dtv {

struct Format;

struct Video {

std::string id; //(string): Video identifier
std::string title; // (string): Video title
std::vector<Format> formats; // (list) formats
std::string fulltitle; // (string): Video title ignoring live timestamp and generic title
std::string ext; // (string): Video filename extension
std::string alt_title; // (string): A secondary title of the video
std::string description; // (string): The description of the video
std::string display_id; // (string): An alternative identifier for the video
std::string uploader; // (string): Full name of the video uploader
std::string uploader_id; // (string): Nickname or id of the video uploader
std::string uploader_url; // (string): URL to the video uploader's profile
std::string license; // (string): License name the video is licensed under
std::vector<std::string> creators; // (list): The creators of the video
std::string creator; // (string): The creators of the video; comma-separated
double timestamp; // (numeric): UNIX timestamp of the moment the video became available
std::string upload_date; // (string): Video upload date in UTC (YYYYMMDD)
double release_timestamp; // (numeric): UNIX timestamp of the moment the video was released
std::string release_date; // (string): The date (YYYYMMDD) when the video was released in UTC
double release_year; // (numeric): Year (YYYY) when the video or album was released
double modified_timestamp; // (numeric): UNIX timestamp of the moment the video was last modified
std::string modified_date; // (string): The date (YYYYMMDD) when the video was last modified in UTC
std::string channel; // (string): Full name of the channel the video is uploaded on
std::string channel_id; // (string): Id of the channel
std::string channel_url; // (string): URL of the channel
double channel_follower_count; // (numeric): Number of followers of the channel
bool channel_is_verified; // (boolean): Whether the channel is verified on the platform
std::string location; // (string): Physical location where the video was filmed
double duration; // (numeric): Length of the video in seconds
std::string duration_string; // (string): Length of the video (HH:mm:ss)
int64_t view_count; // (numeric): How many users have watched the video on the platform
int64_t concurrent_view_count; // (numeric): How many users are currently watching the video on the platform.
int64_t like_count; // (numeric): Number of positive ratings of the video
int64_t dislike_count; // (numeric): Number of negative ratings of the video
int64_t repost_count; // (numeric): Number of reposts of the video
int64_t average_rating; // (numeric): Average rating give by users, the scale used depends on the webpage
int64_t comment_count; // (numeric): Number of comments on the video (For some extractors, comments are only downloaded at the end, and so this field cannot be used)
int64_t age_limit; // (numeric): Age restriction for the video (years)
std::string live_status; // (string): One of "not_live", "is_live", "is_upcoming", "was_live", "post_live" (was live, but VOD is not yet processed)
bool is_live; // (boolean): Whether this video is a live stream or a fixed-length video
bool was_live; // (boolean): Whether this video was originally a live stream
std::string playable_in_embed; // (string): Whether this video is allowed to play in embedded players on other sites
std::string availability; // (string): Whether the video is "private", "premium_only", "subscriber_only", "needs_auth", "unlisted" or "public"
std::string media_type; // (string): The type of media as classified by the site, e.g. "episode", "clip", "trailer"
double start_time; // (numeric): Time in seconds where the reproduction should start, as specified in the URL
double end_time; // (numeric): Time in seconds where the reproduction should end, as specified in the URL
std::string extractor; // (string): Name of the extractor
std::string extractor_key; // (string): Key name of the extractor
double epoch; // (numeric): Unix epoch of when the information extraction was completed
int64_t autonumber; // (numeric): Number that will be increased with each download, starting at --autonumber-start, padded with leading zeros to 5 digits
int64_t video_autonumber; // (numeric): Number that will be increased with each video
int64_t n_entries; // (numeric): Total number of extracted items in the playlist
std::string playlist_id; // (string): Identifier of the playlist that contains the video
std::string playlist_title; // (string): Name of the playlist that contains the video
std::string playlist; // (string): playlist_id or playlist_title
int64_t playlist_count; // (numeric): Total number of items in the playlist. May not be known if entire playlist is not extracted
int64_t playlist_index; // (numeric): Index of the video in the playlist padded with leading zeros according the final index
int64_t playlist_autonumber; // (numeric): Position of the video in the playlist download queue padded with leading zeros according to the total length of the playlist
std::string playlist_uploader; // (string): Full name of the playlist uploader
std::string playlist_uploader_id; // (string): Nickname or id of the playlist uploader
std::string webpage_url; // (string): A URL to the video webpage which if given to yt-dlp should allow to get the same result again
std::string webpage_url_basename; // (string): The basename of the webpage URL
std::string webpage_url_domain; // (string): The domain of the webpage URL
std::string original_url; // (string): The URL given by the user (or same as webpage_url for playlist entries)
std::vector<std::string> categories; // (list): List of categories the video belongs to
std::vector<std::string> tags; // (list): List of tags assigned to the video
std::vector<std::string> cast; // (list): List of cast members

};

class VectorPtrVideos final {
public:
    void PushBack(std::shared_ptr<Video> video_ptr);

    [[nodiscard]] std::vector<std::shared_ptr<Video>> GetAllData() const;

private:
    std::vector<std::shared_ptr<Video>> videos_ptr_;
};


} // namespace dtv
