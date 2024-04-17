#include "commandline.h"
#include <regex>

dtv::CommandLine::CommandLine(const std::vector<std::string> &urls,
                              const std::filesystem::path &path_to_save,
                              const std::string &format):
    path_to_save_{path_to_save},
    format_{format}

// TODO заменить на boost::url
{
    for(const auto& url: urls){
        for(const auto& res : resources){
            std::string regex = R"(^(http(s?)\://)(www\.|m\.|player\.|my\.|proxitok\.|inv\.)?()" + res + R"()+\.(com|edu|gov|m+il|net|org|biz|info|name|museum|us|ca|uk|tv|ru|be|es|video|cc)(\:[0-9]+)*(/($|[a-zA-Z0-9\.+\,\;\?\'\\\+\&amp;%\$#\=~_\-]+))*$)";
                std::regex e(regex);
                if(std::regex_match(url, e)){
                    urls_.emplace_back(url);
                }
        }
    }
}

std::filesystem::path dtv::CommandLine::Path() const
{
    return path_to_save_;
}

std::string dtv::CommandLine::Format() const
{
    return format_;
}

std::vector<std::string> dtv::CommandLine::Urls() const
{
    return urls_;
}

