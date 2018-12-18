/// Copyright (c) 2015-2018 Daniel Keefe, TAs, & Regents of the University of
/// Minnesota.

#include <math.h>
#include <iostream>
#include "gtest/gtest.h"
#include "imagetools/tool_pen.h"

using image_tools::ToolPen;

class ToolPenTest : public ::testing::Test {
  void SetUp() override {}

 protected:
  ToolPen pen_;
};

TEST_F(ToolPenTest, HasCorrectName) {
  EXPECT_EQ(pen_.name(), "Pen");
}

TEST_F(ToolPenTest, HasCorrectMask) {
  /// Get Mask from pen and compare with
  /// what it is supposed to be.
}
