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

TEST_F(VideoTest, ExtractorYoutube1)
{
    ifs.open("jsons/3jMTHkawNGo__Youtube__Holiday_weeks__.info.json");
    ASSERT_TRUE(ifs.is_open());
    boost::json::value const v = boost::json::parse(ifs);
    video = boost::json::value_to<dtv::Video>(std::move(v));
    ifs.close();

    // ASSERT_TRUE(v);

}

TEST_F(VideoTest, ExtractorYoutube2)
{
    ifs.open("jsons/KIWR9Pdt7O0__Youtube__HistoryLegends__.info.json");
    ASSERT_TRUE(ifs.is_open());
    boost::json::value const v = boost::json::parse(ifs);
    video = boost::json::value_to<dtv::Video>(std::move(v));
    ifs.close();
    // ASSERT_TRUE(v);

}

TEST_F(VideoTest, ExtractorYoutube3)
{
    ifs.open("jsons/__2bjWbetsA__Youtube__Sony Pictures Entertainment__.info.json");
    ASSERT_TRUE(ifs.is_open());
    boost::json::value const v = boost::json::parse(ifs);
    video = boost::json::value_to<dtv::Video>(std::move(v));
    ifs.close();
    // ASSERT_TRUE(v);

}
TEST_F(VideoTest, ExtractorYoutube4)
{
    ifs.open("jsons/bsgzvEVEeRU__Youtube__LDPR-TV__.info.json");
    ASSERT_TRUE(ifs.is_open());
    boost::json::value const v = boost::json::parse(ifs);
    video = boost::json::value_to<dtv::Video>(std::move(v));
    ifs.close();
    // ASSERT_TRUE(v);

}
TEST_F(VideoTest, ExtractorYoutube5)
{
    ifs.open("jsons/yBOxxobkzvY__Youtube__Verden TV__.info.json");
    ASSERT_TRUE(ifs.is_open());
    boost::json::value const v = boost::json::parse(ifs);
    video = boost::json::value_to<dtv::Video>(std::move(v));
    ifs.close();
    // ASSERT_TRUE(v);

}
TEST_F(VideoTest, ExtractorPornHub)
{
    ifs.open("jsons/65e9a781a3977__PornHub__NA__.info.json");
    ASSERT_TRUE(ifs.is_open());
    boost::json::value const v = boost::json::parse(ifs);
    video = boost::json::value_to<dtv::Video>(std::move(v));
    ifs.close();
    // ASSERT_TRUE(v);

}
TEST_F(VideoTest, ExtractorRuTube)
{
    ifs.open("jsons/b4e43e911ef2c56f514501041fe46ecf__Rutube__NA__.info.json");
    ASSERT_TRUE(ifs.is_open());
    boost::json::value const v = boost::json::parse(ifs);
    video = boost::json::value_to<dtv::Video>(std::move(v));
    ifs.close();
    // ASSERT_TRUE(v);

}
TEST_F(VideoTest, ExtractorTwitch)
{
    ifs.open("jsons/v2163310012__TwitchVod__NA__.info.json");
    ASSERT_TRUE(ifs.is_open());
    boost::json::value const v = boost::json::parse(ifs);
    video = boost::json::value_to<dtv::Video>(std::move(v));
    ifs.close();
    // ASSERT_TRUE(v);

}
TEST_F(VideoTest, ExtractorTikTok1)
{
    ifs.open("jsons/7040865539949956353__TikTok__birthday June_6th.info.json");
    ASSERT_TRUE(ifs.is_open());
    boost::json::value const v = boost::json::parse(ifs);
    video = boost::json::value_to<dtv::Video>(std::move(v));
    ifs.close();
    // ASSERT_TRUE(v);

}
TEST_F(VideoTest, ExtractorTikTok2)
{
    ifs.open("jsons/7024211316860620033__TikTok__Kika Kim__.info.json");
    ASSERT_TRUE(ifs.is_open());
    boost::json::value const v = boost::json::parse(ifs);
    video = boost::json::value_to<dtv::Video>(std::move(v));
    ifs.close();
    // ASSERT_TRUE(v);

}
TEST_F(VideoTest, ExtractorTikTok3)
{
    ifs.open("jsons/7043048776034028802__TikTok__Yan__.info.json");
    ASSERT_TRUE(ifs.is_open());
    boost::json::value const v = boost::json::parse(ifs);
    video = boost::json::value_to<dtv::Video>(std::move(v));
    ifs.close();
    // ASSERT_TRUE(v);

}
TEST_F(VideoTest, ExtractorMailRu1)
{
    ifs.open("jsons/78529224_14269__MailRu__NA__.info.json");
    ASSERT_TRUE(ifs.is_open());
    boost::json::value const v = boost::json::parse(ifs);
    video = boost::json::value_to<dtv::Video>(std::move(v));
    ifs.close();
    // ASSERT_TRUE(v);

}

TEST_F(VideoTest, ExtractorMailRu2)
{
    ifs.open("jsons/78609180_14254__MailRu__NA__.info.json");
    ASSERT_TRUE(ifs.is_open());
    boost::json::value const v = boost::json::parse(ifs);
    video = boost::json::value_to<dtv::Video>(std::move(v));
    ifs.close();
    // ASSERT_TRUE(v);

}
TEST_F(VideoTest, ExtractorVimeo)
{
    ifs.open("jsons/952597318__Vimeo__NA__.info.json");
    ASSERT_TRUE(ifs.is_open());
    boost::json::value const v = boost::json::parse(ifs);
    video = boost::json::value_to<dtv::Video>(std::move(v));
    ifs.close();
    // ASSERT_TRUE(v);

}
TEST_F(VideoTest, ExtractorBiliBili)
{
    ifs.open("jsons/BV1dw4m1i7JJ__BiliBili__NA__.info.json");
    ASSERT_TRUE(ifs.is_open());
    boost::json::value const v = boost::json::parse(ifs);
    video = boost::json::value_to<dtv::Video>(std::move(v));
    ifs.close();
    // ASSERT_TRUE(v);

}
TEST_F(VideoTest, ExtractorVkRu)
{
    ifs.open("jsons/video_ext__Generic__NA__.info.json");
    ASSERT_TRUE(ifs.is_open());
    boost::json::value const v = boost::json::parse(ifs);
    video = boost::json::value_to<dtv::Video>(std::move(v));
    ifs.close();
    // ASSERT_TRUE(v);

}
TEST_F(VideoTest, ExtractorVkCom1)
{
    ifs.open("jsons/-106879986_456256058__VK__NA__.info.json");
    ASSERT_TRUE(ifs.is_open());
    boost::json::value const v = boost::json::parse(ifs);
    video = boost::json::value_to<dtv::Video>(std::move(v));
    ifs.close();
    // ASSERT_TRUE(v);

}
TEST_F(VideoTest, ExtractorVkCom2)
{
    ifs.open("jsons/-197178980_456239124__VK__NA__.info.json");
    ASSERT_TRUE(ifs.is_open());
    boost::json::value const v = boost::json::parse(ifs);
    video = boost::json::value_to<dtv::Video>(std::move(v));
    ifs.close();
    // ASSERT_TRUE(v);

}
TEST_F(VideoTest, ExtractorVkCom3)
{
    ifs.open("jsons/-215360893_456239107__VK__NA__.info.json");
    ASSERT_TRUE(ifs.is_open());
    boost::json::value const v = boost::json::parse(ifs);
    video = boost::json::value_to<dtv::Video>(std::move(v));
    ifs.close();
    // ASSERT_TRUE(v);

}
TEST_F(VideoTest, ExtractorXvideosCom)
{
    ifs.open("jsons/_-_-_-___Generic__NA__.info.json");
    ASSERT_TRUE(ifs.is_open());
    boost::json::value const v = boost::json::parse(ifs);
    video = boost::json::value_to<dtv::Video>(std::move(v));
    ifs.close();
    // ASSERT_TRUE(v);

}
TEST_F(VideoTest, ExtractorNineGag)
{
    ifs.open("jsons/Lithuania__NineGag__.json");
    ASSERT_TRUE(ifs.is_open());
    boost::json::value const v = boost::json::parse(ifs);
    video = boost::json::value_to<dtv::Video>(std::move(v));
    ifs.close();
    // ASSERT_TRUE(v);

}

