#include "command_line_parser.h"
#include "helper.h"
#include <boost/url.hpp>

const dtv::CommandLine dtv::command_line_parser(int argc, char *argv[]) {
    namespace fs = std::filesystem;
    namespace opt = boost::program_options;

    opt::options_description all;
    opt::options_description general("General");
    opt::options_description filesystem("Filesystem");
    opt::options_description verbosity("Verbosity");
    opt::options_description video("Video");
    opt::options_description audio("Audio");
    opt::options_description subtitle("Subtitle");
    opt::options_description network("Network");
    opt::options_description processing("Pre/Post-Processing");
    opt::options_description hide("Hide");
    opt::options_description debug("Debug");
    opt::options_description visible("Options");

    CommandLine line;

    general.add_options()
        ("help,h", "This help\n")
        ("version,v","")
        ("update,U","")
        ("code-country","")
        ("examples","")
        ;

    filesystem.add_options()
        ("output,o",
         opt::value<fs::path>()->default_value(
             fs::current_path()),
         "The path where the video will be saved. "
         "By default, it will be saved in the directory from which the program is "
         "launched\n")
        ("force-overwrites","")
        ("write-description","")
        ("temp_dir","")
        ;

    verbosity.add_options()
        ("quiet","")
        ("progress","")
        ;

    video.add_options()
        ("height,H",
         opt::value<std::string>()->default_value("1080"),
         "Available options: [4320 2160 1440 1080 720 480 360]\n"
         "The resolution of the downloaded video.\n"
         "If there is no video in this format, then the best quality with a lower "
         "resolution will be downloaded: 1080p -> 720p -> 480p, etc\n")
        ("extension,e", opt::value<std::string>()->default_value("mp4"),
         "[mp4 webm]\n")

        ("merge-output-extension","")
        ("saving-original-video-resolution","")
        ("playlist","")
        ;

    audio.add_options()
        ("translate-from-lang","")
        ("translate-to-lang","")
        ("no-translate","")
        ("only-translate","")
        ("replace-audio","")
        ("replace-translate","")
        ("vol-audio","25")
        ("vol-translate","100")
        ("save-translation","")
        ("save-translation-no-merge","")
        ("save-translation-contaner","")
        ;

    subtitle.add_options()
        ("write-subs","")
        ("sub-lang","")
        ("write-auto-subs","")
        ("list-subs","")
        ("sub-format","")
        ("sub-langs","")
        ("embed-subs","")
        ("convert-subs","")
        ("transcription","")
        ;

    network.add_options()
        ("proxy","")
        ;

    processing.add_options()
        ("exec-after","")
        ("exec-before","")
        ;

    hide.add_options()
        ("urls,u",
         opt::value<std::vector<std::string>>(),
         "The link(s) of the source from where you want to download "
         "the video. Playlists are also supported")
        ;

    debug.add_options()
        ("debug","")
        ("test","")
        ;

    all.add(general).add(filesystem).add(verbosity).add(video).add(audio).add(subtitle).add(network).add(processing).add(hide).add(debug);
    visible.add(general).add(filesystem).add(verbosity).add(video).add(audio).add(subtitle).add(network).add(processing).add(debug);

    opt::positional_options_description p;
    p.add("urls", -1);

    opt::variables_map vm;
    opt::store(opt::command_line_parser(argc, argv).options(all).positional(p).run(), vm);
    opt::notify(vm);

    if (vm.count("help")) {
        std::cout << visible << std::endl;
        exit(EXIT_SUCCESS);
    }
    if (vm.count("version")) {
        exit(EXIT_SUCCESS);
    }
    if (vm.count("update")) {
        exit(EXIT_SUCCESS);
    }
    if (vm.count("code-country")) {
        exit(EXIT_SUCCESS);
    }

    if (vm.count("examples")) {
        std::cout << Helper::exampes << std::endl;
        exit(EXIT_SUCCESS);
    }

    if (vm.count("output")) {
        fs::path const &output = vm["output"].as<fs::path>();
        line.Output(output);
    }
    if (vm.count("force-overwrites")) {
        bool const force_overwrites = vm["force-overwrites"].as<bool>();
        line.Force_overwrites(force_overwrites);
    }
    if (vm.count("write-description")) {
        bool const &write_description = vm["write-description"].as<bool>();
        line.Write_description(write_description);
    }
    if (vm.count("temp_dir")) {
        fs::path const &temp_dir_path = vm["temp_dir"].as<fs::path>();
        line.Temp_dir(temp_dir_path);
    }
    if (vm.count("quiet")) {
        bool const &quiet = vm["quiet"].as<bool>();
        line.Quiet(quiet);
    }
    if (vm.count("progress")) {
        bool const &progress = vm["progress"].as<bool>();
        line.Progress(progress);
    }
    if (vm.count("height")) {
        int const height = vm["height"].as<int>();

        if (height < 0 || height > 5000) {
            std::cerr << "The video resolution is incorrectly specified"
                      << std::endl;
            std::cout << Helper::exampes << std::endl;
            exit(EXIT_FAILURE);
        }
        line.Height(height);
    }
    if (vm.count("extension")) {
        std::string const &extension = vm["extension"].as<std::string>();
        line.Extension(extension);
    }
    if (vm.count("merge-output-extension")) {
        std::string const &merge_output_extension =
            vm["merge-output-extension"].as<std::string>();
        line.Merge_output_extension(merge_output_extension);
    }
    if (vm.count("saving-original-video-resolution")) {
        bool const &saving_original_video_resolution =
            vm["saving-original-video-resolution"].as<bool>();
        line.Saving_original_video_resolution(saving_original_video_resolution);
    }
    if (vm.count("playlist")) {
        bool const &playlist = vm["playlist"].as<bool>();
        line.Playlist(playlist);
    }
    if (vm.count("translate-from-lang")) {
        std::string const &translate_from_lang =
            vm["translate-from-lang"].as<std::string>();
        line.Translate_from_lang(translate_from_lang);
    }
    if (vm.count("translate-to-lang")) {
        std::string const &translate_to_lang =
            vm["translate-to-lang"].as<std::string>();
        line.Translate_to_lang(translate_to_lang);
    }
    if (vm.count("no-translate")) {
        bool const &no_translate = vm["no-translate"].as<bool>();
        line.No_translate(no_translate);
    }
    if (vm.count("only-translate")) {
        bool const &only_translate = vm["only-translate"].as<bool>();
        line.Only_translate(only_translate);
    }
    if (vm.count("replace-audio")) {
        fs::path const &replace_audio = vm["replace-audio"].as<fs::path>();
        line.Replace_audio(replace_audio);
    }
    if (vm.count("replace-translate")) {
        fs::path const &replace_translate =
            vm["replace-translate"].as<fs::path>();
        line.Replace_translate(replace_translate);
    }
    if (vm.count("vol-audio")) {
        int const &vol_audio = vm["vol-audio"].as<int>();
        line.Vol_audio(vol_audio);
    }
    if (vm.count("vol-translate")) {
        int const &vol_translate = vm["vol-translate"].as<int>();
        line.Vol_translate(vol_translate);
    }
    if (vm.count("save-translation")) {
        bool const &save_translation = vm["save-translation"].as<bool>();
        line.Save_translation(save_translation);
    }
    if (vm.count("save-translation-no-merge")) {
        bool const &save_translation_no_merge =
            vm["save-translation-no-merge"].as<bool>();
        line.Save_translation_no_merge(save_translation_no_merge);
    }
    if (vm.count("save-translation-contaner")) {
        std::string const &save_translation_contaner =
            vm["save-translation-contaner"].as<std::string>();
        line.Save_translation_contaner(save_translation_contaner);
    }
    if (vm.count("write-subs")) {
        bool const &write_subs = vm["write-subs"].as<bool>();
        line.Write_subs(write_subs);
    }
    if (vm.count("sub-lang")) {
        std::string const &sub_lang = vm["sub-lang"].as<std::string>();
        line.Sub_lang(sub_lang);
    }
    if (vm.count("write-auto-subs")) {
        bool const &write_auto_subs = vm["write-auto-subs"].as<bool>();
        line.Write_auto_subs(write_auto_subs);
    }
    if (vm.count("sub-format")) {
        std::string const &sub_format = vm["sub-format"].as<std::string>();
        line.Sub_format(sub_format);
    }
    if (vm.count("sub-langs")) {
        std::string const &sub_langs = vm["sub-langs"].as<std::string>();
        line.Sub_langs(sub_langs);
    }
    if (vm.count("embed-subs")) {
        bool const &embed_subs = vm["embed-subs"].as<bool>();
        line.Embed_subs(embed_subs);
    }
    if (vm.count("convert-subs")) {
        std::string const &convert_subs = vm["convert-subs"].as<std::string>();
        line.Convert_subs(convert_subs);
    }
    if (vm.count("transcription")) {
        bool const &transcription = vm["transcription"].as<bool>();
        line.Transcription(transcription);
    }
    if (vm.count("proxy")) {
        std::string const &proxy = vm["proxy"].as<std::string>();
        line.Proxy(proxy);
    }
    if (vm.count("exec-after")) {
        std::string const &exec_after = vm["exec-after"].as<std::string>();
        line.Exec_after(exec_after);
    }
    if (vm.count("exec-before")) {
        std::string const &exec_before = vm["exec-before"].as<std::string>();
        line.Exec_before(exec_before);
    }
    if (vm.count("urls")) {
        std::vector<std::string> const &urls =
            vm["urls"].as<std::vector<std::string>>();
        std::set<boost::url_view> urls_s;

        for (const auto &url : urls) {
            boost::system::result<boost::urls::url_view> r =
                boost::urls::parse_uri(url);

            if (r.has_value())
                urls_s.insert(r.value());
            else {
                std::cerr << "The link to the video is incorrect: " << r.value()
                          << "\n";
                continue;
            }
        }
        line.Urls(urls_s);

    } else {
        std::cout << Helper::exampes << "\n";
        exit(EXIT_FAILURE);
    }
    if (vm.count("debug")) {
        bool const &_debug = vm["debug"].as<bool>();
        line.Debug(_debug);
    }
    if (vm.count("test")) {
        bool const &test = vm["test"].as<bool>();
        line.Test(test);
    }
    return line;
}



