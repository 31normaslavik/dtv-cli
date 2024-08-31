#include "video.h"

namespace dtv {

// void VectorPtrVideos::PushBack(std::shared_ptr<Video> video_ptr) {
//     videos_ptr_.emplace_back(video_ptr);
// }

// std::vector<std::shared_ptr<Video>> VectorPtrVideos::GetAllData() const {
//     return videos_ptr_;
// }

Video tag_invoke(const bj::value_to_tag<Video> &, const boost::json::value &jv)
{
    Video v;

    bj::object const& obj = jv.get_object();
    bj::value const* p = nullptr;

    if(p = obj.if_contains("id"); p)
        v.id = p->get_string(); //(string): Video identifier
    if(p = obj.if_contains("title"); p)
        v.title = p->get_string(); // (string): Video title
    if(p = obj.if_contains("formats"), p) // (list) formats
        v.formats = bj::value_to<std::vector<Format>>(*p);
    if(p = obj.if_contains("fulltitle"); p)
        v.fulltitle = p->get_string(); // (string): Video title ignoring live timestamp and generic title
    if(p = obj.if_contains("ext"); p)
        v.ext = p->get_string(); // (string): Video filename extension
    if(p = obj.if_contains("alt_title"); p)
        v.alt_title = p->get_string(); // (string): A secondary title of the video
    if(p = obj.if_contains("description"); p)
        v.description = p->get_string(); // (string): The description of the video
    if(p = obj.if_contains("display_id"); p)
        v.display_id = p->get_string(); // (string): An alternative identifier for the video
    if(p = obj.if_contains("uploader"); p)
        v.uploader = p->get_string(); // (string): Full name of the video uploader
    if(p = obj.if_contains("uploader_id"); p)
        v.uploader_id = p->get_string(); // (string): Nickname or id of the video uploader
    if(p = obj.if_contains("uploader_url"); p)
        v.uploader_url = p->get_string(); // (string): URL to the video uploader's profile
    if(p = obj.if_contains("license"); p)
        v.license = p->get_string(); // (string): License name the video is licensed under
    if(p = obj.if_contains("creators"), p) // (list): The creators of the video
        v.creators = bj::value_to<std::vector<std::string>>(*p);
    if(p = obj.if_contains("creator"); p)
        v.creator = p->get_string(); // (string): The creators of the video; comma-separated
    p = obj.if_contains("timestamp"); // (numeric): UNIX timestamp of the moment the video became available
        v.timestamp = p ? p->is_double() ? p->get_double() : p->is_int64() ? p->get_int64() : -1 : -1;
    if(p = obj.if_contains("upload_date"); p)
        v.upload_date = p->get_string(); // (string): Video upload date in UTC (YYYYMMDD)
    p = obj.if_contains("release_timestamp"); // (numeric): UNIX timestamp of the moment the video was released
        v.release_timestamp = p ? p->is_double() ? p->get_double() : p->is_int64() ? p->get_int64() : -1 : -1;
    if(p = obj.if_contains("release_date"); p)v.release_date = obj.if_contains("release_date")->get_string(); // (string): The date (YYYYMMDD) when the video was released in UTC
    p = obj.if_contains("release_year"); // (numeric): Year (YYYY) when the video or album was released
        v.release_year = p ? p->is_double() ? p->get_double() : p->is_int64() ? p->get_int64() : -1 : -1;
    p = obj.if_contains("modified_timestamp"); // (numeric): UNIX timestamp of the moment the video was last modified
        v.modified_timestamp = p ? p->is_double() ? p->get_double() : p->is_int64() ? p->get_int64() : -1 : -1;
    if(p = obj.if_contains("modified_date"); p)
        v.modified_date = p->get_string(); // (string): The date (YYYYMMDD) when the video was last modified in UTC
    if(p = obj.if_contains("channel"); p)
        v.channel = p->get_string(); // (string): Full name of the channel the video is uploaded on
    if(p = obj.if_contains("channel_id"); p)
        v.channel_id = p->get_string(); // (string): Id of the channel
    if(p = obj.if_contains("channel_url"); p)
        v.channel_url = p->get_string(); // (string): URL of the channel
    p = obj.if_contains("channel_follower_count"); // (numeric): Number of followers of the channel
        v.channel_follower_count = p ? p->is_double() ? p->get_double() : p->is_int64() ? p->get_int64() : -1 : -1;
    if (p = obj.if_contains("channel_is_verified"); p)
        v.channel_is_verified = p->get_bool(); // (boolean): Whether the channel is verified on the platform
    if(p = obj.if_contains("location"); p)
        v.location = p->get_string(); // (string): Physical location where the video was filmed
    p = obj.if_contains("duration"); // (numeric): Length of the video in seconds
        v.duration = p ? p->is_double() ? p->get_double() : p->is_int64() ? p->get_int64() : -1 : -1;
    if(p = obj.if_contains("duration_string"); p)
        v.duration_string = p->get_string(); // (string): Length of the video (HH:mm:ss)
    p = obj.if_contains("view_count"); // (numeric): How many users have watched the video on the platform
        v.view_count = p ? p->is_double() ? p->get_double() : p->is_int64() ? p->get_int64() : -1 : -1;
    p = obj.if_contains("concurrent_view_count"); // (numeric): How many users are currently watching the video on the platform.
        v.concurrent_view_count = p ? p->is_double() ? p->get_double() : p->is_int64() ? p->get_int64() : -1 : -1;
    p = obj.if_contains("like_count"); // (numeric): Number of positive ratings of the video
        v.like_count = p ? p->is_double() ? p->get_double() : p->is_int64() ? p->get_int64() : -1 : -1;
    p = obj.if_contains("dislike_count"); // (numeric): Number of negative ratings of the video
        v.dislike_count = p ? p->is_double() ? p->get_double() : p->is_int64() ? p->get_int64() : -1 : -1;
    p = obj.if_contains("repost_count"); // (numeric): Number of reposts of the video
        v.repost_count = p ? p->is_double() ? p->get_double() : p->is_int64() ? p->get_int64() : -1 : -1;
    p = obj.if_contains("average_rating"); // (numeric): Average rating give by users, the scale used depends on the webpage
        v.average_rating = p ? p->is_double() ? p->get_double() : p->is_int64() ? p->get_int64() : -1 : -1;
    p = obj.if_contains("comment_count"); // (numeric): Number of comments on the video (For some extractors, comments are only downloaded at the end, and so this field cannot be used)
        v.comment_count = p ? p->is_double() ? p->get_double() : p->is_int64() ? p->get_int64() : -1 : -1;
    p = obj.if_contains("age_limit"); // (numeric): Age restriction for the video (years)
        v.age_limit = p ? p->is_double() ? p->get_double() : p->is_int64() ? p->get_int64() : -1 : -1;
    if(p = obj.if_contains("live_status"); p)
        v.live_status = p->get_string(); // (string): One of "not_live", "is_live", "is_upcoming", "was_live", "post_live" (was live, but VOD is not yet processed)
    if(p = obj.if_contains("is_live"); p)
        v.is_live = p->get_bool(); // (boolean): Whether this video is a live stream or a fixed-length video
    if(p = obj.if_contains("was_live"); p)
        v.was_live = p->get_bool(); // (boolean): Whether this video was originally a live stream
    if(p = obj.if_contains("playable_in_embed"); p)
        v.playable_in_embed = p->get_bool(); // (string): Whether this video is allowed to play in embedded players on other sites
    if(p = obj.if_contains("availability"); p)
        v.availability = p->get_string(); // (string): Whether the video is "private", "premium_only", "subscriber_only", "needs_auth", "unlisted" or "public"
    if(p = obj.if_contains("media_type"); p)
        v.media_type = p->get_string(); // (string): The type of media as classified by the site, e.g. "episode", "clip", "trailer"
    p = obj.if_contains("start_time"); // (numeric): Time in seconds where the reproduction should start, as specified in the URL
        v.start_time = p ? p->is_double() ? p->get_double() : p->is_int64() ? p->get_int64() : -1 : -1;
    p = obj.if_contains("end_time"); // (numeric): Time in seconds where the reproduction should end, as specified in the URL
        v.end_time = p ? p->is_double() ? p->get_double() : p->is_int64() ? p->get_int64() : -1 : -1;
    if(p = obj.if_contains("extractor"); p)
        v.extractor = p->get_string(); // (string): Name of the extractor
    if(p = obj.if_contains("extractor_key"); p)
        v.extractor_key = p->get_string(); // (string): Key name of the extractor
    p = obj.if_contains("epoch"); // (numeric): Unix epoch of when the information extraction was completed
        v.epoch = p ? p->is_double() ? p->get_double() : p->is_int64() ? p->get_int64() : -1 : -1;
    p = obj.if_contains("autonumber"); // (numeric): Number that will be increased with each download, starting at --autonumber-start, padded with leading zeros to 5 digits
        v.autonumber = p ? p->is_double() ? p->get_double() : p->is_int64() ? p->get_int64() : -1 : -1;
    p = obj.if_contains("video_autonumber"); // (numeric): Number that will be increased with each video
        v.video_autonumber = p ? p->is_double() ? p->get_double() : p->is_int64() ? p->get_int64() : -1 : -1;
    p = obj.if_contains("n_entries"); // (numeric): Total number of extracted items in the playlist
        v.n_entries = p ? p->is_double() ? p->get_double() : p->is_int64() ? p->get_int64() : -1 : -1;
    if(p = obj.if_contains("playlist_id"); p)
        v.playlist_id = p->get_string(); // (string): Identifier of the playlist that contains the video
    if(p = obj.if_contains("playlist_title"); p)
        v.playlist_title = p->get_string(); // (string): Name of the playlist that contains the video
    if(p = obj.if_contains("playlist"); p)
        v.playlist = p->get_string(); // (string): playlist_id or playlist_title
    p = obj.if_contains("playlist_count"); // (numeric): Total number of items in the playlist. May not be known if entire playlist is not extracted
        v.playlist_count = p ? p->is_double() ? p->get_double() : p->is_int64() ? p->get_int64() : -1 : -1;
    p = obj.if_contains("playlist_index"); // (numeric): Index of the video in the playlist padded with leading zeros according the final index
        v.playlist_index = p ? p->is_double() ? p->get_double() : p->is_int64() ? p->get_int64() : -1 : -1;
    p = obj.if_contains("playlist_autonumber"); // (numeric): Position of the video in the playlist download queue padded with leading zeros according to the total length of the playlist
        v.playlist_autonumber = p ? p->is_double() ? p->get_double() : p->is_int64() ? p->get_int64() : -1 : -1;
    if(p = obj.if_contains("playlist_uploader"); p)
        v.playlist_uploader = p->get_string(); // (string): Full name of the playlist uploader
    if(p = obj.if_contains("playlist_uploader_id"); p)
        v.playlist_uploader_id = p->get_string(); // (string): Nickname or id of the playlist uploader
    if(p = obj.if_contains("webpage_url"); p)
        v.webpage_url = p->get_string(); // (string): A URL to the video webpage which if given to yt-dlp should allow to get the same result again
    if(p = obj.if_contains("webpage_url_basename"); p)
        v.webpage_url_basename = p->get_string(); // (string): The basename of the webpage URL
    if(p = obj.if_contains("webpage_url_domain"); p)
        v.webpage_url_domain = p->get_string(); // (string): The domain of the webpage URL
    if(p = obj.if_contains("original_url"); p)
        v.original_url = p->get_string(); // (string): The URL given by the user (or same as webpage_url for playlist entries)
    if(obj.if_contains("categories"), p) // (list): List of categories the video belongs to
        v.categories = bj::value_to<std::vector<std::string>>(*p);
    if(obj.if_contains("tags"), p) // (list): List of tags assigned to the video
        v.tags = bj::value_to<std::vector<std::string>>(*p);
    if(obj.if_contains("cast"), p) // (list): List of cast members
        v.cast = bj::value_to<std::vector<std::string>>(*p);

    return v;
}

std::vector<Format> tag_invoke(const bj::value_to_tag<std::vector<Format> > &, const boost::json::value &jv)
{
    if(!jv.is_array())
        return {};

    bj::array const& arr = jv.get_array();

    std::vector<Format> vf;
    Format format;
    bj::value const* p = nullptr;

    for(auto const& f: arr){
        bj::object const& o = f.get_object();

        if(p = o.if_contains("width"), p)
            format.width = p ? p->get_int64() : -1;

        if(p = o.if_contains("height"), p)
            format.height = p ? p->get_int64() : -1;

        if(p = o.if_contains("ext"), p)
            format.ext = p->get_string();

        if(p = o.if_contains("format_id"), p)
            format.format_id = p->get_string();

        if(p = o.if_contains("resolution"), p)
            format.resolution = p->get_string();

        if(p = o.if_contains("dynamic_range"), p)
            format.dynamic_range = p->get_string();

        if(p = o.if_contains("video_ext"), p)
            format.video_ext = p->get_string();

        if(p = o.if_contains("audio_ext"), p)
            format.audio_ext = p->get_string();

        if(p = o.if_contains("format"), p)
            format.format = p->get_string();

        p = o.if_contains("tbr");
            format.tbr = p ? p->is_double() ? p->get_double() : p->is_int64() ? p->get_int64() : -1 : -1;
        p = o.if_contains("vbr");
            format.vbr = p ? p->is_double() ? p->get_double() : p->is_int64() ? p->get_int64() : -1 : -1;
        p = o.if_contains("abr");
            format.abr = p ? p->is_double() ? p->get_double() : p->is_int64() ? p->get_int64() : -1 : -1;

        vf.emplace_back(std::move(format));
    }
    return vf;
}


} // namespace dtv
