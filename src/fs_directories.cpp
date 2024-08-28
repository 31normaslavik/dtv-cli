#include "fs_directories.h"
#include "debug.h"

#include <iostream>
#include <random>

namespace dtv {
    namespace {
        namespace fs = std::filesystem;
    }

        FsDirectories::FsDirectories(const fs::path& pathToSaveDir) {
            _path_to_save = fs::weakly_canonical(pathToSaveDir);
            _path_to_temp = TempDirGenerate(_path_to_save / "dtv-cli", 8);

            if (!fs::exists(_path_to_temp)) {
                fs::create_directories(_path_to_temp);
        }

        fs::current_path(_path_to_temp);
        debug("Func: {}\nSave path: {}\nTemp path: {}\nCurrent path: {}\n", __func__, _path_to_save.string(),
              _path_to_temp.string(), fs::current_path().string());
    }

        fs::path FsDirectories::GetPathToSave() const noexcept {
            return _path_to_save;
    }

        fs::path FsDirectories::GetPathToTemp() const noexcept {
            return _path_to_temp;
    }

    void FsDirectories::ChangeTempPath(const fs::path &new_path)
    {
        if(fs::equivalent(fs::current_path(), _path_to_temp))
            fs::current_path(_path_to_save);

        fs::remove_all(_path_to_temp);
        _path_to_temp = TempDirGenerate(fs::weakly_canonical(new_path) / "dtv-cli", 8);
        fs::create_directories(_path_to_temp);
        fs::current_path(_path_to_temp);

        debug("Func: {}\nSave path: {}\nTemp path: {}\nCurrent path: {}\n", __func__, _path_to_save.string(),
              _path_to_temp.string(), fs::current_path().string());
    }

    FsDirectories::~FsDirectories() {
        if (fs::exists(_path_to_temp)) {
            std::error_code er;

            if(fs::equivalent(fs::current_path(), _path_to_temp))
                fs::current_path(_path_to_save);

            if (er) {
                std::cerr << " Can't change current path to : " << _path_to_save << "\n"
                    << "Value code: " << er.value() << " [" << er.message() << "]\n";
            }

            er.clear();
            fs::remove_all(_path_to_temp, er);
            if (er) {
                std::cerr << " Can't remove dir: " << _path_to_temp << "\n"
                    << "Value code: " << er.value() << " [" << er.message() << "]\n";
            }
        }
    }

    fs::path FsDirectories::TempDirGenerate(const fs::path& path,
                                               const std::size_t length) const noexcept {
        std::random_device rd;
        const std::string chars{"qwertyuiopasdfghjklzxcvbnm"};
        std::uniform_int_distribution<size_t> dist(0, chars.size() - 1);
        std::string temp{path.string() + "-"};

        for (size_t n{}; n < length; ++n)
            temp.push_back(chars[dist(rd)]);

        return fs::path(temp);
    }

} // namespace dtv
