
/*****************************************************************************
 *                   AUTOMATICALLY GENERATED FILE. DO NOT EDIT.              *
 ****************************************************************************/

#include <arpa/inet.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DankMessage.pbo.h"

      static bool
      has_field(const DankMessage *msg, size_t i) {
                size_t byte_index = i / CHAR_BIT;
  return ((unsigned)msg->has_field[byte_index] & (1u << (i % CHAR_BIT - 1)));
}

static void set_field_present(DankMessage*msg, size_t i) {
  size_t byte_index = i / CHAR_BIT;
  msg->has_field[byte_index] |= (1u << (i % CHAR_BIT - 1));
}

static void set_field_absent(DankMessage*msg, size_t i) {
  size_t byte_index = i / CHAR_BIT;
  msg->has_field[byte_index] &= ~(1u << (i % CHAR_BIT - 1));
}

static void check_magic(const DankMessage*msg) {
  if (msg->magic != 0xDEADBEEFu) {
    fprintf(stderr,
            "Invalid magic number for message DankMessage at %p\n",
            (void *)msg);
    abort();
  }
}

void DankMessage_init(DankMessage *msg) {
  memset(msg, 0, sizeof(*msg));
  // TODO: generate this from a hash at compile time
  msg->magic = 0xDEADBEEF;
}
/*
 * string memes
 */
bool DankMessage_has_memes(const DankMessage *msg) {
check_magic(msg);
return has_field(msg, 1);
}
size_t DankMessage_memes(const DankMessage *msg, char *dest, size_t lim) {
if (has_field(msg, 1)) {
size_t char_count = (lim - 1 < msg->memes_size ? lim - 1 : msg->memes_size);
memcpy(dest, msg->memes, char_count);
dest[char_count] = '\0';
return char_count;
} else {
fprintf(stderr, "Requested field memes from DankMessage at address %p, but message does not have the field\n",(void*)msg);
abort();
}
}
void DankMessage_set_memes(DankMessage *msg, const char *src, size_t src_len) {
size_t char_count = (100 > src_len ? src_len : 100);
memcpy((void *)msg->memes, src, char_count);
msg->memes_size = char_count;
set_field_present(msg, 1);
}
void DankMessage_clear_memes(DankMessage *msg) {
if (has_field(msg, 1)) {
set_field_absent(msg, 1);
msg->memes_size = 0;
}
}
/*
 * int32 wowow
 */
bool DankMessage_has_wowow(const DankMessage *msg) {
check_magic(msg);
return has_field(msg, 2);
}
int32_t DankMessage_wowow(const DankMessage*msg) {
check_magic(msg);
if (has_field(msg, 2)) {
return ntohl(msg->wowow);
} else {
fprintf(stderr, "Requested field wowow from DankMessage at address %p, but message dows not have the field \n", (void*)msg);
abort();
}
}
void DankMessage_set_wowow(DankMessage *msg, int32_t value) {
check_magic(msg);
msg->wowow = htonl(value);
set_field_present(msg, 2);
}
void DankMessage_clear_wowow(DankMessage *msg) {
check_magic(msg);
msg->wowow = 0;
set_field_absent(msg, 2);
}
/*
 * int32 swag
 */
bool DankMessage_has_swag(const DankMessage *msg) {
check_magic(msg);
return has_field(msg, 3);
}
int8_t DankMessage_swag(const DankMessage*msg) {
check_magic(msg);
if (has_field(msg, 3)) {
return (msg->swag);
} else {
fprintf(stderr, "Requested field swag from DankMessage at address %p, but message dows not have the field \n", (void*)msg);
abort();
}
}
void DankMessage_set_swag(DankMessage *msg, int8_t value) {
check_magic(msg);
msg->swag = (value);
set_field_present(msg, 3);
}
void DankMessage_clear_swag(DankMessage *msg) {
check_magic(msg);
msg->swag = 0;
set_field_absent(msg, 3);
}
/*
 * string danker
 */
bool DankMessage_has_danker(const DankMessage *msg) {
check_magic(msg);
return has_field(msg, 4);
}
size_t DankMessage_danker(const DankMessage *msg, char *dest, size_t lim) {
if (has_field(msg, 4)) {
size_t char_count = (lim - 1 < msg->danker_size ? lim - 1 : msg->danker_size);
memcpy(dest, msg->danker, char_count);
dest[char_count] = '\0';
return char_count;
} else {
fprintf(stderr, "Requested field danker from DankMessage at address %p, but message does not have the field\n",(void*)msg);
abort();
}
}
void DankMessage_set_danker(DankMessage *msg, const char *src, size_t src_len) {
size_t char_count = (100 > src_len ? src_len : 100);
memcpy((void *)msg->danker, src, char_count);
msg->danker_size = char_count;
set_field_present(msg, 4);
}
void DankMessage_clear_danker(DankMessage *msg) {
if (has_field(msg, 4)) {
set_field_absent(msg, 4);
msg->danker_size = 0;
}
}
void DankMessage_to_bytes(const DankMessage *msg, char *buf) {
          memcpy((void *)buf, (void *)msg, sizeof(*msg));
}

void DankMessage_from_bytes(DankMessage *msg, const char *buf) {
  memcpy((void *)msg, (void *)buf, sizeof(*msg));
}
