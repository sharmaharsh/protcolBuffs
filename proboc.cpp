#include <algorithm>
#include <cctype>

#include "proboc.h"

namespace {
std::string IntegralRenderForwardDeclarations(const std::string &message_name,
                                              const std::string &member_name,
                                              const std::string &datatype) {
  std::string has_fn = "bool " + message_name + "_has_" + member_name +
                       "(const " + message_name + " *msg);\n";
  std::string get_fn = datatype + " " + message_name + "_" + member_name +
                       "(const " + message_name + " *msg);\n";
  std::string set_fn = "void " + message_name + "_set_" + member_name + "(" +
                       message_name + " *msg, " + datatype + " value);\n";
  std::string clear_fn = "void " + message_name + "_clear_" + member_name +
                         "(" + message_name + " *msg);\n";
  return has_fn + get_fn + set_fn + clear_fn;
}

std::string IntegralRenderDefinitions(const std::string &message_name,
                                      const std::string &member_name,
                                      const std::string &datatype,
                                      long long index, const std::string &ntoh,
                                      const std::string &hton) {
  std::string has_fn = "bool " + message_name + "_has_" + member_name +
                       "(const " + message_name +
                       " *msg) {\ncheck_magic(msg);\nreturn has_field(msg, " +
                       std::to_string(index) + ");\n}\n";
  std::string get_fn =
      datatype + " " + message_name + "_" + member_name + "(const " +
      message_name + "*msg) {\ncheck_magic(msg);\nif (has_field(msg, " +
      std::to_string(index) + ")) {\nreturn " + ntoh + "(msg->" + member_name +
      ");\n} else {\nfprintf(stderr, \"Requested field " + member_name +
      " from " + message_name + " at address %p, but message do3s not have the "
                                "field \\n\", (void*)msg); return -1;\n}\n}\n";
  std::string set_fn = "void " + message_name + "_set_" + member_name + "(" +
                       message_name + " *msg, " + datatype +
                       " value) {\ncheck_magic(msg);\nmsg->" + member_name +
                       " = " + hton + "(value);\nset_field_present(msg, " +
                       std::to_string(index) + ");\n}\n";
  std::string clear_fn =
      "void " + message_name + "_clear_" + member_name + "(" + message_name +
      " *msg) {\ncheck_magic(msg);\nmsg->" + member_name +
      " = 0;\nset_field_absent(msg, " + std::to_string(index) + ");\n}\n";
  return has_fn + get_fn + set_fn + clear_fn;
}
}

Int32Member::Int32Member(const std::string &identifier, long long index,
                         const std::string &message_name)
    : index(index), identifier(identifier), message_name(message_name) {}

std::string Int32Member::StructMember() {
  return "uint32_t " + identifier + ";\n";
}

std::string Int32Member::ForwardDeclarations() {
  std::string retval = "/*\n * int32 " + identifier + "\n */\n";
  retval +=
      IntegralRenderForwardDeclarations(message_name, identifier, "int32_t");
  return retval;
}

std::string Int32Member::FunctionDefinitions() {
  std::string retval = "/*\n * int32 " + identifier + "\n */\n";
  retval += IntegralRenderDefinitions(message_name, identifier, "int32_t",
                                      index, "ntohl", "htonl");
  return retval;
}

void Int32Member::SetMessageName(const std::string &message_name) {
  this->message_name = message_name;
}

std::string Int32Member::UnitTest() {
  std::string retval = std::string("TEST(") + message_name + "_" + identifier +
                       ", " + identifier + "_test){\n";
  retval += message_name + " my_message;\n";
  retval += message_name + "_init(&my_message);\n";
  retval += "EXPECT_EQ(0xDEADBEEF, my_message.magic);";
  retval += std::string("EXPECT_EQ(false, ") + message_name + "_has_" +
            identifier + "(&my_message));\n";
  retval +=
      std::string("EXPECT_EQ(0x00000000, my_message.") + identifier + ");\n";

  retval +=
      message_name + "_set_" + identifier + "(&my_message, 0x12345678);\n";

  retval += std::string("EXPECT_EQ(true, ") + message_name + "_has_" +
            identifier + "(&my_message));\n";
  retval += std::string("EXPECT_EQ(htonl(0x12345678), my_message.") +
            identifier + ");\n";
  retval += std::string("EXPECT_EQ(0x12345678, ") + message_name + "_" +
            identifier + "(&my_message));\n";

  retval += message_name + "_clear_" + identifier + "(&my_message);\n";
  retval += std::string("EXPECT_EQ(false, ") + message_name + "_has_" +
            identifier + "(&my_message));\n";
  retval +=
      std::string("EXPECT_EQ(0x00000000, my_message.") + identifier + ");\n";
  retval += "}\n";

  return retval;
}

Int16Member::Int16Member(const std::string &identifier, long long index,
                         const std::string &message_name)
    : index(index), identifier(identifier), message_name(message_name) {}

std::string Int16Member::StructMember() {
  return "uint16_t " + identifier + ";\n";
}

std::string Int16Member::ForwardDeclarations() {
  std::string retval = "/*\n * int16 " + identifier + "\n */\n";
  retval +=
      IntegralRenderForwardDeclarations(message_name, identifier, "int16_t");
  return retval;
}

std::string Int16Member::FunctionDefinitions() {
  std::string retval = "/*\n * int32 " + identifier + "\n */\n";
  retval += IntegralRenderDefinitions(message_name, identifier, "int16_t",
                                      index, "ntohs", "htons");
  return retval;
}

void Int16Member::SetMessageName(const std::string &message_name) {
  this->message_name = message_name;
}

std::string Int16Member::UnitTest() {
  std::string retval = std::string("TEST(") + message_name + "_" + identifier +
                       ", " + identifier + "_test){\n";
  retval += message_name + " my_message;\n";
  retval += message_name + "_init(&my_message);\n";
  retval += "EXPECT_EQ(0xDEADBEEF, my_message.magic);";
  retval += std::string("EXPECT_EQ(false, ") + message_name + "_has_" +
            identifier + "(&my_message));\n";
  retval += std::string("EXPECT_EQ(0x0000, my_message.") + identifier + ");\n";

  retval += message_name + "_set_" + identifier + "(&my_message, 0x1234);\n";

  retval += std::string("EXPECT_EQ(true, ") + message_name + "_has_" +
            identifier + "(&my_message));\n";
  retval +=
      std::string("EXPECT_EQ(htons(0x1234), my_message.") + identifier + ");\n";
  retval += std::string("EXPECT_EQ(0x1234, ") + message_name + "_" +
            identifier + "(&my_message));\n";

  retval += message_name + "_clear_" + identifier + "(&my_message);\n";
  retval += std::string("EXPECT_EQ(false, ") + message_name + "_has_" +
            identifier + "(&my_message));\n";
  retval += std::string("EXPECT_EQ(0x0000, my_message.") + identifier + ");\n";
  retval += "}\n";

  return retval;
}

Int8Member::Int8Member(const std::string &identifier, long long index,
                       const std::string &message_name)
    : index(index), identifier(identifier), message_name(message_name) {}

std::string Int8Member::StructMember() {
  return "uint8_t " + identifier + ";\n";
}

std::string Int8Member::ForwardDeclarations() {
  std::string retval = "/*\n * int8 " + identifier + "\n */\n";
  retval +=
      IntegralRenderForwardDeclarations(message_name, identifier, "uint8_t");
  return retval;
}

std::string Int8Member::FunctionDefinitions() {
  std::string retval = "/*\n * int32 " + identifier + "\n */\n";
  retval += IntegralRenderDefinitions(message_name, identifier, "uint8_t", index,
                                      "", "");
  return retval;
}

void Int8Member::SetMessageName(const std::string &message_name) {
  this->message_name = message_name;
}

std::string Int8Member::UnitTest() {
  std::string retval = std::string("TEST(") + message_name + "_" + identifier +
                       ", " + identifier + "_test){\n";
  retval += message_name + " my_message;\n";
  retval += message_name + "_init(&my_message);\n";
  retval += "EXPECT_EQ(0xDEADBEEF, my_message.magic);";
  retval += std::string("EXPECT_EQ(false, ") + message_name + "_has_" +
            identifier + "(&my_message));\n";
  retval += std::string("EXPECT_EQ(0x00, my_message.") + identifier + ");\n";

  retval += message_name + "_set_" + identifier + "(&my_message, 0x12);\n";

  retval += std::string("EXPECT_EQ(true, ") + message_name + "_has_" +
            identifier + "(&my_message));\n";
  retval += std::string("EXPECT_EQ((0x12), my_message.") + identifier + ");\n";
  retval += std::string("EXPECT_EQ(0x12, ") + message_name + "_" + identifier +
            "(&my_message));\n";

  retval += message_name + "_clear_" + identifier + "(&my_message);\n";
  retval += std::string("EXPECT_EQ(false, ") + message_name + "_has_" +
            identifier + "(&my_message));\n";
  retval += std::string("EXPECT_EQ(0x00, my_message.") + identifier + ");\n";
  retval += "}\n";

  return retval;
}

StringMember::StringMember(const std::string &message_name, long long index,
                           const std::string &identifier, size_t size)
    : index(index), identifier(identifier), message_name(message_name),
      size(size) {}

std::string StringMember::StructMember() {
  return "uint32_t " + identifier + "_size;\nchar " + identifier + "[" +
         std::to_string(size) + "];\n";
}

std::string StringMember::ForwardDeclarations() {
  std::string retval = "/*\n * string " + identifier + "\n */\n";
  std::string has_fn = "bool " + message_name + "_has_" + identifier +
                       "(const " + message_name + " *msg);\n";
  std::string get_fn = "size_t " + message_name + "_" + identifier +
                       "(const " + message_name +
                       " *msg, char *dest, size_t lim);\n";
  std::string set_fn = "void " + message_name + "_set_" + identifier + "(" +
                       message_name +
                       " *msg, const char *src, size_t src_len);\n";
  std::string clear_fn = "void " + message_name + "_clear_" + identifier + "(" +
                         message_name + " *msg);\n";
  return retval + has_fn + get_fn + set_fn + clear_fn;
}

std::string StringMember::FunctionDefinitions() {
  std::string retval = "/*\n * string " + identifier + "\n */\n";
  std::string has_fn = "bool " + message_name + "_has_" + identifier +
                       "(const " + message_name +
                       " *msg) {\ncheck_magic(msg);\nreturn has_field(msg, " +
                       std::to_string(index) + ");\n}\n";
  std::string get_fn =
      "size_t " + message_name + "_" + identifier + "(const " + message_name +
      " *msg, char *dest, size_t lim) {\nif (has_field(msg, " +
      std::to_string(index) + ")) {\nsize_t char_count = (lim - 1 < msg->" +
      identifier + "_size ? lim - 1 : msg->" + identifier +
      "_size);\nmemmove(dest, msg->" + identifier +
      ", char_count);\ndest[char_count] = '\\0';\nreturn char_count;\n} else "
      "{\nfprintf(stderr, \"Requested field " +
      identifier + " from " + message_name +
      " at address %p, but message does not have the "
      "field\\n\",(void*)msg); return 0;\n}\n}\n";
  std::string set_fn =
      "void " + message_name + "_set_" + identifier + "(" + message_name +
      " *msg, const char *src, size_t src_len) {\nsize_t char_count = (" +
      std::to_string(size) + " > src_len ? src_len : " + std::to_string(size) +
      ");\nmemmove((void *)msg->" + identifier + ", src, char_count);\nmsg->" +
      identifier + "_size = htonl(char_count);\nset_field_present(msg, " +
      std::to_string(index) + ");\n}\n";
  std::string clear_fn =
      "void " + message_name + "_clear_" + identifier + "(" + message_name +
      " *msg) {\nif (has_field(msg, " + std::to_string(index) +
      ")) {\nset_field_absent(msg, " + std::to_string(index) + ");\nmsg->" +
      identifier + "_size = 0;\n}\n}\n";
  return retval + has_fn + get_fn + set_fn + clear_fn;
}

void StringMember::SetMessageName(const std::string &message_name) {
  this->message_name = message_name;
}

std::string MessageDescriptor::RenderHeader() {
  std::string include_guard = "_";
  std::transform(begin(identifier), end(identifier),
                 std::back_inserter<std::string>(include_guard),
                 [](const char &x) -> char { return std::toupper(x); });
  include_guard += "_H_";

  std::string retval = R"(
/*****************************************************************************
 *                   AUTOMATICALLY GENERATED FILE. DO NOT EDIT.              *
 ****************************************************************************/
)";

  retval += "#ifndef " + include_guard + "\n"
                      + "#define " + include_guard + "\n";

  retval += R"(#include <stdbool.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
      extern "C" {
#endif // #ifdef __cplusplus

#define )";

    long long max = 0;
    for (const auto &x : members) {
      if (x.first > max)
        max = x.first;
    }

    retval += identifier + "_FIELD_MAX (" + std::to_string(max) + ")\n";

    retval += "typedef struct __attribute__((packed)) {\nuint32_t magic;\n";
    retval += "uint64_t siphash;\n";
    retval += "uint32_t seq;\n";
    retval += "unsigned char has_field[" + identifier +
              "_FIELD_MAX / CHAR_BIT + 1];\n";

    for (auto &x : members) {
      retval += x.second->StructMember();
    }

    retval += "} " + identifier + ";\n";
    retval += "void " + identifier + "_init(" + identifier + " *msg);\n";

    for (auto &x : members) {
      retval += x.second->ForwardDeclarations();
    }

    retval += "void " + identifier + "_to_bytes(" + identifier +
              " *msg, char *buf, uint32_t seq);\n";
    retval += "bool " + identifier + "_from_bytes(" + identifier +
              " *msg, const char *buf, uint32_t *seq_out);\n";

    retval += R"(
#ifdef __cplusplus
  }
#endif // #ifdef __cplusplus

#endif
  )";

  return retval;
}

std::string MessageDescriptor::RenderCppFile() {
  std::string retval = R"(
/*****************************************************************************
 *                   AUTOMATICALLY GENERATED FILE. DO NOT EDIT.              *
 ****************************************************************************/
)";

  retval += R"(
#ifdef NETWORK_BIG_ENDIAN
#include <arpa/inet.h>
#endif
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint64_t siphash24(const void *src, unsigned long src_sz, const char key[16]);

#ifndef NETWORK_BIG_ENDIAN
static uint32_t htonl(uint32_t hostlong) {
  return hostlong;
}

static uint16_t htons(uint16_t hostshort) {
  return hostshort;
}

static uint32_t ntohl(uint32_t netlong) {
  return netlong;
}

static uint16_t ntohs(uint16_t netshort) {
  return netshort;
}
#endif

#include ")";
  retval += identifier;

  retval += R"(.pbo.h"

      static bool
      has_field(const )";

      retval += identifier + R"( *msg, size_t i) {
                size_t byte_index = i / CHAR_BIT;
  return ((unsigned)msg->has_field[byte_index] & (1u << (i % CHAR_BIT - 1)));
}

static void set_field_present()" + 
identifier + R"(*msg, size_t i) {
  size_t byte_index = i / CHAR_BIT;
  msg->has_field[byte_index] |= (1u << (i % CHAR_BIT - 1));
}

static void set_field_absent()" + identifier + R"(*msg, size_t i) {
  size_t byte_index = i / CHAR_BIT;
  msg->has_field[byte_index] &= ~(1u << (i % CHAR_BIT - 1));
}

static void check_magic(const )" + identifier + R"(*msg) {
  if (msg->magic != htonl(0xDEADBEEFu)) {
    fprintf(stderr,
            "Invalid magic number for message )" + identifier + R"( at %p\n",
            (void *)msg);
  }
}

void )" + identifier + R"(_init()" + identifier + R"( *msg) {
  memset(msg, 0, sizeof(*msg));
  // TODO: generate this from a hash at compile time
  msg->magic = htonl(0xDEADBEEFu);
}
)";

for (auto& x : members) {
  retval += x.second->FunctionDefinitions();
}

retval += R"(void )" + identifier + R"(_to_bytes()" + identifier + R"( *msg, char *buf, uint32_t seq) {
          size_t offset = sizeof(msg->magic) + sizeof(msg->siphash);
          msg->seq = seq;
          msg->siphash = siphash24(((char*)msg) + offset, sizeof(*msg) - offset,
                                   "scary spooky skeletons");
          memmove((void *)buf, (void *)msg, sizeof(*msg));
}

bool )" 
+ identifier + R"(_from_bytes()" + identifier + R"( *msg, const char *buf, uint32_t *seq_out) {
  size_t offset = sizeof(msg->magic) + sizeof(msg->siphash);
  memmove((void *)msg, (void*)buf, sizeof(*msg));
  *seq_out = msg->seq;
  return (siphash24(((char*)msg) + offset, sizeof(*msg) - offset,
                                   "scary spooky skeletons") == msg->siphash);
}
)";

return retval;
}

std::string StringMember::UnitTest() {
  std::string retval = "TEST(" + message_name + "_" + identifier + ", " +
                       identifier + "_test) {\n";
  retval += message_name + " my_message;\n";
  retval += message_name + "_init(&my_message);\n";

  retval += "EXPECT_EQ(0xDEADBEEF, my_message.magic);\n";
  retval += "EXPECT_EQ(false, " + message_name + "_has_" + identifier +
            "(&my_message));\n";
  retval += "EXPECT_EQ(0, my_message." + identifier + "_size);\n";
  retval += R"(
      const char *test_str = "The quick brown fox jumps over the lazy dog";
)";
  retval += message_name + "_set_" + identifier 
         + "(&my_message, test_str, strlen(test_str));\n";
retval += "EXPECT_EQ(true, " + message_name + "_has_" + identifier +
          "(&my_message));\n";
retval += R"(
    char buf[150];
)";
  retval += message_name + "_" + identifier 
         + "(&my_message, buf, sizeof(buf));\n";
retval += R"(
    EXPECT_EQ(0, strcmp(buf, test_str));
)";

  retval += message_name + "_clear_" + identifier + "(&my_message);\n";
retval += "EXPECT_EQ(false, " + message_name + "_has_" + identifier +
          "(&my_message));\n";
retval += "EXPECT_EQ(0, my_message." + identifier + "_size);\n";

retval += R"(
    // Test string truncation
    memset(buf, 3, sizeof(buf));
buf[sizeof(buf) - 1] = 0;
)";
  retval += message_name + "_set_" + identifier
         + "(&my_message, buf, strlen(buf));\n";
retval += R"(
    char buf2[150];
)";

  retval += message_name + "_" + identifier
         + "(&my_message, buf2, sizeof(buf2));\n";
retval += R"(
    buf[100] = 0;
EXPECT_EQ(100, strlen(buf2));
EXPECT_EQ(0, strcmp(buf, buf2));
}
)";
  return retval;
}

std::string MessageDescriptor::RenderTestFile() {
  std::string retval = R"(
#ifdef NETWORK_BIG_ENDIAN
#include <arpa/inet.h>
#endif
#include <gtest/gtest.h>
#include <stdint.h>

#ifndef NETWORK_BIG_ENDIAN
static uint32_t htonl(uint32_t hostlong) {
  return hostlong;
}

static uint16_t htons(uint16_t hostshort) {
  return hostshort;
}

static uint32_t ntohl(uint32_t netlong) {
  return netlong;
}

static uint16_t ntohs(uint16_t netshort) {
  return netshort;
}
#endif



)";
  retval += "#include \"" + identifier + ".pbo.h\"\n";

  for (const auto& x : members) {
    retval += x.second->UnitTest();
  }

  return retval;
}

std::vector<MessageDescriptor> probo_messages(1);
