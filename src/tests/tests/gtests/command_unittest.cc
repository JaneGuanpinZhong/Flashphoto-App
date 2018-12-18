/**
This file is part of the CSCI-3081W Project Code, which was developed
at the University of Minnesota.
Copyright (c) 2018 Jane/Guanpin Zhong at the University of Minnesota.
Original Author(s) of this File:
  Jane/Guanpin Zhong, 11/14/18, University of Minnesota
*/

#include <iostream>
#include "gtest/gtest.h"
#include <mingfx.h>
#include <string>
#include <vector>
#include "mia/command_line_processor.h"
#include "imagetools/pixel_buffer.h"
#include "imagetools/image_editor.h"

using image_tools::CommandLineProcessor;
using image_tools::ImageEditor;

class CommandLineProcessorTest : public ::testing::Test {
  void SetUp() override {
    cmd_ = new CommandLineProcessor();
    image_tools::PixelBuffer* test1 =
      new image_tools::PixelBuffer("resources/test1.png");
    image1 = new ImageEditor(test1);
  }

  /// delete the pointers after use
  void TearDown() override {
    delete cmd_;
    cmd_ = NULL;
    delete image1;
    image1 = NULL;
  }

protected:
  CommandLineProcessor *cmd_;
  ImageEditor *image1;

  /// help message
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

  /// help function to transfer the type of the input vector
  char** trans(std::vector<std::string> v, int argc) {
    char** argv = new char* [argc];
    for (int i = 0; i < argc; i++) {
      argv[i] = (char*) malloc(v[i].length() * sizeof(char));
      std::strcpy (argv[i], (v.at(i)).c_str());
    }
    return argv;
  }
};

  /// @brief Basic idea for the first five tests: checking if those illegal
  /// commands will cause printing the correct error messages.
  /// test illegal input file name
TEST_F(CommandLineProcessorTest, badInput) {
  std::vector<std::string> v = {"mia", "-threshold", "0.3", "out.png"};
  testing::internal::CaptureStdout();
  cmd_->ProcessCommandLine(4, trans(v, 4));
  std::string output = testing::internal::GetCapturedStdout();
  std::string errormsg = std::string("Failed to load the file.\n") + help_;
  EXPECT_EQ(output, errormsg);
}

  /// test illegal output file name
TEST_F(CommandLineProcessorTest, badOutput) {
  std::vector<std::string> v =
    {"mia", "./resources/city.png", "-edgedetect", "out.p"};
  testing::internal::CaptureStdout();
  cmd_->ProcessCommandLine(4, trans(v, 4));
  std::string output = testing::internal::GetCapturedStdout();
  std::string errormsg = std::string("Failed to save the file.\n") + help_;
  EXPECT_EQ(output, errormsg);
}

  /// test missing parameter
TEST_F(CommandLineProcessorTest, noParameter) {
  std::vector<std::string> v =
    {"mia", "resources/city.png", "-threshold", "out.png"};
  testing::internal::CaptureStdout();
  cmd_->ProcessCommandLine(4, trans(v, 4));
  std::string output = testing::internal::GetCapturedStdout();
  std::string errormsg =
    std::string("Fails to find the float number parameter!\n") + help_;
  EXPECT_EQ(output, errormsg);
}

  /// test legal parameter, if it is a float
TEST_F(CommandLineProcessorTest, wrongParameter) {
  std::vector<std::string> v =
    {"mia", "resources/city.png", "-threshold", "a", "out1.png"};
  testing::internal::CaptureStdout();
  cmd_->ProcessCommandLine(5, trans(v, 5));
  std::string output = testing::internal::GetCapturedStdout();
  std::string errormsg =
    std::string("Fails to find the float number parameter!\n") + help_;
  EXPECT_EQ(output, errormsg);
}

  /// test legal parameter: if greater than 0
TEST_F(CommandLineProcessorTest, legalParameter) {
  std::vector<std::string> v =
    {"mia", "resources/city.png", "-threshold", "-2", "out1.png"};
  testing::internal::CaptureStdout();
  cmd_->ProcessCommandLine(5, trans(v, 5));
  std::string output = testing::internal::GetCapturedStdout();
  std::string errormsg =
    std::string("Invalid parameter!\n") + help_;
  EXPECT_EQ(output, errormsg);
}

  /// @brief For the overall commands tests, I try to compare two result
  /// pictures generated from running the ProcessorCommandLine functions and
  /// using ImageEditor objects

  /// test zero command
TEST_F(CommandLineProcessorTest, overallCommands) {
  std::vector<std::string> v =
    {"mia", "resources/tower.png", "resources/out.png"};
  cmd_->ProcessCommandLine(3, trans(v, 3));
  image_tools::PixelBuffer *out1 =
    new image_tools::PixelBuffer("resources/out.png");
  image_tools::PixelBuffer *in1 =
    new image_tools::PixelBuffer("resources/tower.png");
  EXPECT_TRUE(*out1 == *in1);
  delete out1;
  delete in1;
  out1 = NULL;
  in1 = NULL;
}

  /// test one command
TEST_F(CommandLineProcessorTest, overallCommands1) {
  std::vector<std::string> v1 =
    {"mia", "resources/test1.png", "-edgedetect", "resources/out1.png"};
  cmd_->ProcessCommandLine(4, trans(v1, 4));
  image_tools::PixelBuffer *show1 =
    new image_tools::PixelBuffer("resources/out1.png");
  /// output picture after executing the command line

  image1->ApplyEdgeDetectFilter();
  image_tools::PixelBuffer *show2 = image1->pixel_buffer();
  /// output after applying the filter using ImageEditor
  EXPECT_TRUE(*show1 == *show2);
  delete show1;
  show1 = NULL;
}

  /// test one commands
TEST_F(CommandLineProcessorTest, overallCommands2) {
  std::vector<std::string> v =
    {"mia", "resources/test1.png", "-blue", "0.5", "resources/out2.png"};
  cmd_->ProcessCommandLine(5, trans(v, 5));
  image_tools::PixelBuffer *show3 =
    new image_tools::PixelBuffer("resources/out2.png");
  /// output picture after executing the command line
  image1->ApplyChannelsFilter(1.0, 1.0, 0.5);
  image_tools::PixelBuffer *show4 = image1->pixel_buffer();
  /// output after applying the filter using ImageEditor
  EXPECT_TRUE(*show3 == *show4);
  delete show3;
  show3 = NULL;
}
  /// test two commands
TEST_F(CommandLineProcessorTest, overallCommands3) {
  std::vector<std::string> v =
    {"mia", "resources/test1.png", "-blur", "4", "-edgedetect", "resources/out3.png"};
  cmd_->ProcessCommandLine(6, trans(v, 6));
  image_tools::PixelBuffer *show5 =
    new image_tools::PixelBuffer("resources/out3.png");
  /// output picture after executing the command line
  image1->ApplyBlurFilter(4);
  image1->ApplyEdgeDetectFilter();
  image_tools::PixelBuffer *show6 = image1->pixel_buffer();
  /// output after applying the filter using ImageEditor
  EXPECT_TRUE(*show5 == *show6);
  delete show5;
  show5 = NULL;
}
