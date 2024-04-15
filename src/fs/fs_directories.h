#pragma once

#include <string>
#include <filesystem>

namespace dtv {

    class FsDirectories {
    public:
        explicit FsDirectories(const std::filesystem::path& path_to_save, const std::string& path_to_temp = "dtv-cli",
                               size_t length = 6);

        [[nodiscard]] std::filesystem::path GetPathToSave() const noexcept;
        [[nodiscard]] std::filesystem::path GetPathToTemp() const noexcept;

        ~FsDirectories();

    private:
        [[nodiscard]] std::string TempDirGenerate(const std::string& dir, std::size_t length) const noexcept;
        [[nodiscard]] std::filesystem::path FsInitFullPath(const std::string& path_to_save) const noexcept;

        std::filesystem::path path_to_temp_;
        std::filesystem::path path_to_save_;
    };

} // dtv

