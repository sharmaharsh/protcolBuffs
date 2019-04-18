#include <stdio.h>
#include <string.h>

#include "DankMessage.pbo.h"

int main() {
  DankMessage my_dank;
  DankMessage_init(&my_dank);

  const char *test_str = "The quick brown fox jumps over the lazy dog\n";

  DankMessage_set_memes(&my_dank, test_str, strlen(test_str));
  DankMessage_set_wowow(&my_dank, 0xDEADBEEF);
  DankMessage_set_swag(&my_dank, -3);
  DankMessage_set_danker(&my_dank, test_str + 4, strlen(test_str + 4));

  unsigned char serialization_buf[sizeof(DankMessage)];
  DankMessage_to_bytes(&my_dank, serialization_buf);

  DankMessage parsed_msg;
  DankMessage_from_bytes(&parsed_msg, serialization_buf);

  char str_buf1[100], str_buf2[100];
  DankMessage_memes(&parsed_msg, str_buf1, sizeof(str_buf1));
  DankMessage_danker(&parsed_msg, str_buf2, sizeof(str_buf2));

  printf("memes: %s\nwowow: %d\nswag: %d\ndanker: %s\n", str_buf1,
         DankMessage_wowow(&parsed_msg), DankMessage_swag(&parsed_msg),
         str_buf2);
  return 0;
}
