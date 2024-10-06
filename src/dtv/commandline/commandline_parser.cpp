#include "commandline_parser.h"
#include "debug.h"
#include "helper.h"
#include "version.h"
#include <boost/program_options.hpp>
#include <boost/url.hpp>

dtv::CommandLine dtv::command_line_parser(std::vector<std::string> const &arguments) {
    namespace fs = std::filesystem;
    namespace opt = boost::program_options;

    const unsigned short line_length = 150;
    opt::options_description all;
    opt::options_description general("General");
    opt::options_description filesystem("Filesystem");
    opt::options_description verbosity("Verbosity");
    opt::options_description video("Video", line_length);
    opt::options_description audio("Audio", line_length);
    opt::options_description subtitle("Subtitle");
    opt::options_description network("Network");
    opt::options_description processing("Pre/Post-Processing", line_length);
    opt::options_description hide("Hide");
    opt::options_description debug("Debug", line_length);
    opt::options_description visible("Options");

    CommandLine line;

    general.add_options()
        ("help,h", "This help")
        ("version,v", "Version dtv-cli")
        // ("update,U","")
        ("code-country", "Code countries")
        ("examples", "Examples")
        ;

    filesystem.add_options()
        ("output,o",
         opt::value<std::string>()->default_value(fs::current_path()),
         "Path to save")
        ("no-overwrites", "Do not overwrite exist files")
        // ("write-description","")
        ("temp-dir", opt::value<std::string>(), "Changing temporary path")
        ;

    verbosity.add_options()
        // ("quiet", "")
        // ("progress", "")
        ;

    video.add_options()
        ("height,H",
         opt::value<int>(),
         "[4320 2160 1440 1080 720 480 360]\n"
         "The resolution of the downloaded video")
        ("extension,e", opt::value<std::string>()->default_value("mp4"),
         "[mp4 webm]. If the selected container is not contained on the resource from which the download is being made, "
                      "then the available one will be selected. If desired, with the \"--merge-output-extension\" key, "
                      "you can force the desired container to be selected")

        ("merge-output-extension", opt::value<std::string>(), "Select the final file extension. For example [mp3 flac webm aac mkv, etc.]")
        // ("saving-original-video-resolution","")
        ("yes-playlist", "Download the playlist, if the URL refers to a video and a playlist")
        ("fps", opt::value<int>(), "Preferred fps video")
        ;

    audio.add_options()
        ("translate-from-lang,l", opt::value<std::string>()->default_value("en"),"The original language. The language must match the real one in the video!!!")
        ("translate-to-lang,L", opt::value<std::string>()->default_value("ru"),"The language to be translated into")
        ("no-translate,t", "Don't translate videos and simply download video")
        ("only-translate,T", "Save only the audio translation")
        ("replace-audio", opt::value<std::string>(),"Replace the audio in the video with your own")
        ("replace-translate", opt::value<std::string>(),"Replace the audio-to-video translation with your own")
        ("vol-audio", opt::value<int>(),"The sound level of the original audio")
        ("vol-translate", opt::value<int>(),"Audio translation sound level")
        ("save-translation","Create a video with a translation and a separate translation next to the video")
        ("save-translation-no-merge","Create a video without translation and a separate translation (without merging files)")
        ("save-translation-contaner", opt::value<std::string>(),"Translation file container [mkv mp4 aac flac, etc.] (default mp3)")
        ;

    subtitle.add_options()
        ("write-subs,s","Download subtitles")
        ("sub-lang,S", opt::value<std::string>()->default_value("ru"),"Subtitles language")
        // ("write-auto-subs","")
        // ("list-subs","")
        // ("sub-format", opt::value<std::string>()->default_value("srt"),"")
        ("sub-langs", "Subtitles langs")
        // ("embed-subs","")
        // ("convert-subs","")
        // ("transcription","")
        // ("no-merge-subs", "")
        ;

    network.add_options()
        // ("proxy","")
        ;

    processing.add_options()
        ("exec-after","Execute a command after download videos")
        ("exec-before","Execute a command before download videos")
        ;

    hide.add_options()
        ("urls,u",
         opt::value<std::vector<std::string>>(),
         "The link(s) of the source from where you want to download "
         "the video. Playlists are also supported")
        ;

    debug.add_options()
        ("debug","Debug")
        // ("test","Test mode. Video length limit of 10 seconds")
        ;

    all.add(general).add(filesystem).add(verbosity).add(video).add(audio).add(subtitle).add(network).add(processing).add(hide).add(debug);
    visible.add(general).add(filesystem).add(verbosity).add(video).add(audio).add(subtitle).add(network).add(processing).add(debug);

    opt::positional_options_description positional;
    positional.add("urls", -1);

    opt::variables_map _vm;
    opt::store(opt::command_line_parser(arguments).options(all).positional(positional).run(), _vm);
    opt::notify(_vm);

    /**
     * GENERAL
     */
    if (_vm.contains("help")) {
        std::cout << visible << "\n";
        exit(EXIT_SUCCESS);
    }
    if (_vm.contains("version")) {
        std::cout << getName() << " " << getVersion() << "\n";
        exit(EXIT_SUCCESS);
    }
    if (_vm.contains("update")) {
        exit(EXIT_SUCCESS);
    }
    if (_vm.contains("code-country")) {
        std::cout << Helper::codes_country << "\n";
        exit(EXIT_SUCCESS);
    }

    if (_vm.contains("examples")) {
        std::cout << Helper::exampes << "\n";
        exit(EXIT_SUCCESS);
    }

    /*
     * FILESYSTEM
     */
    if (_vm.contains("output")) {
        fs::path const &output = _vm["output"].as<std::string>();
        line.Output(output);
    }
    if (_vm.contains("no-overwrites")) {
        line.No_overwrites(true);
    }
    if (_vm.contains("write-description")) {
        line.Write_description(true);
    }
    if (_vm.contains("temp-dir")) {
        fs::path const &temp_dir_path = _vm["temp-dir"].as<std::string>();
        line.Output(temp_dir_path);
    }

    /*
     * VERBOSITY
     */
    if (_vm.contains("quiet")) {
        line.Quiet(true);
    }
    if (_vm.contains("progress")) {
        line.Progress(true);
    }

    /*
     * VIDEO
     */
    if (_vm.contains("height")) {
        int const height = _vm["height"].as<int>();

        if (height < 0 || height > 5000) {
            std::cerr << "The video resolution is incorrectly specified\n";
            std::cout << Helper::exampes << "\n";
            exit(EXIT_FAILURE);
        }
        line.Height(height);
    }
    if (_vm.contains("extension")) {
        auto const &extension = _vm["extension"].as<std::string>();
        line.Extension(extension);
    }
    if (_vm.contains("merge-output-extension")) {
        auto const &merge_output_extension =
            _vm["merge-output-extension"].as<std::string>();
        line.Merge_output_extension(merge_output_extension);
    }
    if (_vm.contains("saving-original-video-resolution")) {
        line.Saving_original_video_resolution(true);
    }
    if (_vm.contains("yes-playlist")) {
        line.YesPlaylist(true);
    }
    if (_vm.contains("fps")) {
        int fps = _vm["fps"].as<int>();
        if(fps > 15) {
            line.Fps(fps);
        }
    }

    /*
     * AUDIO
     */
    if (_vm.contains("translate-from-lang")) {
        auto const &translate_from_lang =
            _vm["translate-from-lang"].as<std::string>();
        line.Translate_from_lang(translate_from_lang);
    }
    if (_vm.contains("translate-to-lang")) {
        auto const &translate_to_lang =
            _vm["translate-to-lang"].as<std::string>();
        line.Translate_to_lang(translate_to_lang);
    }
    if (_vm.contains("no-translate")) {
        line.No_translate(true);
    }
    if (_vm.contains("only-translate")) {
        line.Only_translate(true);
    }
    if (_vm.contains("replace-audio")) {
        fs::path const &replace_audio = _vm["replace-audio"].as<std::string>();
        line.Replace_audio(replace_audio);
    }
    if (_vm.contains("replace-translate")) {
        fs::path const &replace_translate =
            _vm["replace-translate"].as<std::string>();
        line.Replace_translate(replace_translate);
    }
    if (_vm.contains("vol-audio")) {
        int const vol_audio = _vm["vol-audio"].as<int>();
        line.Vol_audio(vol_audio / 100.);
    }
    if (_vm.contains("vol-translate")) {
        int const vol_translate = _vm["vol-translate"].as<int>();
        line.Vol_translate(vol_translate / 100.);
    }
    if (_vm.contains("save-translation")) {
        if(line.WithoutTranslation()) {
            std::cout << "The --save-translation and --no-translate flags cannot be used together. "
                         "The --save-translation flag will be ignored\n";
        } else {
            line.Save_translation(true);
        }
    }
    if (_vm.contains("save-translation-no-merge")) {
        if(line.WithoutTranslation()) {
            std::cout << "The --save-translation-no-merge and --no-translate flags cannot be used together. "
                         "The --save-translation-no-merge flag will be ignored\n";
        } else {
            line.Save_translation_no_merge(true);
        }
    }
    if (_vm.contains("save-translation-contaner")) {
        auto const &save_translation_contaner =
            _vm["save-translation-contaner"].as<std::string>();
        line.Save_translation_contaner(save_translation_contaner);
    }

    /**
     * SUBTITLES
     */
    if (_vm.contains("write-subs")) {
        line.Write_subs(true);
    }
    if (_vm.contains("sub-lang")) {
        auto const &sub_lang = _vm["sub-lang"].as<std::string>();
        line.Sub_lang(sub_lang);
    }
    if (_vm.contains("write-auto-subs")) {
        line.Write_auto_subs(true);
    }
    if (_vm.contains("sub-format")) {
        auto const &sub_format = _vm["sub-format"].as<std::string>();
        line.Sub_format(sub_format);
    }
    if (_vm.contains("sub-langs")) {
        std::cout << Helper::subtitles_langs << "\n";
    }
    if (_vm.contains("embed-subs")) {
        line.Embed_subs(true);
    }
    if (_vm.contains("convert-subs")) {
        auto const &convert_subs = _vm["convert-subs"].as<std::string>();
        line.Convert_subs(convert_subs);
    }
    if (_vm.contains("transcription")) {
        line.Transcription(true);
    }

    /*
     * NETWORK
     */
    if (_vm.contains("proxy")) {
        auto const &proxy = _vm["proxy"].as<std::string>();
        line.Proxy(proxy);
    }

    /*
     * PROCESSING
     */
    if (_vm.contains("exec-after")) {
        auto const &exec_after = _vm["exec-after"].as<std::string>();
        line.Exec_after(exec_after);
    }
    if (_vm.contains("exec-before")) {
        auto const &exec_before = _vm["exec-before"].as<std::string>();
        line.Exec_before(exec_before);
    }

    /*
     * HIDE
     */
    if (_vm.contains("urls")) {
        auto const &urls = _vm["urls"].as<std::vector<std::string>>();

        std::set<std::string> urls_s;

        for (const auto &url : urls) {
            boost::system::result<boost::urls::url_view> result_url =
                boost::urls::parse_uri(url);

            if (result_url.has_value()) {
                urls_s.insert(result_url.value().buffer());
            } else {
                std::cerr << "The link to the video is incorrect: "
                          << result_url.value() << " [" << result_url.error() << "]\n";
                continue;
            }
        }
        line.Urls(urls_s);

    } else {
        std::cout << Helper::exampes << "\n";
        exit(EXIT_FAILURE);
    }

    /*
     * DEBUG
     */
    if (_vm.contains("debug")) {
        Debug::debug = true;
    }
    if (_vm.contains("test")) {
        line.Test(true);
    }
    return line;
}



