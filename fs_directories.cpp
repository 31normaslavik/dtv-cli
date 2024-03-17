//
// Created by pancake on 12/12/23.
//

#include "fs_directories.h"

#include <iostream>
#include <random>

namespace dtv {
    namespace {
        namespace fs = std::filesystem;
    }

        FsDirectories::FsDirectories(const std::filesystem::path& pathToSave,
                                 const std::string& pathToTemp, const size_t length) {

        this->pathToSave = fs_init_full_path(pathToSave);
        if (!fs::exists(this->pathToSave))
            fs::create_directories(this->pathToSave);

        this->pathToTemp = fs::temp_directory_path().append(tempDirGenerate(pathToTemp, length));

        if (!fs::exists(this->pathToTemp)) {
            fs::create_directories(this->pathToTemp);
        }


        fs::current_path(this->pathToTemp);
        std::cout << fs::current_path() << std::endl;
    }

    fs::path FsDirectories::getPathToSave() const noexcept {
        return pathToSave;
    }

    fs::path FsDirectories::getPathToTemp() const noexcept {
        return pathToTemp;
    }

    FsDirectories::~FsDirectories() {
        std::filesystem::remove_all(pathToTemp);
    }

    // void FsDirectories::setPathToTempDirectory() const noexcept {
    //     fs::current_path(pathToTemp);
    // }

    std::string FsDirectories::tempDirGenerate(const std::string& dir,
                                               const std::size_t length) const noexcept {
        std::random_device rd;

        const std::string chars{"qwertyuiopasdfghjklzxcvbnm"};
        std::uniform_int_distribution<size_t> dist(0, chars.size() - 1);

        std::string temp{dir + "-"};
        for (int n = 0; n < length; ++n)
            temp.push_back(chars[dist(rd)]);

        return temp;
    }

    fs::path FsDirectories::fs_init_full_path(const std::string& pathToSave) {
        if (pathToSave.starts_with(".") && pathToSave.size() == 1) {
            return fs::path(std::getenv("PWD"));
        } else if (pathToSave.starts_with("." + std::to_string(fs::path::preferred_separator))) {
            return fs::path (std::string(std::getenv("PWD")) + fs::path::preferred_separator + pathToSave.substr(2));
        } else if (!pathToSave.starts_with("/")) {
            return fs::path(std::string(std::getenv("PWD")) + fs::path::preferred_separator + pathToSave);
        } else {
            return fs::path(pathToSave);
        }
    }
} // namespace dtv
