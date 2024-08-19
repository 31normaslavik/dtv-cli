
#include "fs_directories.h"
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

using namespace testing;

struct FsDirectoriesTest: public Test{
    dtv::FsDirectories *fs;
protected:
    void SetUp(){
        fs = new dtv::FsDirectories();
    }
    void TearDown(){
        delete fs;
    }

};

TEST_F(FsDirectoriesTest, ChangeTempDir)
{
    std::filesystem::path path = fs->GetPathToTemp();
    ASSERT_TRUE(std::filesystem::exists(path));

    std::filesystem::path oldPath = path;
    std::filesystem::path newPath = std::filesystem::current_path() / "../tempDirForTest";
    fs->ChangeTempPath(newPath);

    ASSERT_TRUE(std::filesystem::exists(newPath));
    ASSERT_FALSE(std::filesystem::exists(oldPath));




    // EXPECT_EQ(1, 1);
    // ASSERT_THAT(0, Eq(0));
}
