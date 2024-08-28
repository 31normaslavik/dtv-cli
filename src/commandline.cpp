#include "commandline.h"

namespace dtv{

CommandLine::CommandLine(){
}

std::shared_ptr<FsDirectories> CommandLine::Output() const
{
    if(_output == nullptr)
        throw std::runtime_error("Output not inicialized!!!");
    return _output;
}

void CommandLine::Output(const fs::path &output)
{
    if(!_output)
        _output = std::make_shared<FsDirectories>(output);
    else{
        _output->ChangeTempPath(output);
    }
}

bool CommandLine::No_overwrites() const
{
    return _no_overwrites;
}

void CommandLine::No_overwrites(bool no_overwrites)
{
    _no_overwrites = no_overwrites;
}

bool CommandLine::Write_description() const
{
    return _write_description;
}

void CommandLine::Write_description(bool Write_description)
{
    _write_description = Write_description;
}

// fs::path CommandLine::Temp_dir() const
// {
//     return _temp_dir;
// }

void CommandLine::Temp_dir(const fs::path &temp_dir)
{
    if(!_output)
        throw std::runtime_error("FsDirectories not initialized!");
    _output->ChangeTempPath(temp_dir);
}

bool CommandLine::Quiet() const
{
    return _quiet;
}

void CommandLine::Quiet(bool Quiet)
{
    _quiet = Quiet;
}

bool CommandLine::Progress() const
{
    return _progress;
}

void CommandLine::Progress(bool Progress)
{
    _progress = Progress;
}

int CommandLine::Height() const
{
    return _height;
}

void CommandLine::Height(int Height)
{
    _height = Height;
}

std::string CommandLine::Extension() const
{
    return _extension;
}

void CommandLine::Extension(const std::string &Extension)
{
    _extension = Extension;
}

std::string CommandLine::Merge_output_extension() const
{
    return _merge_output_extension;
}

void CommandLine::Merge_output_extension(const std::string &Merge_output_extension)
{
    _merge_output_extension = Merge_output_extension;
}

bool CommandLine::Saving_original_video_resolution() const
{
    return _saving_original_video_resolution;
}

void CommandLine::Saving_original_video_resolution(bool Saving_original_video_resolution)
{
    _saving_original_video_resolution = Saving_original_video_resolution;
}

bool CommandLine::YesPlaylist() const
{
    return _yesPlaylist;
}

void CommandLine::YesPlaylist(bool yesPlaylist)
{
    _yesPlaylist = yesPlaylist;
}

std::string CommandLine::Translate_from_lang() const
{
    return _translate_from_lang;
}

void CommandLine::Translate_from_lang(const std::string &Translate_from_lang)
{
    _translate_from_lang = Translate_from_lang;
}

std::string CommandLine::Translate_to_lang() const
{
    return _translate_to_lang;
}

void CommandLine::Translate_to_lang(const std::string &Translate_to_lang)
{
    _translate_to_lang = Translate_to_lang;
}

bool CommandLine::No_translate() const
{
    return _no_translate;
}

void CommandLine::No_translate(bool No_translate)
{
    _no_translate = No_translate;
}

bool CommandLine::Only_translate() const
{
    return _only_translate;
}

void CommandLine::Only_translate(bool Only_translate)
{
    _only_translate = Only_translate;
}

fs::path CommandLine::Replace_audio() const
{
    return _replace_audio;
}

void CommandLine::Replace_audio(const fs::path &Replace_audio)
{
    _replace_audio = Replace_audio;
}

fs::path CommandLine::Replace_translate() const
{
    return _replace_translate;
}

void CommandLine::Replace_translate(const fs::path &Replace_translate)
{
    _replace_translate = Replace_translate;
}

double CommandLine::Vol_audio() const
{
    return _vol_audio;
}

void CommandLine::Vol_audio(double Vol_audio)
{
    _vol_audio = Vol_audio;
}

double CommandLine::Vol_translate() const
{
    return _vol_translate;
}

void CommandLine::Vol_translate(double Vol_translate)
{
    _vol_translate = Vol_translate;
}

bool CommandLine::Save_translation() const
{
    return _save_translation;
}

void CommandLine::Save_translation(bool Save_translation)
{
    _save_translation = Save_translation;
}

bool CommandLine::Save_translation_no_merge() const
{
    return _save_translation_no_merge;
}

void CommandLine::Save_translation_no_merge(bool Save_translation_no_merge)
{
    _save_translation_no_merge = Save_translation_no_merge;
}

std::string CommandLine::Save_translation_contaner() const
{
    return _save_translation_contaner;
}

void CommandLine::Save_translation_contaner(const std::string &Save_translation_contaner)
{
    _save_translation_contaner = Save_translation_contaner;
}

bool CommandLine::Write_subs() const
{
    return _write_subs;
}

void CommandLine::Write_subs(bool Write_subs)
{
    _write_subs = Write_subs;
}

std::string CommandLine::Sub_lang() const
{
    return _sub_lang;
}

void CommandLine::Sub_lang(const std::string &Sub_lang)
{
    _sub_lang = Sub_lang;
}

bool CommandLine::Write_auto_subs() const
{
    return _write_auto_subs;
}

void CommandLine::Write_auto_subs(bool Write_auto_subs)
{
    _write_auto_subs = Write_auto_subs;
}

std::string CommandLine::Sub_format() const
{
    return _sub_format;
}

void CommandLine::Sub_format(const std::string &Sub_format)
{
    _sub_format = Sub_format;
}

std::string CommandLine::Sub_langs() const
{
    return _sub_langs;
}

void CommandLine::Sub_langs(const std::string &Sub_langs)
{
    _sub_langs = Sub_langs;
}

bool CommandLine::Embed_subs() const
{
    return _embed_subs;
}

void CommandLine::Embed_subs(bool Embed_subs)
{
    _embed_subs = Embed_subs;
}

std::string CommandLine::Convert_subs() const
{
    return _convert_subs;
}

void CommandLine::Convert_subs(const std::string &Convert_subs)
{
    _convert_subs = Convert_subs;
}

bool CommandLine::Transcription() const
{
    return _transcription;
}

void CommandLine::Transcription(bool Transcription)
{
    _transcription = Transcription;
}

std::string CommandLine::Proxy() const
{
    return _proxy;
}

void CommandLine::Proxy(const std::string &Proxy)
{
    _proxy = Proxy;
}

std::string CommandLine::Exec_after() const
{
    return _exec_after;
}

void CommandLine::Exec_after(const std::string &Exec_after)
{
    _exec_after = Exec_after;
}

std::string CommandLine::Exec_before() const
{
    return _exec_before;
}

void CommandLine::Exec_before(const std::string &Exec_before)
{
    _exec_before = Exec_before;
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

void CommandLine::Test(bool Test)
{
    _test = Test;
}

} // namespace dtv

