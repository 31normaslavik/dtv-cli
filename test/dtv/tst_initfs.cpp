
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

using namespace testing;

TEST(filesystemTest, InitFS)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}
