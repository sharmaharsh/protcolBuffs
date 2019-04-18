
/*****************************************************************************
 *                   AUTOMATICALLY GENERATED FILE. DO NOT EDIT.              *
 ****************************************************************************/

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIG_ENDIAN 0

#if (!BIG_ENDIAN)
static uint32_t swap_32(uint32_t op) {
  return ((op>>24)&0xff) |
         ((op<<8)&0xff0000) | 
         ((op>>8)&0xff00) |
         ((op<<24)&0xff000000);
}
#endif

static uint32_t ntohl(uint32_t netlong) {
#if BIG_ENDIAN
  return netlong;
#else
  return swap_32(netlong); 
#endif
}

static uint32_t htonl(uint32_t hostlong) {
#if BIG_ENDIAN
  return hostlong;
#else
  return swap_32(hostlong);
#endif
}

#if (!BIG_ENDIAN)
static uint16_t swap_16(uint16_t op) {
  return (op>>8) | (op<<8);
}
#endif

static uint16_t ntohs(uint16_t netshort) {
#if BIG_ENDIAN
  return netshort;
#else
  return swap_16(netshort);
#endif
}

static uint16_t htons(uint16_t hostshort) {
#if BIG_ENDIAN
  return hostshort;
#else
  return swap_16(hostshort);
#endif
}


#include "TestMessage.pbo.h"

      static bool
      has_field(const TestMessage *msg, size_t i) {
                size_t byte_index = i / CHAR_BIT;
  return ((unsigned)msg->has_field[byte_index] & (1u << (i % CHAR_BIT - 1)));
}

static void set_field_present(TestMessage*msg, size_t i) {
  size_t byte_index = i / CHAR_BIT;
  msg->has_field[byte_index] |= (1u << (i % CHAR_BIT - 1));
}

static void set_field_absent(TestMessage*msg, size_t i) {
  size_t byte_index = i / CHAR_BIT;
  msg->has_field[byte_index] &= ~(1u << (i % CHAR_BIT - 1));
}

static void check_magic(const TestMessage*msg) {
  if (msg->magic != htonl(0xDEADBEEFu)) {
    fprintf(stderr,
            "Invalid magic number for message TestMessage at %p\n",
            (void *)msg);
    abort();
  }
}

void TestMessage_init(TestMessage *msg) {
  memset(msg, 0, sizeof(*msg));
  // TODO: generate this from a hash at compile time
  msg->magic = htonl(0xDEADBEEF);
}
/*
 * int32 my32
 */
bool TestMessage_has_my32(const TestMessage *msg) {
check_magic(msg);
return has_field(msg, 1);
}
int32_t TestMessage_my32(const TestMessage*msg) {
check_magic(msg);
if (has_field(msg, 1)) {
return ntohl(msg->my32);
} else {
fprintf(stderr, "Requested field my32 from TestMessage at address %p, but message dows not have the field \n", (void*)msg);
abort();
}
}
void TestMessage_set_my32(TestMessage *msg, int32_t value) {
check_magic(msg);
msg->my32 = htonl(value);
set_field_present(msg, 1);
}
void TestMessage_clear_my32(TestMessage *msg) {
check_magic(msg);
msg->my32 = 0;
set_field_absent(msg, 1);
}
/*
 * int32 my16
 */
bool TestMessage_has_my16(const TestMessage *msg) {
check_magic(msg);
return has_field(msg, 2);
}
int16_t TestMessage_my16(const TestMessage*msg) {
check_magic(msg);
if (has_field(msg, 2)) {
return ntohs(msg->my16);
} else {
fprintf(stderr, "Requested field my16 from TestMessage at address %p, but message dows not have the field \n", (void*)msg);
abort();
}
}
void TestMessage_set_my16(TestMessage *msg, int16_t value) {
check_magic(msg);
msg->my16 = htons(value);
set_field_present(msg, 2);
}
void TestMessage_clear_my16(TestMessage *msg) {
check_magic(msg);
msg->my16 = 0;
set_field_absent(msg, 2);
}
/*
 * int32 my8
 */
bool TestMessage_has_my8(const TestMessage *msg) {
check_magic(msg);
return has_field(msg, 3);
}
int8_t TestMessage_my8(const TestMessage*msg) {
check_magic(msg);
if (has_field(msg, 3)) {
return (msg->my8);
} else {
fprintf(stderr, "Requested field my8 from TestMessage at address %p, but message dows not have the field \n", (void*)msg);
abort();
}
}
void TestMessage_set_my8(TestMessage *msg, int8_t value) {
check_magic(msg);
msg->my8 = (value);
set_field_present(msg, 3);
}
void TestMessage_clear_my8(TestMessage *msg) {
check_magic(msg);
msg->my8 = 0;
set_field_absent(msg, 3);
}
/*
 * string myS100
 */
bool TestMessage_has_myS100(const TestMessage *msg) {
check_magic(msg);
return has_field(msg, 4);
}
size_t TestMessage_myS100(const TestMessage *msg, char *dest, size_t lim) {
if (has_field(msg, 4)) {
size_t char_count = (lim - 1 < msg->myS100_size ? lim - 1 : msg->myS100_size);
memcpy(dest, msg->myS100, char_count);
dest[char_count] = '\0';
return char_count;
} else {
fprintf(stderr, "Requested field myS100 from TestMessage at address %p, but message does not have the field\n",(void*)msg);
abort();
}
}
void TestMessage_set_myS100(TestMessage *msg, const char *src, size_t src_len) {
size_t char_count = (100 > src_len ? src_len : 100);
memcpy((void *)msg->myS100, src, char_count);
msg->myS100_size = htonl(char_count);
set_field_present(msg, 4);
}
void TestMessage_clear_myS100(TestMessage *msg) {
if (has_field(msg, 4)) {
set_field_absent(msg, 4);
msg->myS100_size = 0;
}
}
void TestMessage_to_bytes(const TestMessage *msg, char *buf) {
          memcpy((void *)buf, (void *)msg, sizeof(*msg));
}

void TestMessage_from_bytes(TestMessage *msg, const char *buf) {
  memcpy((void *)msg, (void *)buf, sizeof(*msg));
}
