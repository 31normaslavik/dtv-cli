
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include "video.h"
#include <fstream>
#include <boost/json/src.hpp>

using namespace testing;

struct VideoTest : public Test{
    dtv::Video video;
    std::ifstream ifs;
    // Test interface
protected:
    void SetUp(){}
    void TearDown(){}
};

TEST_F(VideoTest, ExtractorYoutube)
{
    ifs.open("../../test/jsons/3jMTHkawNGo__Youtube__Holiday weeks__.info.json");
    boost::json::value const v = boost::json::parse(ifs);
    video = boost::json::value_to<dtv::Video>(std::move(v));

    // ASSERT_TRUE(v);

}
