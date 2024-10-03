#pragma once

#include "fs.h"
#include <set>
#include <string>

namespace dtv{
namespace fs = std::filesystem;

class CommandLine{
public:
    [[nodiscard]] std::shared_ptr<FsDir> Output() const;
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
    void Write_description(bool write_description);
    void Temp_dir(const fs::path &temp_dir);
    void Quiet(bool quiet);
    void Progress(bool progress);
    void Height(int height);
    void Extension(const std::string &extension);
    void Merge_output_extension(const std::string &merge_output_extension);
    void Saving_original_video_resolution(bool saving_original_video_resolution);
    void YesPlaylist(bool yes_playlist);
    void Fps(int fps);
    void Translate_from_lang(const std::string &translate_from_lang);
    void Translate_to_lang(const std::string &translate_to_lang);
    void No_translate(bool no_translate);
    void Only_translate(bool only_translate);
    void Replace_audio(const fs::path &replace_audio);
    void Replace_translate(const fs::path &replace_translate);
    void Vol_audio(double vol_audio);
    void Vol_translate(double vol_translate);
    void Save_translation(bool save_translation);
    void Save_translation_no_merge(bool save_translation_no_merge);
    void Save_translation_contaner(const std::string &save_translation_contaner);
    void Write_subs(bool write_subs);
    void Sub_lang(const std::string &sub_lang);
    void Write_auto_subs(bool write_auto_subs);
    void Sub_format(const std::string &sub_format);
    void Sub_langs(const std::string &sub_langs);
    void Embed_subs(bool embed_subs);
    void Convert_subs(const std::string &convert_subs);
    void Transcription(bool transcription);
    void Proxy(const std::string &proxy);
    void Exec_after(const std::string &exec_after);
    void Exec_before(const std::string &exec_before);
    void Urls(const std::set<std::string> &urls);
    void Test(bool test);

private:
    std::shared_ptr<dtv::FsDir> _output;
    bool _no_overwrites{false};
    bool _write_description{false};
    bool _quiet{false};
    bool _progress{false};
    int _height{1080};
    std::string _extension;
    std::string _merge_output_extension;
    bool _saving_original_video_resolution{false};
    bool _yes_playlist{false};
    int _fps{30};
    std::string _translate_from_lang;
    std::string _translate_to_lang;
    bool _no_translate{false};
    bool _only_translate{false};
    fs::path _replace_audio;
    fs::path _replace_translate;
    double _vol_audio{0.25};
    double _vol_translate{1.};
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
