
#include <gtest/gtest.h>

#include "TestMessage.pbo.h"
TEST(TestMessage_my32, my32_test){
TestMessage my_message;
TestMessage_init(&my_message);
EXPECT_EQ(0xDEADBEEF, my_message.magic);EXPECT_EQ(false, TestMessage_has_my32(&my_message));
EXPECT_EQ(0x00000000, my_message.my32);
TestMessage_set_my32(&my_message, 0x12345678);
EXPECT_EQ(true, TestMessage_has_my32(&my_message));
EXPECT_EQ(htonl(0x12345678), my_message.my32);
EXPECT_EQ(0x12345678, TestMessage_my32(&my_message));
TestMessage_clear_my32(&my_message);
EXPECT_EQ(false, TestMessage_has_my32(&my_message));
EXPECT_EQ(0x00000000, my_message.my32);
}
TEST(TestMessage_my16, my16_test){
TestMessage my_message;
TestMessage_init(&my_message);
EXPECT_EQ(0xDEADBEEF, my_message.magic);EXPECT_EQ(false, TestMessage_has_my16(&my_message));
EXPECT_EQ(0x0000, my_message.my16);
TestMessage_set_my16(&my_message, 0x1234);
EXPECT_EQ(true, TestMessage_has_my16(&my_message));
EXPECT_EQ(htons(0x1234), my_message.my16);
EXPECT_EQ(0x1234, TestMessage_my16(&my_message));
TestMessage_clear_my16(&my_message);
EXPECT_EQ(false, TestMessage_has_my16(&my_message));
EXPECT_EQ(0x0000, my_message.my16);
}
TEST(TestMessage_my8, my8_test){
TestMessage my_message;
TestMessage_init(&my_message);
EXPECT_EQ(0xDEADBEEF, my_message.magic);EXPECT_EQ(false, TestMessage_has_my8(&my_message));
EXPECT_EQ(0x00, my_message.my8);
TestMessage_set_my8(&my_message, 0x12);
EXPECT_EQ(true, TestMessage_has_my8(&my_message));
EXPECT_EQ((0x12), my_message.my8);
EXPECT_EQ(0x12, TestMessage_my8(&my_message));
TestMessage_clear_my8(&my_message);
EXPECT_EQ(false, TestMessage_has_my8(&my_message));
EXPECT_EQ(0x00, my_message.my8);
}
TEST(TestMessage_myS100, myS100_test) {
TestMessage my_message;
TestMessage_init(&my_message);
EXPECT_EQ(0xDEADBEEF, my_message.magic);
EXPECT_EQ(false, TestMessage_has_myS100(&my_message));
EXPECT_EQ(0, my_message.myS100_size);

      const char *test_str = "The quick brown fox jumps over the lazy dog";
TestMessage_set_myS100(&my_message, test_str, strlen(test_str));
EXPECT_EQ(true, TestMessage_has_myS100(&my_message));

    char buf[150];
TestMessage_myS100(&my_message, buf, sizeof(buf));

    EXPECT_EQ(0, strcmp(buf, test_str));
TestMessage_clear_myS100(&my_message);
EXPECT_EQ(false, TestMessage_has_myS100(&my_message));
EXPECT_EQ(0, my_message.myS100_size);

    // Test string truncation
    memset(buf, 3, sizeof(buf));
buf[sizeof(buf) - 1] = 0;
TestMessage_set_myS100(&my_message, buf, strlen(buf));

    char buf2[150];
TestMessage_myS100(&my_message, buf2, sizeof(buf2));

    buf[100] = 0;
EXPECT_EQ(100, strlen(buf2));
EXPECT_EQ(0, strcmp(buf, buf2));
}
