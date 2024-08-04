#pragma once

#include <boost/url.hpp>
#include <filesystem>
#include <set>
#include <string>

namespace dtv{
namespace fs = std::filesystem;

class CommandLine{
public:
    CommandLine();

    [[nodiscard]] CommandLine(const CommandLine &) = default;
    CommandLine(CommandLine &&) = default;
    CommandLine &operator=(const CommandLine &) = default;
    CommandLine &operator=(CommandLine &&) = default;

    fs::path Output() const;
    void Output(const fs::path &Output);
    [[nodiscard]] bool Force_overwrites() const;
    void Force_overwrites(bool Force_overwrites);
    [[nodiscard]] bool Write_description() const;
    void Write_description(bool Write_description);
    [[nodiscard]] fs::path Temp_dir() const;
    void Temp_dir(const fs::path &Temp_dir);
    [[nodiscard]] bool Quiet() const;
    void Quiet(bool Quiet);
    [[nodiscard]] bool Progress() const;
    void Progress(bool Progress);
    [[nodiscard]] int Height() const;
    void Height(int Height);
    [[nodiscard]] std::string Extension() const;
    void Extension(const std::string &Extension);
    [[nodiscard]] std::string Merge_output_extension() const;
    void Merge_output_extension(const std::string &Merge_output_extension);
    [[nodiscard]] bool Saving_original_video_resolution() const;
    void Saving_original_video_resolution(bool Saving_original_video_resolution);
    [[nodiscard]] bool Playlist() const;
    void Playlist(bool Playlist);
    [[nodiscard]] std::string Translate_from_lang() const;
    void Translate_from_lang(const std::string &Translate_from_lang);
    [[nodiscard]] std::string Translate_to_lang() const;
    void Translate_to_lang(const std::string &Translate_to_lang);
    [[nodiscard]] bool No_translate() const;
    void No_translate(bool No_translate);
    [[nodiscard]] bool Only_translate() const;
    void Only_translate(bool Only_translate);
    [[nodiscard]] fs::path Replace_audio() const;
    void Replace_audio(const fs::path &Replace_audio);
    [[nodiscard]] fs::path Replace_translate() const;
    void Replace_translate(const fs::path &Replace_translate);
    [[nodiscard]] double Vol_audio() const;
    void Vol_audio(double Vol_audio);
    [[nodiscard]] double Vol_translate() const;
    void Vol_translate(double Vol_translate);
    [[nodiscard]] bool Save_translation() const;
    void Save_translation(bool Save_translation);
    [[nodiscard]] bool Save_translation_no_merge() const;
    void Save_translation_no_merge(bool Save_translation_no_merge);
    [[nodiscard]] std::string Save_translation_contaner() const;
    void Save_translation_contaner(const std::string &Save_translation_contaner);
    [[nodiscard]] bool Write_subs() const;
    void Write_subs(bool Write_subs);
    [[nodiscard]] std::string Sub_lang() const;
    void Sub_lang(const std::string &Sub_lang);
    [[nodiscard]] bool Write_auto_subs() const;
    void Write_auto_subs(bool Write_auto_subs);
    [[nodiscard]] std::string Sub_format() const;
    void Sub_format(const std::string &Sub_format);
    [[nodiscard]] std::string Sub_langs() const;
    void Sub_langs(const std::string &Sub_langs);
    [[nodiscard]] bool Embed_subs() const;
    void Embed_subs(bool Embed_subs);
    [[nodiscard]] std::string Convert_subs() const;
    void Convert_subs(const std::string &Convert_subs);
    [[nodiscard]] bool Transcription() const;
    void Transcription(bool Transcription);
    [[nodiscard]] std::string Proxy() const;
    void Proxy(const std::string &Proxy);
    [[nodiscard]] std::string Exec_after() const;
    void Exec_after(const std::string &Exec_after);
    [[nodiscard]] std::string Exec_before() const;
    void Exec_before(const std::string &Exec_before);
    [[nodiscard]] std::set<boost::urls::url_view> Urls() const;
    void Urls(const std::set<boost::urls::url_view> &Urls);
    [[nodiscard]] bool Debug() const;
    void Debug(bool Debug);
    [[nodiscard]] bool Test() const;
    void Test(bool Test);

private:
    fs::path _output;
    bool _force_overwrites;
    bool _write_description;
    fs::path _temp_dir;
    bool _quiet;
    bool _progress;
    int _height;
    std::string _extension;
    std::string _merge_output_extension;
    bool _saving_original_video_resolution;
    bool _playlist;
    std::string _translate_from_lang;
    std::string _translate_to_lang;
    bool _no_translate;
    bool _only_translate;
    fs::path _replace_audio;
    fs::path _replace_translate;
    double _vol_audio;
    double _vol_translate;
    bool _save_translation;
    bool _save_translation_no_merge;
    std::string _save_translation_contaner;
    bool _write_subs;
    std::string _sub_lang;
    bool _write_auto_subs;
    //list_subs TODO печатать сразу в консоль
    std::string _sub_format; // FORMAT "srt" or "ass/srt/best"
    std::string _sub_langs;
    bool _embed_subs;
    std::string _convert_subs; // FORMAT ass, lrc, srt, vtt
    bool _transcription;
    std::string _proxy;
    std::string _exec_after;
    std::string _exec_before;
    std::set<boost::urls::url_view> _urls;
    bool _debug;
    bool _test;
};


} // namespace dtv
