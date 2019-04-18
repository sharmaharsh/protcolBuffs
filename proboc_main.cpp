#include <cstdio>
#include <fstream>
#include <gflags/gflags.h>
#include <iomanip>
#include <iostream>
#include <vector>

#include "proboc.h"

DEFINE_string(input_file, "",
              "The file to read ProtoBono message descriptions from");
DEFINE_string(output_dir, "", "Directory to output files to");
DEFINE_bool(streams, false, "Use input and output streams");
DEFINE_int32(stage, 1, "");

extern FILE *yyin;

extern "C" {
int yyparse();
}

int main(int argc, char **argv) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  FILE *input = nullptr;
  if (!FLAGS_streams) {
    if (!FLAGS_input_file.empty()) {
      input = fopen(FLAGS_input_file.c_str(), "r");
    }
  } else {
    input = stdin;
  }
  yyin = input;

  yyparse();
  if (nullptr != input) {
    fclose(input);
  }

  if (FLAGS_output_dir.empty()) {
    FLAGS_output_dir = "./";
  } else {
    FLAGS_output_dir += "/";
  }
  if (!FLAGS_streams) {
    for (auto &message : probo_messages) {
      if (message.processed) {
        std::ofstream(FLAGS_output_dir + message.identifier + ".pbo.h")
            << message.RenderHeader();
        std::ofstream(FLAGS_output_dir + message.identifier + ".pbo.c")
            << message.RenderCppFile();
        #ifdef PIC32
        std::ofstream(FLAGS_output_dir + message.identifier + "_test.c")
            << message.RenderTestFile();
        #else
        std::ofstream(FLAGS_output_dir + message.identifier + "_test.cpp")
            << message.RenderTestFile();
        #endif
      }
    }
  } else {
    for (auto &message : probo_messages) {
      if (message.processed) {
        switch (FLAGS_stage) {
        case 1:
          std::cout << message.RenderHeader();
          break;
        case 2:
          std::cout << message.RenderCppFile();
          break;
        case 3:
          std::cout << message.RenderTestFile();
          break;
        default:
          std::cerr << "invalid stage number";
        }
      }
    }
  }
}
