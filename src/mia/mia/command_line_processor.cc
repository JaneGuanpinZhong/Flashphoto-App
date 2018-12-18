/**
This file is part of the CSCI-3081W Project Code, which was developed
at the University of Minnesota.
Copyright (c) 2018 Jane/Guanpin Zhong at the University of Minnesota.
Original Author(s) of this File:
  Jane/Guanpin Zhong, 11/14/18, University of Minnesota
*/

#include <iostream>
#include <string>
#include <cmath>
#include "mia/command_line_processor.h"

namespace image_tools {
  /// Constructor
  CommandLineProcessor::CommandLineProcessor() {
    image_editor = new ImageEditor();
  }

  /// Constructor
  CommandLineProcessor::CommandLineProcessor(image_tools::ImageEditor* image) {
    image_editor = image;
  }

  /// Destructor
  CommandLineProcessor::~CommandLineProcessor() {
    delete image_editor;
    image_editor = NULL;
  }

  /// Help function used to check if the parameter can be converted to float
  /// successfully.
  bool CommandLineProcessor::convertToFloat(std::string input) {
    float outputFloatValue = 0;
    try {
     outputFloatValue = std::stof(input);
     }
     catch(...) {
       std::cout << "Fails to find the float number parameter!" << std::endl;
       return false;
     }
     (void) outputFloatValue;
    return true;
  }

  void CommandLineProcessor::ProcessCommandLine(int argc, char* argv[]) {
  if (argc == 2) {
    /// If the user types "-h" (help message),
    /// print out all the options.
    if (std::string(argv[1]) == "-h") {
      helpMessage();
      return;
    } else {
      std::cout << "Invalid command!" << std::endl;
      helpMessage();
      return;
    }  /// If the user types two things, but the second one is not "-h",
    /// print out an error message and all the options.
    }
  for (int i = 1; i < argc; i++) {
    std::string mystring = static_cast<std::string>(argv[i]);
    /// See if the first one is a image name.
    if (i == 1) {
      if (isPng(mystring)) {
        LoadCommand *load_ = new LoadCommand(image_editor, mystring);
        cmds.push_back(load_);
        continue;
      } else {
        std::cout << "Failed to load the file." << std::endl;
        helpMessage();
        return;
        }
    } else if (i == argc - 1) {
      /// See if the last one is a image name.
      if (isPng(mystring)) {
      SaveCommand *save_ = new SaveCommand(image_editor, mystring);
      cmds.push_back(save_);
    } else {
        std::cout << "Failed to save the file." << std::endl;
        helpMessage();
        return;
      }
    } else {
    if (mystring == "-edgedetect") {
      EdgeFilterCommand *edge_cmd_ = new EdgeFilterCommand(image_editor);
      cmds.push_back(edge_cmd_);
    } else if (mystring == "-blur") {
      float myFloat = 0;
      if (convertToFloat(std::string(argv[i+1]))) {
      myFloat = std::stof(std::string(argv[i+1]));
      if (myFloat < 0) {
        std::cout << "Invalid parameter!" << std::endl;
        helpMessage();
        return;
      }  /// Check if the parameter is larger than 0.
         /// And same for other commands below.
      BlurFilterCommand *blur_ =
          new BlurFilterCommand(image_editor, myFloat);
        cmds.push_back(blur_);
        i++;
      } else {
        helpMessage();
        return;
      }
    } else if (mystring == "-sharpen") {
      float myFloat = 0;
      if (convertToFloat(std::string(argv[i+1]))) {
        myFloat = std::stof(std::string(argv[i+1]));
        if (myFloat < 0) {
          std::cout << "Invalid parameter!" << std::endl;
          helpMessage();
          return;
        }
        SharpenFilterCommand *sharpen_ =
          new SharpenFilterCommand(image_editor, myFloat);
        cmds.push_back(sharpen_);
        i++;
    } else {
      helpMessage();
      return;
    }
    } else if (mystring == "-red") {
      float myFloat = 0;
      if (convertToFloat(std::string(argv[i+1]))) {
        myFloat = std::stof(std::string(argv[i+1]));
        if (myFloat < 0) {
          std::cout << "Invalid parameter!" << std::endl;
          helpMessage();
          return;
        }
      ChannelsFilterCommand *red_ =
        new ChannelsFilterCommand(image_editor, myFloat, 1, 1);
      cmds.push_back(red_);
      i++;
    } else {
      helpMessage();
      return;
    }
    } else if (mystring == "-green") {
      float myFloat = 0;
      if (convertToFloat(std::string(argv[i+1]))) {
        myFloat = std::stof(std::string(argv[i+1]));
        if (myFloat < 0) {
          std::cout << "Invalid parameter!" << std::endl;
          helpMessage();
          return;
        }
      ChannelsFilterCommand *green_ =
        new ChannelsFilterCommand(image_editor, 1, myFloat, 1);
      cmds.push_back(green_);
    } else {
      helpMessage();
      return;
    }
    } else if (mystring == "-blue") {
      float myFloat = 0;
      if (convertToFloat(std::string(argv[i+1]))) {
        myFloat = std::stof(std::string(argv[i+1]));
        if (myFloat < 0) {
          std::cout << "Invalid parameter!" << std::endl;
          helpMessage();
          return;
        }
      ChannelsFilterCommand *blue_ =
        new ChannelsFilterCommand(image_editor, 1, 1, myFloat);
      cmds.push_back(blue_);
      i++;
    } else {
      helpMessage();
      return;
    }
  } else if (mystring == "-quantize") {
      /// The only filter that needs an integer parameter;
      float myint = std::stof(std::string(argv[i+1]));
      float dif = myint - floor(myint);
      if (!(dif > 0 || dif < 0) && myint >= 0) {
        QuantizeFilterCommand *quantize_ =
          new QuantizeFilterCommand(image_editor, myint);
        cmds.push_back(quantize_);
        i++;
    } else {
      helpMessage();
      return;
    }
    } else if (mystring == "-saturate") {
      float myFloat = 0;
      if (convertToFloat(std::string(argv[i+1]))) {
        myFloat = std::stof(std::string(argv[i+1]));
        if (myFloat < 0) {
          std::cout << "Invalid parameter!" << std::endl;
          helpMessage();
          return;
        }
      SaturateFilterCommand *saturate_ =
        new SaturateFilterCommand(image_editor, myFloat);
      cmds.push_back(saturate_);
      i++;
    } else {
      helpMessage();
      return;
    }
    } else if (mystring == "-threshold") {
      float myFloat = 0;
      if (convertToFloat(std::string(argv[i+1]))
    ) {
      myFloat = std::stof(std::string(argv[i+1]));
      if (myFloat < 0 || myFloat > 1) {
        std::cout << "Invalid parameter!" << std::endl;
        helpMessage();
        return;
      }
      ThresholdFilterCommand *threshold_ =
        new ThresholdFilterCommand(image_editor, myFloat);
      cmds.push_back(threshold_);
      i++;
    } else {
      helpMessage();
      return;
      }
    } else if (mystring == "-motionblur-n-s") {
      float myFloat = 0;
      if (convertToFloat(std::string(argv[i+1]))) {
        myFloat = std::stof(std::string(argv[i+1]));
        if (myFloat < 0) {
          std::cout << "Invalid parameter!" << std::endl;
          helpMessage();
          return;
        }
      ConvolutionFilterMotionBlur::MBlurDir dir_ =
        ConvolutionFilterMotionBlur::MBLUR_DIR_N_S;
      MotionBlurFilterCommand *motion_ns_ =
        new MotionBlurFilterCommand(image_editor, myFloat, dir_);
      cmds.push_back(motion_ns_);
      i++;
    } else {
      helpMessage();
      return;
    }
    } else if (mystring == "-motionblur-e-w") {
      float myFloat = 0;
      if (convertToFloat(std::string(argv[i+1]))) {
        myFloat = std::stof(std::string(argv[i+1]));
        if (myFloat < 0) {
          std::cout << "Invalid parameter!" << std::endl;
          helpMessage();
          return;
        }
      ConvolutionFilterMotionBlur::MBlurDir dir_ =
        ConvolutionFilterMotionBlur::MBLUR_DIR_E_W;
      MotionBlurFilterCommand *motion_ew_ =
        new MotionBlurFilterCommand(image_editor, myFloat, dir_);
      cmds.push_back(motion_ew_);
      i++;
    } else {
      helpMessage();
      return;
    }
    } else if (mystring == "-motionblur-ne-sw") {
      float myFloat = 0;
      if (convertToFloat(std::string(argv[i+1]))) {
        myFloat = std::stof(std::string(argv[i+1]));
        if (myFloat < 0) {
          std::cout << "Invalid parameter!" << std::endl;
          helpMessage();
          return;
        }
      ConvolutionFilterMotionBlur::MBlurDir dir_ =
        ConvolutionFilterMotionBlur::MBLUR_DIR_NE_SW;
      MotionBlurFilterCommand *motion_ne_sw_ =
        new MotionBlurFilterCommand(image_editor, myFloat, dir_);
      cmds.push_back(motion_ne_sw_);
      i++;
    } else {
      helpMessage();
      return;
    }
    } else if (mystring == "-motionblur-nw-se") {
      float myFloat = 0;
      if (convertToFloat(std::string(argv[i+1]))) {
        myFloat = std::stof(std::string(argv[i+1]));
        if (myFloat < 0) {
          std::cout << "Invalid parameter!" << std::endl;
          helpMessage();
          return;
        }
      ConvolutionFilterMotionBlur::MBlurDir dir_ =
        ConvolutionFilterMotionBlur::MBLUR_DIR_NW_SE;
      MotionBlurFilterCommand *motion_nw_se_ =
        new MotionBlurFilterCommand(image_editor, myFloat, dir_);
      cmds.push_back(motion_nw_se_);
      i++;
    } else {
      helpMessage();
      return;
    }
    } else {
      std::cout << "Invalid commands!" << std::endl;
      helpMessage();
      return;
    }
  }
}
  /// After finishing going through all the possible inputs,
  /// we traverse the vector and execute it.
  for (std::vector<int>::size_type x=0; x < (cmds.size()); x++) {
    cmds[x]->Execute();
    delete cmds[x];
    cmds[x] = NULL;
  }
}

  /// Help function to check if the file name is legal.
  bool CommandLineProcessor::isPng(std::string name) {
    int length = name.size();
    std::string sub = name.substr(length-4, 4);
    return (sub == ".png" || sub == ".PNG");
  }

  void CommandLineProcessor::helpMessage() {
    std::string help_ = std::string("usage: mia infile.png [image processing")
        + "commands ...] outfile.png\n"
        + "infile.png: input image file in png format\n"
        + "outfile.png: filename to use for saving the result\n"
        + "image processing commands:\n"
        + "-blur r: apply a gaussian blur of radius r\n"
        + "-edgedetect: apply an edge detection filter\n"
        + "-sharpen r: apply a sharpening filter of radius r\n"
        + "-red s: scale the red channel by factor s\n"
        + "-green s: scale the green channel by factor s\n"
        + "-blue s: scale the blue channel by factor s\n"
        + "-quantize n: quantize each color channel into n bins\n"
        + "-saturate s: saturate colors by scale factor s\n"
        + "-threshold c: threshold using cutoff value c\n"
        + "-motionblur-n-s r: north-south motion blur with kernel radius r\n"
        + "-motionblur-e-w r: east-west motion blur with kernel radius r\n"
        + "-motionblur-ne-sw r: ne-sw motion blur with kernel radius r\n"
        + "-motionblur-nw-se r: nw-se motion blur with kernel radius r\n";
      std::cout << help_;
  }
}  /// namespace image_tools
