/**
This file is part of the CSCI-3081W Project Code, which was developed
at the University of Minnesota.
Copyright (c) 2018 Jane/Guanpin Zhong at the University of Minnesota.
Original Author(s) of this File:
  Jane/Guanpin Zhong, 11/14/18, University of Minnesota
*/

/** @brief
Basic idea or regression tests:
  In each test for different filters or tools, I check if there is already one
  file applied by them. If no, then I just create it, and it just becomes the
  my ground-truth picture. After that, every time I try to run that command, so
  I already have a "standard", which is the ground-truth picture. I just create
  a new one and compare it with my ground-truth one. If they match, then the
  test is successful.
*/

#include <iostream>
#include "gtest/gtest.h"
#include <mingfx.h>
#include <string>
#include <vector>
#include <map>

#include "imagetools/image_editor.h"
#include "imagetools/pixel_buffer.h"
#include "imagetools/color_data.h"

using image_tools::ImageEditor;

class RegressionTest : public ::testing::Test {
  void SetUp() override {
    image_tools::PixelBuffer* test1 = new image_tools::PixelBuffer("resources/test1.png");
    image1 = new ImageEditor(test1);
    image_tools::PixelBuffer* test2 = new image_tools::PixelBuffer("resources/test2.png");
    image2 = new ImageEditor(test2);
    image_tools::PixelBuffer* test3 = new image_tools::PixelBuffer("resources/test3.png");
    image3 = new ImageEditor(test3);
  }

  void TearDown() override {
    delete image1;
    image1 = NULL;
    delete image2;
    image2 = NULL;
    delete image3;
    image3 = NULL;
  }

 protected:
  ImageEditor *image1;
  ImageEditor *image2;
  ImageEditor *image3;
  image_tools::ToolBlur tBlur_;
  image_tools::ToolCalligraphyPen tcPen_;
  image_tools::ToolChalk tChalk_;
  image_tools::ToolEraser tEraser_;
  image_tools::ToolHighlighter tHighlighter_;
  image_tools::ToolPen tPen_;
  image_tools::ToolSprayCan tSpray_can_;
  image_tools::ToolStamp tStamp_;
};

  /// Tests for filters are below.
TEST_F(RegressionTest, FilterThresholdTest) {
  image_tools::PixelBuffer try1 =
    image_tools::PixelBuffer(*image2->pixel_buffer());
  image2->ApplyThresholdFilter(0.45);
  image_tools::PixelBuffer *try2 = image2->pixel_buffer();
  /// output after applying the filter
  std::string name = "resources/filter_test_threshold_out.png";
  if (mingfx::Platform::FileExists(name)) {
    try1 = image_tools::PixelBuffer(name);
} else {
    std::cout << "Create new" << std::endl;
    image2->SaveToFile(name);
    try1 = image_tools::PixelBuffer(name);
}
  EXPECT_TRUE(try1 == *try2);
}

TEST_F(RegressionTest, FilterChannelsTest1) {
  image_tools::PixelBuffer try1 =
    image_tools::PixelBuffer(*image2->pixel_buffer());
  image2->ApplyChannelsFilter(2.7, 1.0, 1.0);
  image_tools::PixelBuffer *try2 = image2->pixel_buffer();
  /// output after applying the filter
  std::string name = "resources/filter_test_channels_out1.png";
  if (mingfx::Platform::FileExists(name)) {
    try1 = image_tools::PixelBuffer(name);
} else {
    std::cout << "Create new" << std::endl;
    image2->SaveToFile(name);
    std::cout << "here?" << std::endl;
    try1 = image_tools::PixelBuffer(name);
}
  EXPECT_TRUE(try1 == *try2);
}

TEST_F(RegressionTest, FilterChannelsTest2) {
  image_tools::PixelBuffer try1 =
    image_tools::PixelBuffer(*image2->pixel_buffer());
  image2->ApplyChannelsFilter(1.0, 3.8, 1.0);
  image_tools::PixelBuffer *try2 = image2->pixel_buffer();
  /// output after applying the filter
  std::string name = "resources/filter_test_channels_out2.png";
  if (mingfx::Platform::FileExists(name)) {
    try1 = image_tools::PixelBuffer(name);
} else {
    std::cout << "Create new" << std::endl;
    image2->SaveToFile(name);
    try1 = image_tools::PixelBuffer(name);
}
  EXPECT_TRUE(try1 == *try2);
}

TEST_F(RegressionTest, FilterChannelsTest3) {
  image_tools::PixelBuffer try1 =
    image_tools::PixelBuffer(*image2->pixel_buffer());
  image2->ApplyChannelsFilter(1.0, 1.0, 4.6);
  image_tools::PixelBuffer *try2 = image2->pixel_buffer();
  /// output after applying the filter
  std::string name = "resources/filter_test_channels_out3.png";
  if (mingfx::Platform::FileExists(name)) {
    try1 = image_tools::PixelBuffer(name);
} else {
    std::cout << "Create new" << std::endl;
    image2->SaveToFile(name);
    try1 = image_tools::PixelBuffer(name);
}
  EXPECT_TRUE(try1 == *try2);
}

TEST_F(RegressionTest, FilterQuantizeTest) {
  image_tools::PixelBuffer try1 =
    image_tools::PixelBuffer(*image2->pixel_buffer());
  image2->ApplyQuantizeFilter(4);
  image_tools::PixelBuffer *try2 = image2->pixel_buffer();
  /// output after applying the filter
  std::string name = "resources/filter_test_quantize_out.png";
  if (mingfx::Platform::FileExists(name)) {
    try1 = image_tools::PixelBuffer(name);
} else {
    std::cout << "Create new" << std::endl;
    image2->SaveToFile(name);
    try1 = image_tools::PixelBuffer(name);
}
  EXPECT_TRUE(try1 == *try2);
}

TEST_F(RegressionTest, FilterSaturateTest) {
  image_tools::PixelBuffer try1 =
    image_tools::PixelBuffer(*image2->pixel_buffer());
  image2->ApplySaturateFilter(6.6);
  image_tools::PixelBuffer *try2 = image2->pixel_buffer();
  /// output after applying the filter
  std::string name = "resources/filter_test_saturate_out.png";
  if (mingfx::Platform::FileExists(name)) {
    try1 = image_tools::PixelBuffer(name);
} else {
    std::cout << "Create new" << std::endl;
    image2->SaveToFile(name);
    try1 = image_tools::PixelBuffer(name);
}
  EXPECT_TRUE(try1 == *try2);
}

TEST_F(RegressionTest, FilterBlurTest) {
  image_tools::PixelBuffer try1 =
    image_tools::PixelBuffer(*image2->pixel_buffer());
  image2->ApplyBlurFilter(5.0);
  image_tools::PixelBuffer *try2 = image2->pixel_buffer();
  /// output after applying the filter
  std::string name = "resources/cfilter_test_blur_out.png";
  if (mingfx::Platform::FileExists(name)) {
    try1 = image_tools::PixelBuffer(name);
} else {
    std::cout << "Create new" << std::endl;
    image2->SaveToFile(name);
    try1 = image_tools::PixelBuffer(name);
}
  EXPECT_TRUE(try1 == *try2);
}

TEST_F(RegressionTest, FilterEdgedetectTest) {
  image_tools::PixelBuffer try1 =
    image_tools::PixelBuffer(*image3->pixel_buffer());
  image3->ApplyEdgeDetectFilter();
  image_tools::PixelBuffer *try2 = image3->pixel_buffer();
  /// output after applying the filter
  std::string name = "resources/cfilter_test_edge_out.png";
  if (mingfx::Platform::FileExists(name)) {
    try1 = image_tools::PixelBuffer(name);
} else {
    std::cout << "Create new" << std::endl;
    image3->SaveToFile(name);
    try1 = image_tools::PixelBuffer(name);
}
  EXPECT_TRUE(try1 == *try2);
}

TEST_F(RegressionTest, FilterSharpenTest) {
  image_tools::PixelBuffer try1 =
    image_tools::PixelBuffer(*image3->pixel_buffer());
  image3->ApplySharpenFilter(3.0);
  image_tools::PixelBuffer *try2 = image3->pixel_buffer();
  /// output after applying the filter
  std::string name = "resources/cfilter_test_sharpen_out.pn";
  if (mingfx::Platform::FileExists(name)) {
    try1 = image_tools::PixelBuffer(name);
} else {
    std::cout << "Create new" << std::endl;
    image3->SaveToFile(name);
    try1 = image_tools::PixelBuffer(name);
}
  EXPECT_TRUE(try1 == *try2);
}

TEST_F(RegressionTest, FilterMotionBlurTestNS) {
  image_tools::PixelBuffer try1 =
    image_tools::PixelBuffer(*image3->pixel_buffer());
  image_tools::ConvolutionFilterMotionBlur::MBlurDir dir_ =
    image_tools::ConvolutionFilterMotionBlur::MBLUR_DIR_N_S;
  image3->ApplyMotionBlurFilter(4.0, dir_);
  image_tools::PixelBuffer *try2 = image3->pixel_buffer();
  /// output after applying the filter
  std::string name = "resources/cfilter_test_ns_out.png";
  if (mingfx::Platform::FileExists(name)) {
    try1 = image_tools::PixelBuffer(name);
} else {
    std::cout << "Create new" << std::endl;
    image3->SaveToFile(name);
    try1 = image_tools::PixelBuffer(name);
}
  EXPECT_TRUE(try1 == *try2);
}

TEST_F(RegressionTest, FilterMotionBlurTestEW) {
  image_tools::PixelBuffer try1 =
    image_tools::PixelBuffer(*image3->pixel_buffer());
  image_tools::ConvolutionFilterMotionBlur::MBlurDir dir_ =
    image_tools::ConvolutionFilterMotionBlur::MBLUR_DIR_E_W;
  image3->ApplyMotionBlurFilter(4.0, dir_);
  image_tools::PixelBuffer *try2 = image3->pixel_buffer();
  /// output after applying the filter
  std::string name = "resources/cfilter_test_ew_out.png";
  if (mingfx::Platform::FileExists(name)) {
    try1 = image_tools::PixelBuffer(name);
} else {
    std::cout << "Create new" << std::endl;
    image3->SaveToFile(name);
    try1 = image_tools::PixelBuffer(name);
}
  EXPECT_TRUE(try1 == *try2);
}

TEST_F(RegressionTest, FilterMotionBlurTestNESW) {
  image_tools::PixelBuffer try1 =
    image_tools::PixelBuffer(*image3->pixel_buffer());
  image_tools::ConvolutionFilterMotionBlur::MBlurDir dir_ =
    image_tools::ConvolutionFilterMotionBlur::MBLUR_DIR_NE_SW;
  image3->ApplyMotionBlurFilter(4.0, dir_);
  image_tools::PixelBuffer *try2 = image3->pixel_buffer();
  /// output after applying the filter
  std::string name = "resources/cfilter_test_nesw_out.png";
  if (mingfx::Platform::FileExists(name)) {
    try1 = image_tools::PixelBuffer(name);
} else {
    std::cout << "Create new" << std::endl;
    image3->SaveToFile(name);
    try1 = image_tools::PixelBuffer(name);
}
  EXPECT_TRUE(try1 == *try2);
}

TEST_F(RegressionTest, FilterMotionBlurTestNWSE) {
  image_tools::PixelBuffer try1 =
    image_tools::PixelBuffer(*image3->pixel_buffer());
  image_tools::ConvolutionFilterMotionBlur::MBlurDir dir_ =
    image_tools::ConvolutionFilterMotionBlur::MBLUR_DIR_NW_SE;
  image3->ApplyMotionBlurFilter(4.0, dir_);
  image_tools::PixelBuffer *try2 = image3->pixel_buffer();
  /// output after applying the filter
  std::string name = "resources/cfilter_test_nwse_out.png";
  if (mingfx::Platform::FileExists(name)) {
    try1 = image_tools::PixelBuffer(name);
} else {
    std::cout << "Create new" << std::endl;
    image3->SaveToFile(name);
    try1 = image_tools::PixelBuffer(name);
}
  EXPECT_TRUE(try1 == *try2);
}

/// Tests for tools are below.
TEST_F(RegressionTest, FilterToolBlurTest) {
  image_tools::PixelBuffer try1 =
    image_tools::PixelBuffer(*image1->pixel_buffer());
  image_tools::ColorData color = image_tools::ColorData(0.8, 0.2, 0.2);
  image1->StartStroke(tBlur_.name(), color, 4, 20, 20);
  for (int i = 21; i < 200; i++) {
    image1->AddToStroke(i, i);
  }
  image1->EndStroke(200, 200);
  image_tools::PixelBuffer *try2 = image1->pixel_buffer();
  /// output after applying the filter
  std::string name = "resources/tool_test_blur_out.png";
  if (mingfx::Platform::FileExists(name)) {
    try1 = image_tools::PixelBuffer(name);
} else {
    std::cout << "Create new" << std::endl;
    image1->SaveToFile(name);
    try1 = image_tools::PixelBuffer(name);
}
  EXPECT_TRUE(try1 == *try2);
}

TEST_F(RegressionTest, FilterToolPenTest) {
  image_tools::PixelBuffer try1 =
    image_tools::PixelBuffer(*image1->pixel_buffer());
  image_tools::ColorData color = image_tools::ColorData(0.8, 0.2, 0.2);
  image1->StartStroke(tPen_.name(), color, 4, 20, 20);
  for (int i = 21; i < 200; i++) {
    image1->AddToStroke(i, i);
  }
  image1->EndStroke(200, 200);
  image_tools::PixelBuffer *try2 = image1->pixel_buffer();
  /// output after applying the filter
  std::string name = "resources/tool_test_pen_out.pn";
  if (mingfx::Platform::FileExists(name)) {
    try1 = image_tools::PixelBuffer(name);
} else {
    std::cout << "Create new" << std::endl;
    image1->SaveToFile(name);
    try1 = image_tools::PixelBuffer(name);
}
  EXPECT_TRUE(try1 == *try2);
}

TEST_F(RegressionTest, FilterCalligraphyPenTest) {
  image_tools::PixelBuffer try1 =
    image_tools::PixelBuffer(*image1->pixel_buffer());
  image_tools::ColorData color = image_tools::ColorData(0.8, 0.2, 0.2);
  image1->StartStroke(tcPen_.name(), color, 4, 20, 20);
  for (int i = 21; i < 200; i++) {
    image1->AddToStroke(i, i);
  }
  image1->EndStroke(200, 200);
  image_tools::PixelBuffer *try2 = image1->pixel_buffer();
  /// output after applying the filter
  std::string name = "resources/tool_test_calpen_out.pn";
  if (mingfx::Platform::FileExists(name)) {
    try1 = image_tools::PixelBuffer(name);
} else {
    std::cout << "Create new" << std::endl;
    image1->SaveToFile(name);
    try1 = image_tools::PixelBuffer(name);
}
  EXPECT_TRUE(try1 == *try2);
}

  /// Chalk is a little special, where we need to set seed, in order to
  /// draw the same thing every time we run it, instead of random seed.
TEST_F(RegressionTest, ToolChalkTest) {
  image_tools::PixelBuffer try1 =
    image_tools::PixelBuffer(*image1->pixel_buffer());
  image_tools::ColorData color = image_tools::ColorData(0.8, 0.2, 0.2);
  tChalk_.setSeed(1);
  image1->StartStroke(tChalk_.name(), color, 4, 20, 20);
  for (int i = 21; i < 200; i++) {
    image1->AddToStroke(i, i);
  }
  image1->EndStroke(200, 200);
  image_tools::PixelBuffer *try2 = image1->pixel_buffer();
  /// output after applying the filter
  std::string name = "resources/tool_test_chalk_out.pn";
  if (mingfx::Platform::FileExists(name)) {
    try1 = image_tools::PixelBuffer(name);
} else {
    std::cout << "Create new" << std::endl;
    image1->SaveToFile(name);
    try1 = image_tools::PixelBuffer(name);
}
  EXPECT_TRUE(try1 == *try2);
}

TEST_F(RegressionTest, ToolSprayCanTest) {
  image_tools::PixelBuffer try1 =
    image_tools::PixelBuffer(*image1->pixel_buffer());
  image_tools::ColorData color = image_tools::ColorData(0.8, 0.2, 0.2);
  image1->StartStroke(tSpray_can_.name(), color, 4, 20, 20);
  for (int i = 21; i < 200; i++) {
    image1->AddToStroke(i, i);
  }
  image1->EndStroke(200, 200);
  image_tools::PixelBuffer *try2 = image1->pixel_buffer();
  /// output after applying the filter
  std::string name = "resources/tool_test_spraycan_out.pn";
  if (mingfx::Platform::FileExists(name)) {
    try1 = image_tools::PixelBuffer(name);
} else {
    std::cout << "Create new" << std::endl;
    image1->SaveToFile(name);
    try1 = image_tools::PixelBuffer(name);
}
  EXPECT_TRUE(try1 == *try2);
}

TEST_F(RegressionTest, ToolHighlighterTest) {
  image_tools::PixelBuffer try1 =
    image_tools::PixelBuffer(*image1->pixel_buffer());
  image_tools::ColorData color = image_tools::ColorData(0.8, 0.2, 0.2);
  image1->StartStroke(tHighlighter_.name(), color, 4, 20, 20);
  for (int i = 21; i < 200; i++) {
    image1->AddToStroke(i, i);
  }
  image1->EndStroke(200, 200);
  image_tools::PixelBuffer *try2 = image1->pixel_buffer();
  /// output after applying the filter
  std::string name = "resources/tool_test_highlighter_out.pn";
  if (mingfx::Platform::FileExists(name)) {
    try1 = image_tools::PixelBuffer(name);
} else {
    std::cout << "Create new" << std::endl;
    image1->SaveToFile(name);
    try1 = image_tools::PixelBuffer(name);
}
  EXPECT_TRUE(try1 == *try2);
}

TEST_F(RegressionTest, ToolStampTest) {
  image_tools::PixelBuffer try1 =
    image_tools::PixelBuffer(*image1->pixel_buffer());
  image_tools::ColorData color = image_tools::ColorData(0.8, 0.2, 0.2);
  image1->StartStroke(tStamp_.name(), color, 4, 20, 20);
  for (int i = 21; i < 200; i++) {
    image1->AddToStroke(i, i);
  }
  image1->EndStroke(200, 200);
  image_tools::PixelBuffer *try2 = image1->pixel_buffer();
  /// output after applying the filter
  std::string name = "resources/tool_test_stamp_out.pn";
  if (mingfx::Platform::FileExists(name)) {
    try1 = image_tools::PixelBuffer(name);
} else {
    std::cout << "Create new" << std::endl;
    image1->SaveToFile(name);
    try1 = image_tools::PixelBuffer(name);
}
  EXPECT_TRUE(try1 == *try2);
}

TEST_F(RegressionTest, ToolEraserTest) {
  image_tools::PixelBuffer try1 =
    image_tools::PixelBuffer(*image1->pixel_buffer());
  image_tools::ColorData color = image_tools::ColorData(0.8, 0.2, 0.2);
  image1->StartStroke(tEraser_.name(), color, 4, 20, 20);
  for (int i = 21; i < 200; i++) {
    image1->AddToStroke(i, i);
  }
  image1->EndStroke(200, 200);
  image_tools::PixelBuffer *try2 = image1->pixel_buffer();
  /// output after applying the filter
  std::string name = "resources/tool_test_eraser_out.pn";
  if (mingfx::Platform::FileExists(name)) {
    try1 = image_tools::PixelBuffer(name);
} else {
    std::cout << "Create new" << std::endl;
    image1->SaveToFile(name);
    try1 = image_tools::PixelBuffer(name);
}
  EXPECT_TRUE(try1 == *try2);
}
