#include "commandline.h"

namespace dtv{

std::shared_ptr<FsDir> CommandLine::Output() const
{
    if(_output == nullptr) {
        throw std::runtime_error("Output not inicialized!!!");
    }
    return _output;
}

void CommandLine::Output(const fs::path &output)
{
    if(!_output) {
        _output = std::make_shared<FsDir>(output);
    } else{
        _output->ChangeTempPath(output);
    }
}

bool CommandLine::NoOverwrites() const
{
    return _no_overwrites;
}

void CommandLine::No_overwrites(bool no_overwrites)
{
    _no_overwrites = no_overwrites;
}

bool CommandLine::WriteDescription() const
{
    return _write_description;
}

void CommandLine::Write_description(bool write_description)
{
    _write_description = write_description;
}

void CommandLine::Temp_dir(const fs::path &temp_dir)
{
    if(!_output) {
        throw std::runtime_error("FsDirectories not initialized!");
    }
    _output->ChangeTempPath(temp_dir);
}

bool CommandLine::Quiet() const
{
    return _quiet;
}

void CommandLine::Quiet(bool quiet)
{
    _quiet = quiet;
}

bool CommandLine::Progress() const
{
    return _progress;
}

void CommandLine::Progress(bool progress)
{
    _progress = progress;
}

int CommandLine::Height() const
{
    return _height;
}

void CommandLine::Height(int height)
{
    _height = height;
}

std::string CommandLine::Extension() const
{
    return _extension;
}

void CommandLine::Extension(const std::string &extension)
{
    _extension = extension;
}

std::string CommandLine::MergeOutputExtension() const
{
    return _merge_output_extension;
}

void CommandLine::Merge_output_extension(const std::string &merge_output_extension)
{
    _merge_output_extension = merge_output_extension;
}

bool CommandLine::SavingOriginalVideoResolution() const
{
    return _saving_original_video_resolution;
}

void CommandLine::Saving_original_video_resolution(bool saving_original_video_resolution)
{
    _saving_original_video_resolution = saving_original_video_resolution;
}

bool CommandLine::YesPlaylist() const
{
    return _yes_playlist;
}

int CommandLine::Fps() const
{
    return _fps;
}

void CommandLine::YesPlaylist(bool yes_playlist)
{
    _yes_playlist = yes_playlist;
}

void CommandLine::Fps(int fps)
{
    _fps = fps;
}

std::string CommandLine::TranslateFromLang() const
{
    return _translate_from_lang;
}

void CommandLine::Translate_from_lang(const std::string &translate_from_lang)
{
    _translate_from_lang = translate_from_lang;
}

std::string CommandLine::TranslateToLang() const
{
    return _translate_to_lang;
}

void CommandLine::Translate_to_lang(const std::string &translate_to_lang)
{
    _translate_to_lang = translate_to_lang;
}

bool CommandLine::WithoutTranslation() const
{
    return _no_translate;
}

void CommandLine::No_translate(bool no_translate)
{
    _no_translate = no_translate;
}

bool CommandLine::TranslationOnly() const
{
    return _only_translate;
}

void CommandLine::Only_translate(bool only_translate)
{
    _only_translate = only_translate;
}

fs::path CommandLine::ReplaceSound() const
{
    return _replace_audio;
}

void CommandLine::Replace_audio(const fs::path &replace_audio)
{
    _replace_audio = replace_audio;
}

fs::path CommandLine::ReplaceTranslate() const
{
    return _replace_translate;
}

void CommandLine::Replace_translate(const fs::path &replace_translate)
{
    _replace_translate = replace_translate;
}

double CommandLine::Vol_audio() const
{
    return _vol_audio;
}

void CommandLine::Vol_audio(double vol_audio)
{
    _vol_audio = vol_audio;
}

double CommandLine::Vol_translate() const
{
    return _vol_translate;
}

void CommandLine::Vol_translate(double vol_translate)
{
    _vol_translate = vol_translate;
}

bool CommandLine::Save_translation() const
{
    return _save_translation;
}

void CommandLine::Save_translation(bool save_translation)
{
    _save_translation = save_translation;
}

bool CommandLine::Save_translation_no_merge() const
{
    return _save_translation_no_merge;
}

void CommandLine::Save_translation_no_merge(bool save_translation_no_merge)
{
    _save_translation_no_merge = save_translation_no_merge;
}

std::string CommandLine::Save_translation_contaner() const
{
    return _save_translation_contaner;
}

void CommandLine::Save_translation_contaner(const std::string &save_translation_contaner)
{
    _save_translation_contaner = save_translation_contaner;
}

bool CommandLine::Write_subs() const
{
    return _write_subs;
}

void CommandLine::Write_subs(bool write_subs)
{
    _write_subs = write_subs;
}

std::string CommandLine::Sub_lang() const
{
    return _sub_lang;
}

void CommandLine::Sub_lang(const std::string &sub_lang)
{
    _sub_lang = sub_lang;
}

bool CommandLine::Write_auto_subs() const
{
    return _write_auto_subs;
}

void CommandLine::Write_auto_subs(bool write_auto_subs)
{
    _write_auto_subs = write_auto_subs;
}

std::string CommandLine::Sub_format() const
{
    return _sub_format;
}

void CommandLine::Sub_format(const std::string &sub_format)
{
    _sub_format = sub_format;
}

std::string CommandLine::Sub_langs() const
{
    return _sub_langs;
}

void CommandLine::Sub_langs(const std::string &sub_langs)
{
    _sub_langs = sub_langs;
}

bool CommandLine::Embed_subs() const
{
    return _embed_subs;
}

void CommandLine::Embed_subs(bool embed_subs)
{
    _embed_subs = embed_subs;
}

std::string CommandLine::Convert_subs() const
{
    return _convert_subs;
}

void CommandLine::Convert_subs(const std::string &convert_subs)
{
    _convert_subs = convert_subs;
}

bool CommandLine::Transcription() const
{
    return _transcription;
}

void CommandLine::Transcription(bool transcription)
{
    _transcription = transcription;
}

std::string CommandLine::Proxy() const
{
    return _proxy;
}

void CommandLine::Proxy(const std::string &proxy)
{
    _proxy = proxy;
}

std::string CommandLine::Exec_after() const
{
    return _exec_after;
}

void CommandLine::Exec_after(const std::string &exec_after)
{
    _exec_after = exec_after;
}

std::string CommandLine::Exec_before() const
{
    return _exec_before;
}

void CommandLine::Exec_before(const std::string &exec_before)
{
    _exec_before = exec_before;
}

std::set<std::string> CommandLine::Urls() const
{
    return _urls;
}

void CommandLine::Urls(const std::set<std::string> &urls)
{
    _urls = urls;
}

bool CommandLine::Test() const
{
    return _test;
}

void CommandLine::Test(bool test)
{
    _test = test;
}

} // namespace dtv
