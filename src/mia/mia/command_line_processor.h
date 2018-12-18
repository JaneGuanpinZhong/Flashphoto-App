/**
This file is part of the CSCI-3081W Project Code, which was developed
at the University of Minnesota.
Copyright (c) 2018 Jane/Guanpin Zhong at the University of Minnesota.
Original Author(s) of this File:
  Jane/Guanpin Zhong, 11/14/18, University of Minnesota
*/


#ifndef MIA_COMMAND_LINE_PROCESSOR_H_
#define MIA_COMMAND_LINE_PROCESSOR_H_

#include <string>
#include <vector>
#include "mia/image_editor_commands.h"

namespace image_tools {

/// @brief A class used to create, store and run all commands from user input.
class CommandLineProcessor {
 public:
  /// Constructor
  CommandLineProcessor();

  /// constructor
  explicit CommandLineProcessor(image_tools::ImageEditor* image);

  /// destructor
  ~CommandLineProcessor();

  /// help function to check if the file name is legal
  bool convertToFloat(std::string input);

  /// check if the file name is legal.
  bool isPng(std::string name);

  /// print out help message
  void helpMessage();

  /// used to match all commands and execute them
  void ProcessCommandLine(int argc, char* argv[]);

 private:
  std::vector<ImageEditorCommand*> cmds;
  ImageEditor *image_editor;
};
}  /// namespace image_tools

#endif  // MIA_COMMAND_LINE_PROCESSOR_H_
