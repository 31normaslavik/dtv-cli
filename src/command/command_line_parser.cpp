#include "command_line_parser.h"

const dtv::CommandLine dtv::command_line_parser(int argc, char *argv[]) {
    namespace opt = boost::program_options;
    opt::options_description general("All options");

    std::string format;

    general.add_options()("help,h", "This help\n")
        ("format,f", opt::value<std::string>(&format)->default_value("mp4"),
         "[mp4 webm]\n")

        ("resolution,r",
         opt::value<std::string>()->default_value("1080"),
         "Available options: [4320 2160 1440 1080 720 480 360]\n"
         "The resolution of the downloaded video.\n"
         "If there is no video in this format, then the best quality with a lower "
         "resolution will be downloaded: 1080p -> 720p -> 480p, etc\n")

        ("fps", "Sets the priority to 60 fps for the video. If there is no video "
                "with 60 fps, it will be downloaded from 30 fps")(
            "hdr", "Sets the priority in HDR for the video. If the video does not "
            "support HDR, it will be downloaded without it\n")

        ("output,o",
         opt::value<std::filesystem::path>()->default_value(
             std::filesystem::current_path()),
         "The path where the video will be saved. "
         "By default, it will be saved in the directory from which the program is "
         "launched\n")

        ("urls,u",
         opt::value<std::vector<std::string>>()->multitoken(),
         "The link(s) of the source from where you want to download "
         "the video. Playlists are also supported");

    opt::options_description examples("Examples");
    examples.add_options()(
        "examples,e",
        "If the specified path does not exist, the program will try to create "
        "the missing directories\n"
        "For 4320p video resolution, only mp4 format is supported\n\n"
        "#Format mp4, 1080p, fps 30, path current\n"
        "dtv-cli -u \"url1\"\n\n"
        "#Format mp4, 480p, fps 30, path ./playlist4\n"
        "dtv-cli --output ./playlist4 --format mp4 --resolution 480 --urls "
        "\"url1\" \"url2\"\n\n"
        "#Format mp4, 1080p, fps 60, path ./playlist1\n"
        "dtv-cli --output ./playlist1 --format mp4 --resolution 1080 --fps "
        "--urls \"url\"\n\n"
        "#Format mp4, 2160p, fps 60, HDR, path ./playlist4\n"
        "dtv-cli --output ./playlist4 --format mp4 --resolution 2160 --fps --hdr "
        "--urls \"url1\" \"url2\"\n\n"
        "#Format webm, 2160p, fps 60, HDR, path /home/user/Videos\n"
        "dtv-cli -o /home/user/Videos -f webm -r 2160 --fps --hdr -u \"url1\" "
        "\"url2\" \"url3\"\n\n"
        "#Format mp4, 4320p, fps 60, HDR, path ./myvideos\n"
        "dtv-cli -o ./myvideos -f mp4 -r 7680x4320 --fps --hdr -u \"url1\" "
        "\"url2\" \"url3\"\n\n"
        "#Format webm, 1080p, fps 30, path current\n"
        "dtv-cli -f webm -u \"url1\"\n");

    opt::options_description all;
    all.add(general).add(examples);

    opt::variables_map vm;
    opt::store(opt::command_line_parser(argc, argv).options(all).run(), vm);
    opt::notify(vm);

    if (vm.count("help")) {
        std::cout << general << std::endl;
        std::cout << examples << std::endl;
        exit(0);
    }

    if (vm.count("examples")) {
        std::cout << examples << std::endl;
        exit(0);
    }

    if (vm.count("urls")) {
        std::cout << "urls:\n" << vm["urls"].as<std::vector<std::string>>()
                  << "\n";
        for (const auto &url : vm["urls"].as<std::vector<std::string>>())
            if (url.find("https://") == std::string::npos) {
                std::cerr << "The link to the video is incorrect: " << url << "\n";
                //exit(0);
            }

    } else {
        std::cout << examples << "\n";
        exit(0);
    }

    if (vm.count("format")) {
        if (format != "mp4" && format != "webm") {
            std::cerr << "Invalid format is specified" << std::endl;
            std::cout << examples << std::endl;
            exit(0);
        }
    }

    if (std::string resolution; vm.count("resolution")) {
        resolution = vm["resolution"].as<std::string>();
        if (resolution != "360" && resolution != "480" && resolution != "720" &&
            resolution != "1080" && resolution != "1440" && resolution != "2160" &&
            resolution != "4320") {
            std::cerr << "The video resolution is incorrectly specified" << std::endl;
            std::cout << examples << std::endl;
            exit(0);
        } else {
            if (resolution == "4320" && format == "webm") {
                std::cerr << "For 4320p video resolution, only mp4 format is supported"
                          << std::endl;
                std::cout << examples << std::endl;
                exit(0);
            }
            format.append("_").append(resolution);
        }
    }

    if (vm.count("fps")) {
        format += "_60";
    } else {
        format += "_30";
    }

    if (vm.count("hdr")) {
        format += "_10";
    }

    if (vm.count("output")) {
        std::cout << "path to save files: " << vm["output"].as<std::filesystem::path>()
                  << "\n\n";
    }

    dtv::CommandLine line(vm["urls"].as<std::vector<std::string>>(),
                          vm["output"].as<std::filesystem::path>(),
                          format);

    return line;
}



