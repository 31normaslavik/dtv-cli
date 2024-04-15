#include "fs_directories.h"

#include <iostream>
#include <random>

namespace dtv {
    namespace {
        namespace fs = std::filesystem;
    }

        FsDirectories::FsDirectories(const std::filesystem::path& pathToSave,
                                 const std::string& pathToTemp, const size_t length) {

            this->path_to_save_ = FsInitFullPath(pathToSave);
            if (!fs::exists(this->path_to_save_))
                fs::create_directories(this->path_to_save_);

            this->path_to_temp_ = fs::temp_directory_path().append(TempDirGenerate(pathToTemp, length));

            if (!fs::exists(this->path_to_temp_)) {
                fs::create_directories(this->path_to_temp_);
        }


        fs::current_path(this->path_to_temp_);
        std::cout << "current temp path: " << fs::current_path() << "\n\n";
    }

        fs::path FsDirectories::GetPathToSave() const noexcept {
            return path_to_save_;
    }

        fs::path FsDirectories::GetPathToTemp() const noexcept {
            return path_to_temp_;
    }

    FsDirectories::~FsDirectories() {
        std::filesystem::remove_all(path_to_temp_);
    }

    std::string FsDirectories::TempDirGenerate(const std::string& dir,
                                               const std::size_t length) const noexcept {
        std::random_device rd;

        const std::string chars{"qwertyuiopasdfghjklzxcvbnm"};
        std::uniform_int_distribution<size_t> dist(0, chars.size() - 1);

        std::string temp{dir + "-"};
        for (size_t n{}; n < length; ++n)
            temp.push_back(chars[dist(rd)]);

        return temp;
    }

    fs::path FsDirectories::FsInitFullPath(const std::string& pathToSave) const noexcept {
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
