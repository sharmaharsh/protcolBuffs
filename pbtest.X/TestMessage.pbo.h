
/*****************************************************************************
 *                   AUTOMATICALLY GENERATED FILE. DO NOT EDIT.              *
 ****************************************************************************/
#ifndef _TESTMESSAGE_H_
#define _TESTMESSAGE_H_
#include <stdbool.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
      extern "C" {
#endif // #ifdef __cplusplus

#define TestMessage_FIELD_MAX (4)
typedef struct __attribute__((packed)) {
uint32_t magic;
unsigned char has_field[TestMessage_FIELD_MAX / CHAR_BIT + 1];
uint32_t my32;
uint16_t my16;
uint8_t my8;
uint32_t myS100_size;
char myS100[100];
} TestMessage;
void TestMessage_init(TestMessage *msg);
/*
 * int32 my32
 */
bool TestMessage_has_my32(const TestMessage *msg);
int32_t TestMessage_my32(const TestMessage *msg);
void TestMessage_set_my32(TestMessage *msg, int32_t value);
void TestMessage_clear_my32(TestMessage *msg);
/*
 * int16 my16
 */
bool TestMessage_has_my16(const TestMessage *msg);
int16_t TestMessage_my16(const TestMessage *msg);
void TestMessage_set_my16(TestMessage *msg, int16_t value);
void TestMessage_clear_my16(TestMessage *msg);
/*
 * int8 my8
 */
bool TestMessage_has_my8(const TestMessage *msg);
int8_t TestMessage_my8(const TestMessage *msg);
void TestMessage_set_my8(TestMessage *msg, int8_t value);
void TestMessage_clear_my8(TestMessage *msg);
/*
 * string myS100
 */
bool TestMessage_has_myS100(const TestMessage *msg);
size_t TestMessage_myS100(const TestMessage *msg, char *dest, size_t lim);
void TestMessage_set_myS100(TestMessage *msg, const char *src, size_t src_len);
void TestMessage_clear_myS100(TestMessage *msg);
void TestMessage_to_bytes(const TestMessage *msg, char *buf);
void TestMessage_from_bytes(TestMessage *msg, const char *buf);

#ifdef __cplusplus
  }
#endif // #ifdef __cplusplus

#endif
  