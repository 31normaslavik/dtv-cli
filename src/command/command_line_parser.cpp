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
        ("temp-dir-path","")
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

    if (vm.count("examples")) {
        std::cout << Helper::exampes << std::endl;
        exit(EXIT_SUCCESS);
    }

    if (vm.count("urls")) {
        std::vector<std::string> const& urls = vm["urls"].as<std::vector<std::string>>();
        std::set<boost::url_view> urls_s;

        for (const auto &url : urls){
            boost::system::result<boost::urls::url_view> r = boost::urls::parse_uri(url);

            if(r.has_value())
                urls_s.insert(r.value());
            else {
                std::cerr << "The link to the video is incorrect: " << r.value() << "\n";
                continue ;
            }
        }

        line.Urls(urls_s);

    } else {
        std::cout << Helper::exampes << "\n";
        exit(EXIT_FAILURE);
    }

    if (std::string resolution; vm.count("resolution")) {
        resolution = vm["resolution"].as<std::string>();
        if (resolution != "360" && resolution != "480" && resolution != "720" &&
            resolution != "1080" && resolution != "1440" && resolution != "2160" &&
            resolution != "4320") {
            std::cerr << "The video resolution is incorrectly specified" << std::endl;
            std::cout << Helper::exampes << std::endl;
            exit(0);
        } else {
            // if (resolution == "4320" && format == "webm") {
            //     std::cerr << "For 4320p video resolution, only mp4 format is supported"
            //               << std::endl;
            //     std::cout << examples << std::endl;
            //     exit(0);
            // }
            // format.append("_").append(resolution);
        }
    }


    if (vm.count("output")) {
        std::cout << "path to save files: " << vm["output"].as<fs::path>()
                  << "\n\n";
    }

    return line;
}



