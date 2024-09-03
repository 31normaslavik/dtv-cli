#pragma once

#include <filesystem>

namespace dtv {

    class FsDirectories {
    public:
        explicit FsDirectories(const std::filesystem::path &pathToSaveDir = std::filesystem::current_path());

        [[nodiscard]] std::filesystem::path GetPathToSave() const noexcept;
        [[nodiscard]] std::filesystem::path GetPathToTemp() const noexcept;
        void ChangeTempPath(const std::filesystem::path& new_path);

        ~FsDirectories();

    private:
        [[nodiscard]] std::filesystem::path TempDirGenerate(const std::filesystem::path& dir, std::size_t length) const noexcept;

        std::filesystem::path _path_to_temp;
        std::filesystem::path _path_to_save;
    };

} // dtv

