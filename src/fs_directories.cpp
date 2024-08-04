#include "fs_directories.h"

#include <iostream>
#include <random>

namespace dtv {
    namespace {
        namespace fs = std::filesystem;
    }

        FsDirectories::FsDirectories(const std::filesystem::path& pathToSave,
                                 const std::string& pathToTemp, const size_t length) {

            this->path_to_save_ = FsInitFullPath(pathToSave.string());
            if (!fs::exists(this->path_to_save_))
                fs::create_directories(this->path_to_save_);

            this->path_to_temp_ = fs::temp_directory_path().append(TempDirGenerate(pathToTemp, length));

            if (!fs::exists(this->path_to_temp_)) {
                fs::create_directories(this->path_to_temp_);
        }


        fs::current_path(this->path_to_temp_);
        std::cout << "Current temp path: " << fs::current_path() << "\n\n";
    }

        fs::path FsDirectories::GetPathToSave() const noexcept {
            return path_to_save_;
    }

        fs::path FsDirectories::GetPathToTemp() const noexcept {
            return path_to_temp_;
    }

    FsDirectories::~FsDirectories() {
        if (fs::exists(path_to_temp_)) {

            std::error_code er;
            fs::current_path(fs::temp_directory_path(), er);
            if (er) {
                std::cerr << " Can't remove dir: " << path_to_temp_ << "\n"
                    << "Value code: " << er.value() << " [" << er.message() << "]\n";
            }

            er.clear();

            std::filesystem::remove_all(path_to_temp_, er);
            if (er) {
                std::cerr << " Can't remove dir: " << path_to_temp_ << "\n"
                    << "Value code: " << er.value() << " [" << er.message() << "]\n";
            }
        }
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
        fs::path p;

        if (pathToSave.starts_with(".") && pathToSave.size() == 1) {
            return p = fs::current_path();

        } else if (pathToSave.starts_with("." + std::to_string(fs::path::preferred_separator))) {
            return p = fs::current_path() / pathToSave.substr(2);
        
        } else if (!pathToSave.starts_with(fs::path::preferred_separator)) {
            return p = fs::current_path() / pathToSave;
        
        } else {
            return fs::path(pathToSave);
        }
    }
} // namespace dtv
