#include "command_line_parser.h"
#include "debug.h"
#include "helper.h"
#include "version.h"
#include <boost/url.hpp>

const dtv::CommandLine dtv::command_line_parser(int argc, char *argv[]) {
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
         opt::value<std::string>()->default_value(fs::current_path().string()),
         "Path to save")
        ("no-overwrites","Do not overwrite exist files")
        // ("write-description","")
        ("temp-dir", opt::value<std::string>() ,"Changing temporary path")
        ;

    verbosity.add_options()
        // ("quiet", "")
        // ("progress", "")
        ;

    video.add_options()
        ("height,H",
         opt::value<int>()->default_value(1080),
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
        ("vol-audio", opt::value<int>()->default_value(25),"The sound level of the original audio")
        ("vol-translate", opt::value<int>()->default_value(100),"Audio translation sound level")
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
        // ("debug","Debug")
        ("test","Test mode. Video length limit of 10 seconds")
        ;

    all.add(general).add(filesystem).add(verbosity).add(video).add(audio).add(subtitle).add(network).add(processing).add(hide).add(debug);
    visible.add(general).add(filesystem).add(verbosity).add(video).add(audio).add(subtitle).add(network).add(processing).add(debug);

    opt::positional_options_description p;
    p.add("urls", -1);

    opt::variables_map vm;
    opt::store(opt::command_line_parser(argc, argv).options(all).positional(p).run(), vm);
    opt::notify(vm);

    /**
     * GENERAL
     */
    if (vm.contains("help")) {
        std::cout << visible << "\n";
        exit(EXIT_SUCCESS);
    }
    if (vm.contains("version")) {
        std::cout << getName() << " " << getVersion() << "\n";
        exit(EXIT_SUCCESS);
    }
    if (vm.contains("update")) {
        exit(EXIT_SUCCESS);
    }
    if (vm.contains("code-country")) {
        std::cout << Helper::codes_country << "\n";
        exit(EXIT_SUCCESS);
    }

    if (vm.contains("examples")) {
        std::cout << Helper::exampes << "\n";
        exit(EXIT_SUCCESS);
    }

    /*
     * FILESYSTEM
     */
    if (vm.contains("output")) {
        fs::path const &output = vm["output"].as<std::string>();
        line.Output(output);
    }
    if (vm.contains("no-overwrites,w")) {
        line.No_overwrites(true);
    }
    if (vm.contains("write-description")) {
        line.Write_description(true);
    }
    if (vm.contains("temp-dir")) {
        fs::path const &temp_dir_path = vm["temp-dir"].as<std::string>();
        line.Output(temp_dir_path);
    }

    /*
     * VERBOSITY
     */
    if (vm.contains("quiet")) {
        line.Quiet(true);
    }
    if (vm.contains("progress")) {
        line.Progress(true);
    }

    /*
     * VIDEO
     */
    if (vm.contains("height")) {
        int const height = vm["height"].as<int>();

        if (height < 0 || height > 5000) {
            std::cerr << "The video resolution is incorrectly specified\n";
            std::cout << Helper::exampes << "\n";
            exit(EXIT_FAILURE);
        }
        line.Height(height);
    }
    if (vm.contains("extension")) {
        std::string const &extension = vm["extension"].as<std::string>();
        line.Extension(extension);
    }
    if (vm.contains("merge-output-extension")) {
        std::string const &merge_output_extension =
            vm["merge-output-extension"].as<std::string>();
        line.Merge_output_extension(merge_output_extension);
    }
    if (vm.contains("saving-original-video-resolution")) {
        line.Saving_original_video_resolution(true);
    }
    if (vm.contains("yes-playlist")) {
        line.YesPlaylist(true);
    }
    if (vm.contains("fps")) {
        int fps = vm["fps"].as<int>();
        if(fps > 15)
            line.Fps(fps);
    }

    /*
     * AUDIO
     */
    if (vm.contains("translate-from-lang")) {
        std::string const &translate_from_lang =
            vm["translate-from-lang"].as<std::string>();
        line.Translate_from_lang(translate_from_lang);
    }
    if (vm.contains("translate-to-lang")) {
        std::string const &translate_to_lang =
            vm["translate-to-lang"].as<std::string>();
        line.Translate_to_lang(translate_to_lang);
    }
    if (vm.contains("no-translate")) {
        line.No_translate(true);
    }
    if (vm.contains("only-translate")) {
        line.Only_translate(true);
    }
    if (vm.contains("replace-audio")) {
        fs::path const &replace_audio = vm["replace-audio"].as<std::string>();
        line.Replace_audio(replace_audio);
    }
    if (vm.contains("replace-translate")) {
        fs::path const &replace_translate =
            vm["replace-translate"].as<std::string>();
        line.Replace_translate(replace_translate);
    }
    if (vm.contains("vol-audio")) {
        int const vol_audio = vm["vol-audio"].as<int>();
        line.Vol_audio(vol_audio / 100.);
    }
    if (vm.contains("vol-translate")) {
        int const vol_translate = vm["vol-translate"].as<int>();
        line.Vol_translate(vol_translate / 100.);
    }
    if (vm.contains("save-translation")) {
        line.Save_translation(true);
    }
    if (vm.contains("save-translation-no-merge")) {
        line.Save_translation_no_merge(true);
    }
    if (vm.contains("save-translation-contaner")) {
        std::string const &save_translation_contaner =
            vm["save-translation-contaner"].as<std::string>();
        line.Save_translation_contaner(save_translation_contaner);
    }

    /**
     * SUBTITLES
     */
    if (vm.contains("write-subs")) {
        line.Write_subs(true);
    }
    if (vm.contains("sub-lang")) {
        std::string const &sub_lang = vm["sub-lang"].as<std::string>();
        line.Sub_lang(sub_lang);
    }
    if (vm.contains("write-auto-subs")) {
        line.Write_auto_subs(true);
    }
    if (vm.contains("sub-format")) {
        std::string const &sub_format = vm["sub-format"].as<std::string>();
        line.Sub_format(sub_format);
    }
    if (vm.contains("sub-langs")) {
        std::cout << Helper::subtitles_langs << "\n";
    }
    if (vm.contains("embed-subs")) {
        line.Embed_subs(true);
    }
    if (vm.contains("convert-subs")) {
        std::string const &convert_subs = vm["convert-subs"].as<std::string>();
        line.Convert_subs(convert_subs);
    }
    if (vm.contains("transcription")) {
        line.Transcription(true);
    }

    /*
     * NETWORK
     */
    if (vm.contains("proxy")) {
        std::string const &proxy = vm["proxy"].as<std::string>();
        line.Proxy(proxy);
    }

    /*
     * PROCESSING
     */
    if (vm.contains("exec-after")) {
        std::string const &exec_after = vm["exec-after"].as<std::string>();
        line.Exec_after(exec_after);
    }
    if (vm.contains("exec-before")) {
        std::string const &exec_before = vm["exec-before"].as<std::string>();
        line.Exec_before(exec_before);
    }

    /*
     * HIDE
     */
    if (vm.contains("urls")) {
        std::vector<std::string> const &urls =
            vm["urls"].as<std::vector<std::string>>();
        std::set<std::string> urls_s;

        for (const auto &url : urls) {
            boost::system::result<boost::urls::url_view> r =
                boost::urls::parse_uri(url);

            if (r.has_value())
                urls_s.insert(r.value().buffer());
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

    /*
     * DEBUG
     */
    if (vm.contains("debug")) {
        Debug::debug = true;
    }
    if (vm.contains("test")) {
        line.Test(true);
    }
    return line;
}



