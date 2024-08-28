
#include "fs_directories.h"
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

using namespace testing;

struct FsDirectoriesTest: public Test{
    dtv::FsDirectories fs;
protected:
    void SetUp(){
    }
    void TearDown(){
    }

};

TEST_F(FsDirectoriesTest, ChangeTempDir)
{
    std::filesystem::path path = fs.GetPathToTemp();
    ASSERT_TRUE(std::filesystem::exists(fs.GetPathToTemp()));
    ASSERT_TRUE(std::filesystem::exists(fs.GetPathToSave()));

    std::filesystem::path newPath = std::filesystem::weakly_canonical("..");
    fs.ChangeTempPath(newPath);

    ASSERT_TRUE(std::filesystem::exists(newPath));
    ASSERT_FALSE(std::filesystem::exists(path));

    // EXPECT_EQ(1, 1);
    // ASSERT_THAT(0, Eq(0));
}
