#include "../command/commandline.h"
#include "../presentation/presentation.h"
#include <regex>

dtv::CommandLine::CommandLine(const std::vector<std::string> &urls,
                              const std::filesystem::path &pathToSave,
                              const std::string &format):
    path_to_save_{pathToSave}

{
    for(const auto& url: urls){
        for(const auto& res : resources){
            std::string regex = R"(^(http(s?)\://)(www\.|m\.|player\.|my\.|proxitok\.|inv\.)?()" + res + R"()+\.(com|edu|gov|m+il|net|org|biz|info|name|museum|us|ca|uk|tv|ru|be|es|video|cc)(\:[0-9]+)*(/($|[a-zA-Z0-9\.+\,\;\?\'\\\+\&amp;%\$#\=~_\-]+))*$)";
                std::regex e(regex);
                //std::string str = url;
                if(std::regex_match(url, e)){
                    std::string frmt = Format::combinate_format(Format::format_video_argv(format,res));
                    resources_list_.emplace(Source(res, url, frmt));
                }

        }
    }

    //_format = Format::combinate_format(Format::format_video_argv(format))

}

std::filesystem::path dtv::CommandLine::Path() const
{
    return path_to_save_;
}

// std::string dtv::CommandLine::getFormat()
// {
//     return std::move(_format);
// }

std::set<dtv::Source,dtv::cmpSource> dtv::CommandLine::Resources() const
{
    return std::move(resources_list_);
}

dtv::Source::Source(const std::string &resource, const std::string &url, const std::string& format):
    resource_{resource},
    url_{url},
    format_{format}
{
}
