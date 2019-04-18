
/*****************************************************************************
 *                   AUTOMATICALLY GENERATED FILE. DO NOT EDIT.              *
 ****************************************************************************/
#ifndef _DANKMESSAGE_H_
#define _DANKMESSAGE_H_
#include <stdbool.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
      extern "C" {
#endif // #ifdef __cplusplus

#define DankMessage_FIELD_MAX (4)
typedef struct __attribute__((packed)) {
uint32_t magic;
unsigned char has_field[DankMessage_FIELD_MAX / CHAR_BIT + 1];
size_t memes_size;
char memes[100];
uint32_t wowow;
uint8_t swag;
size_t danker_size;
char danker[100];
} DankMessage;
void DankMessage_init(DankMessage *msg);
/*
 * string memes
 */
bool DankMessage_has_memes(const DankMessage *msg);
size_t DankMessage_memes(const DankMessage *msg, char *dest, size_t lim);
void DankMessage_set_memes(DankMessage *msg, const char *src, size_t src_len);
void DankMessage_clear_memes(DankMessage *msg);
/*
 * int32 wowow
 */
bool DankMessage_has_wowow(const DankMessage *msg);
int32_t DankMessage_wowow(const DankMessage *msg);
void DankMessage_set_wowow(DankMessage *msg, int32_t value);
void DankMessage_clear_wowow(DankMessage *msg);
/*
 * int8 swag
 */
bool DankMessage_has_swag(const DankMessage *msg);
int8_t DankMessage_swag(const DankMessage *msg);
void DankMessage_set_swag(DankMessage *msg, int8_t value);
void DankMessage_clear_swag(DankMessage *msg);
/*
 * string danker
 */
bool DankMessage_has_danker(const DankMessage *msg);
size_t DankMessage_danker(const DankMessage *msg, char *dest, size_t lim);
void DankMessage_set_danker(DankMessage *msg, const char *src, size_t src_len);
void DankMessage_clear_danker(DankMessage *msg);
void DankMessage_to_bytes(const DankMessage *msg, char *buf);
void DankMessage_from_bytes(DankMessage *msg, const char *buf);

#ifdef __cplusplus
  }
#endif // #ifdef __cplusplus

#endif
  