/**
This file is part of the CSCI-3081W Project Code, which was developed
at the University of Minnesota.
Copyright (c) 2018 Jane/Guanpin Zhong at the University of Minnesota.
Original Author(s) of this File:
  Jane/Guanpin Zhong, 11/01/18, University of Minnesota
*/

#ifndef IMAGETOOLS_CONVOLUTION_EDGE_H_
#define IMAGETOOLS_CONVOLUTION_EDGE_H_

#include "imagetools/convolution.h"
#include <cmath>
#include <cstdlib>
#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {
  /// @brief Main purpose:
  /// Transform the image into one that only shows the edges of shapes by
  /// convolving it with a 3x3 edge detection kernel. Pixels on the border
  /// of differently colored regions will be bright, while pixels in areas
  /// of low change will be dark.
class ConvolutionFilterEdge: public ConvolutionFilter {
 public:
  /// Default constructor
  ConvolutionFilterEdge();
  /// Destructor
  virtual ~ConvolutionFilterEdge();

  /** @brief Override the function from super class.
  Create a fixed 3*3 kernel for this filter.
  Used to only show edges of shapes by convoving it with a 3x3
  edge detection kernel, making borders of differently colored
  region bright, and pixels in low change areas dark. */
  FloatMatrix* CreateKernel() override;
};
}  /// namespace image_tools

#endif  // IMAGETOOLS_CONVOLUTION_EDGE_H_
