ProtoBono
=========

Overview
--------
ProtoBono is a serialization format targeted at embedded systems. The main features of the format include:

* Efficiency - ProtoBono is a binary wire format that is represented in memory exactly how it is transmitted on the wire. Serialization/Parsing is essentially instantaneous
* Simplicity - ProtoBono abstracts away the implementation details to ensure correctness and allow for rapid development of applications
* Embedded system support - ProtoBono avoids all use of the C language heap in favor of representing the wire format in-place. This works especially well on memory-constrained embedded systems but also generalizes to more powerful platforms with little to no performance or simplicity costs.

Build Process
-------------

ProtoBono compiler dependencies:

* GNU C and C++ language toolchains (g++ requires c++14 support)
* GNU make
* Flex and Bison

Build instructions:

    $ cd (protobono directory)
    $ make

The build process generates a binary called proboc - the proboc compiler

proboc Command Line Flags
-------------------------

* input\_file: If specified, reads a ProtoBono description file from the specifed path rather than standard input
* output\_directory: If specified, writes the output .c and .h files to the specified path rather than the current directory.

ProtoBono IDL format
--------------------

ProtoBono messages are specified in a format similar to Google's Protocol Buffers, but modified to allow for the embedded system constraint. A sample description is as follows:

    message DankMessage {
      string[10] memes = 1;
      int32 wowow = 2;
      int8 swag = 3;
      string[10] danker = 4;
    }

The message "DankMessage" will be created as a C language struct on which you can call various accessor functions. The various members within the message are given unique indices so as to keep track of their presence within the in-memory structure.

Member Datatypes
----------------

* string[] - Fixed-width character array type.
* int{32, 16, 8} - Fixed with signed integral types

C Language API
--------------

The ProtoBono compiler generates the following functions for each message:

* Message-global functions
    * void {message name}\_init(const {message name} \*msg);
        * Initializes the message (NEED TO DO THIS ON EVERY PB MESSAGE)
    * void {message name}\_to\_bytes(const {message name} \*msg, char \*buf);
        * Helper function to copy serialized bytes of a message into a given buffer
    * void {message name}\_from\_bytes({message name} \*msg, const char \*buf);
        * Helper function to parse serialized bytes of a message in the given buffer into an object of the message type

* Integral type functions (int32, int16, int8)
    * bool {message name}\_has\_{member name}(const {message name} \*msg);
        * Returns whether the given instance has a value for the member
    * {integral type} {message name}\_{member name}(const {message name} \*msg);
        * Returns the value of the field
    * void {message name}\_set\_{member name}({message name} \*msg, {integral type} value);
        * Sets the value of the field
    * void {message name}\_clear\_{member name}({message name} \*msg);
        * Clears the value of the field

* String type functions
    * bool {message name}\_has\_{member name}(const {message name} \*msg);
      * Returns whether the message has a value for the string member
    * size\_t {message name}\_{member name}(const {message name} \*msg, char \*dest, size\_t lim);
      * Copies the string value of the field into the given buffer, provided a limiting size lim. lim is the size of the entire buffer, null termination is handled automaticallyv.
    * void {message name}\_set\_{member name}({message name} \*msg, const char \*src, size\_t src\_len);
      * Copies the string in the given buffer up to min(src\_len, string size);
    * void {message name}\_clear\_{member name}({message name} \*msg);
      * Clears the string member

Example Usage
-------------

Sample message definition reproduced from above:

\#DankMessage.pbo

    message DankMessage {
      string[10] memes = 1;
      int32 wowow = 2;
      int8 swag = 3;
      string[10] danker = 4;
    }

Compilation Command:

    $ ./proboc < DankMessage.pbo

C usage:

\#test.c

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

Compilation command:

    $ gcc test.c DankMessage.pbo.c -o ./test

Output:

    memes: The quick brown fox jumps over the lazy dog

    wowow: -559038737
    swag: -3
    danker: quick brown fox jumps over the lazy dog
