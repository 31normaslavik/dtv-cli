#include "formater.h"

#include <map>

namespace dtv {

Formater::Formater(Video const& video, CommandLine const& line): _video{video}, _line{line}
{
}

std::any Formater::GetFormat(const FORMAT eformat) const
{
    const int64_t closest = findClosest(_line.Height());

    std::map<std::string, Format> _mvideo;
    std::map<std::string, Format> _maudio;

    for(Format const& format: _video.formats){
        if (format.height == closest && format.video_ext != "none"){
            if(eformat == FORMAT::FirstClosestVideo)
                return format;

            if(_mvideo.contains(format.video_ext) && _mvideo[format.video_ext].size < format.size){
                _mvideo[format.video_ext] = format;
            }else
                _mvideo[format.video_ext] = format;
            continue;
        }

        if(format.resolution == "audio only"){            
            if(eformat == FORMAT::FirstClosestAudio)
                return format;

            if(_maudio.contains(format.audio_ext) && _maudio[format.audio_ext].size < format.size){
                _maudio[format.audio_ext] = format;
            }else
                _maudio[format.audio_ext] = format;
            continue;
        }
    }

    std::string extv, exta, format_id;
    if(_mvideo.contains(_line.Extension())){
        format_id = _mvideo.at(_line.Extension()).format_id;
        extv = _line.Extension();
    }
    else {
        _line.Extension() == "mp4" ? extv = "webm" : extv = "mp4";
        if(_mvideo.contains(extv))
            format_id = _mvideo.at(extv).format_id;
        else
            throw std::runtime_error("Extensions [" + _line.Extension() + " " + extv + "] not conteined in source");
    }

    extv == "mp4" ? exta = "m4a" : exta = "webm";

    if(_maudio.contains(exta)){
        format_id += "+" + _maudio.at(exta).format_id;
    }
    return format_id;
}

int64_t Formater::findClosest(int64_t target) const
{
    if (target <= _video.formats.begin()->height)
        return _video.formats.begin()->height;

    if (target >= _video.formats.rbegin()->height)
        return _video.formats.rbegin()->height;

    size_t i = 0, j = _video.formats.size(), mid = 0;

    while (i < j) {
        mid = (i + j) / 2;
        if (_video.formats[mid].height == target)
            return _video.formats[mid].height;

        if (target < _video.formats[mid].height) {
            if (mid > 0 && target > _video.formats[mid - 1].height)
                return getClosest(_video.formats[mid - 1].height, _video.formats[mid].height, target);
            j = mid;
        }
        else {
            if (mid < _video.formats.size() - 1 && target < _video.formats[mid + 1].height)
                return getClosest(_video.formats[mid].height, _video.formats[mid + 1].height, target);
            i = mid + 1;
        }
    }
    return _video.formats[mid].height;
}

int64_t dtv::Formater::getClosest(int64_t val1, int64_t val2, int64_t target) const
{
    if (target - val1 >= val2 - target)
        return val2;
    else
        return val1;
}

} // namespace dtv
