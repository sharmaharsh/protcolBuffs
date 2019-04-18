
#include <arpa/inet.h>
#include <gtest/gtest.h>

#include "DankMessage.pbo.h"
TEST(DankMessage_memes, memes_test) {
DankMessage my_message;
DankMessage_init(&my_message);
EXPECT_EQ(0xDEADBEEF, my_message.magic);
EXPECT_EQ(false, DankMessage_has_memes(&my_message));
EXPECT_EQ(0, my_message.memes_size);

      const char *test_str = "The quick brown fox jumps over the lazy dog";
DankMessage_set_memes(&my_message, test_str, strlen(test_str));
EXPECT_EQ(true, DankMessage_has_memes(&my_message));

    char buf[150];
DankMessage_memes(&my_message, buf, sizeof(buf));

    EXPECT_EQ(0, strcmp(buf, test_str));
DankMessage_clear_memes(&my_message);
EXPECT_EQ(false, DankMessage_has_memes(&my_message));
EXPECT_EQ(0, my_message.memes_size);

    // Test string truncation
    memset(buf, 3, sizeof(buf));
buf[sizeof(buf) - 1] = 0;
DankMessage_set_memes(&my_message, buf, strlen(buf));

    char buf2[150];
DankMessage_memes(&my_message, buf2, sizeof(buf2));

    buf[100] = 0;
EXPECT_EQ(100, strlen(buf2));
EXPECT_EQ(0, strcmp(buf, buf2));
}
TEST(DankMessage_wowow, wowow_test){
DankMessage my_message;
DankMessage_init(&my_message);
EXPECT_EQ(0xDEADBEEF, my_message.magic);EXPECT_EQ(false, DankMessage_has_wowow(&my_message));
EXPECT_EQ(0x00000000, my_message.wowow);
DankMessage_set_wowow(&my_message, 0x12345678);
EXPECT_EQ(true, DankMessage_has_wowow(&my_message));
EXPECT_EQ(htonl(0x12345678), my_message.wowow);
EXPECT_EQ(0x12345678, DankMessage_wowow(&my_message));
DankMessage_clear_wowow(&my_message);
EXPECT_EQ(false, DankMessage_has_wowow(&my_message));
EXPECT_EQ(0x00000000, my_message.wowow);
}
TEST(DankMessage_swag, swag_test){
DankMessage my_message;
DankMessage_init(&my_message);
EXPECT_EQ(0xDEADBEEF, my_message.magic);EXPECT_EQ(false, DankMessage_has_swag(&my_message));
EXPECT_EQ(0x00, my_message.swag);
DankMessage_set_swag(&my_message, 0x12);
EXPECT_EQ(true, DankMessage_has_swag(&my_message));
EXPECT_EQ((0x12), my_message.swag);
EXPECT_EQ(0x12, DankMessage_swag(&my_message));
DankMessage_clear_swag(&my_message);
EXPECT_EQ(false, DankMessage_has_swag(&my_message));
EXPECT_EQ(0x00, my_message.swag);
}
TEST(DankMessage_danker, danker_test) {
DankMessage my_message;
DankMessage_init(&my_message);
EXPECT_EQ(0xDEADBEEF, my_message.magic);
EXPECT_EQ(false, DankMessage_has_danker(&my_message));
EXPECT_EQ(0, my_message.danker_size);

      const char *test_str = "The quick brown fox jumps over the lazy dog";
DankMessage_set_danker(&my_message, test_str, strlen(test_str));
EXPECT_EQ(true, DankMessage_has_danker(&my_message));

    char buf[150];
DankMessage_danker(&my_message, buf, sizeof(buf));

    EXPECT_EQ(0, strcmp(buf, test_str));
DankMessage_clear_danker(&my_message);
EXPECT_EQ(false, DankMessage_has_danker(&my_message));
EXPECT_EQ(0, my_message.danker_size);

    // Test string truncation
    memset(buf, 3, sizeof(buf));
buf[sizeof(buf) - 1] = 0;
DankMessage_set_danker(&my_message, buf, strlen(buf));

    char buf2[150];
DankMessage_danker(&my_message, buf2, sizeof(buf2));

    buf[100] = 0;
EXPECT_EQ(100, strlen(buf2));
EXPECT_EQ(0, strcmp(buf, buf2));
}
