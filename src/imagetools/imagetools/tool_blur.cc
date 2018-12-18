/**
This file is part of the CSCI-3081W Project Support Code, which was developed
at the University of Minnesota.

This code is to be used for student coursework.  It is not an open source
project.
Copyright (c) 2015-2018 Daniel Keefe, TAs, & Regents of the University of
Minnesota.

Original Author(s) of this File:
  Seth Johnson, 4/4/2015, University of Minnesota

Author(s) of Significant Updates/Modifications to the File:
  Jane/Guanpin Zhong, 2018, UMN
*/

#include "imagetools/tool_blur.h"
#include "imagetools/mask_factory.h"

namespace image_tools {
  /// Constructor
ToolBlur::ToolBlur() {
  /// Set up a blur filter to use a radius of 5.0 here
  filter_ = new ConvolutionFilterBlur(5.0);
  filter_->SetupFilter();
  /** @brief
  The blur operation is not fast, so space the repeated applications of the
  stamp out as far as we can get away with while still having it look good
  1/3 overlap is pretty good for this. */
  stamp_overlap_ = 0.333;
}

ToolBlur::~ToolBlur() {
  /// Cleanup the filter here if needed.
  filter_->CleanupFilter();
  delete filter_;
  filter_ = NULL;
}

FloatMatrix* ToolBlur::CreateMask(float radius) {
  return MaskFactory::CreateLinearFalloffMask(radius);
}

ColorData ToolBlur::LookupPaintColor(int x, int y) {
  /** @brief
  The hook to calculate a filtered version of the
  pixel. Use your filter to compute the blurred version of the pixel at (x,y)
  in *buffer_ and return the new color to make this tool work.
  */
  ColorData color = filter_->CalculaterFilteredPixel(buffer_, x, y);
  return color;
}

} /* namespace image_tools */
