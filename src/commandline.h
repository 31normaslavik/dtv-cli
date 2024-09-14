#pragma once

#include "fs_directories.h"
#include <boost/url.hpp>
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

    std::shared_ptr<FsDirectories> Output() const;
    [[nodiscard]] bool NoOverwrites() const;
    [[nodiscard]] bool WriteDescription() const;
    [[nodiscard]] bool Quiet() const;
    [[nodiscard]] bool Progress() const;
    [[nodiscard]] int Height() const;
    [[nodiscard]] std::string Extension() const;
    [[nodiscard]] std::string MergeOutputExtension() const;
    [[nodiscard]] bool SavingOriginalVideoResolution() const;
    [[nodiscard]] bool YesPlaylist() const;
    [[nodiscard]] int Fps() const;
    [[nodiscard]] std::string TranslateFromLang() const;
    [[nodiscard]] std::string TranslateToLang() const;
    [[nodiscard]] bool WithoutTranslation() const;
    [[nodiscard]] bool TranslationOnly() const;
    [[nodiscard]] fs::path ReplaceSound() const;
    [[nodiscard]] fs::path ReplaceTranslate() const;
    [[nodiscard]] double Vol_audio() const;
    [[nodiscard]] double Vol_translate() const;
    [[nodiscard]] bool Save_translation() const;
    [[nodiscard]] bool Save_translation_no_merge() const;
    [[nodiscard]] std::string Save_translation_contaner() const;
    [[nodiscard]] bool Write_subs() const;
    [[nodiscard]] std::string Sub_lang() const;
    [[nodiscard]] bool Write_auto_subs() const;
    [[nodiscard]] std::string Sub_format() const;
    [[nodiscard]] std::string Sub_langs() const;
    [[nodiscard]] bool Embed_subs() const;
    [[nodiscard]] std::string Convert_subs() const;
    [[nodiscard]] bool Transcription() const;
    [[nodiscard]] std::string Proxy() const;
    [[nodiscard]] std::string Exec_after() const;
    [[nodiscard]] std::string Exec_before() const;
    [[nodiscard]] std::set<std::string> Urls() const;
    [[nodiscard]] bool Test() const;

    void Output(const fs::path &output);
    void No_overwrites(bool no_overwrites);
    void Write_description(bool Write_description);
    void Temp_dir(const fs::path &temp_dir);
    void Quiet(bool Quiet);
    void Progress(bool Progress);
    void Height(int Height);
    void Extension(const std::string &Extension);
    void Merge_output_extension(const std::string &Merge_output_extension);
    void Saving_original_video_resolution(bool Saving_original_video_resolution);
    void YesPlaylist(bool yesPlaylist);
    void Fps(int fps);
    void Translate_from_lang(const std::string &Translate_from_lang);
    void Translate_to_lang(const std::string &translate_to_lang);
    void No_translate(bool No_translate);
    void Only_translate(bool only_translate);
    void Replace_audio(const fs::path &replace_audio);
    void Replace_translate(const fs::path &Replace_translate);
    void Vol_audio(double Vol_audio);
    void Vol_translate(double Vol_translate);
    void Save_translation(bool Save_translation);
    void Save_translation_no_merge(bool Save_translation_no_merge);
    void Save_translation_contaner(const std::string &Save_translation_contaner);
    void Write_subs(bool Write_subs);
    void Sub_lang(const std::string &Sub_lang);
    void Write_auto_subs(bool Write_auto_subs);
    void Sub_format(const std::string &Sub_format);
    void Sub_langs(const std::string &Sub_langs);
    void Embed_subs(bool Embed_subs);
    void Convert_subs(const std::string &convert_subs);
    void Transcription(bool transcription);
    void Proxy(const std::string &proxy);
    void Exec_after(const std::string &exec_after);
    void Exec_before(const std::string &exec_before);
    void Urls(const std::set<std::string> &urls);
    void Test(bool Test);

private:
    std::shared_ptr<dtv::FsDirectories> _output;
    bool _no_overwrites{false};
    bool _write_description{false};
    bool _quiet{false};
    bool _progress{false};
    int _height;
    std::string _extension;
    std::string _merge_output_extension;
    bool _saving_original_video_resolution{false};
    bool _yesPlaylist{false};
    int _fps{30};
    std::string _translate_from_lang;
    std::string _translate_to_lang;
    bool _no_translate{false};
    bool _only_translate{false};
    fs::path _replace_audio;
    fs::path _replace_translate;
    double _vol_audio;
    double _vol_translate;
    bool _save_translation{false};
    bool _save_translation_no_merge{false};
    std::string _save_translation_contaner;
    bool _write_subs{false};
    std::string _sub_lang;
    bool _write_auto_subs{false};
    //list_subs TODO печатать сразу в консоль
    std::string _sub_format; // FORMAT "srt" or "ass/srt/best"
    std::string _sub_langs;
    bool _embed_subs{false};
    std::string _convert_subs; // FORMAT ass, lrc, srt, vtt
    bool _transcription{false};
    std::string _proxy;
    std::string _exec_after;
    std::string _exec_before;
    std::set<std::string> _urls;
    bool _test{false};
};

} // namespace dtv
