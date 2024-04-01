//
// Created by pancake on 12/12/23.
//
#pragma once

#ifndef FS_DIRECTORIES_H
#define FS_DIRECTORIES_H

#include <string>
#include <filesystem>

namespace dtv {

    class FsDirectories {
    public:
        explicit FsDirectories(const std::filesystem::path& pathToSave, const std::string& pathToTemp = "dtv-cli",
                               size_t length = 6);

        [[nodiscard]] std::filesystem::path getPathToSave() const noexcept;
        [[nodiscard]] std::filesystem::path getPathToTemp() const noexcept;

        // void setPathToTempDirectory() const noexcept;

        // ~FsDirectories();

    private:
        [[nodiscard]] std::string tempDirGenerate(const std::string& dir, std::size_t length) const noexcept;
        std::filesystem::path fs_init_full_path(const std::string& pathToSave);

        std::filesystem::path pathToTemp;
        std::filesystem::path pathToSave;
    };
} // dtv

#endif //FS_DIRECTORIES_H
