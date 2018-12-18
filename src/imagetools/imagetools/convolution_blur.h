/**
This file is part of the CSCI-3081W Project Code, which was developed
at the University of Minnesota.
Copyright (c) 2018 Jane/Guanpin Zhong at the University of Minnesota.
Original Author(s) of this File:
  Jane/Guanpin Zhong, 11/01/18, University of Minnesota
*/

#ifndef IMAGETOOLS_CONVOLUTION_BLUR_H_
#define IMAGETOOLS_CONVOLUTION_BLUR_H_

#include "imagetools/convolution.h"
#include <cmath>
#include <cstdlib>
#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {
  /** @brief Main purpose:
  Use a Gaussian Blur image convolution kernel to blur the image in
  proportion to the amount specified in the GUI. */
class ConvolutionFilterBlur: public ConvolutionFilter {
 public:
  /// Default constructor
  ConvolutionFilterBlur();
  /// Constructor
  explicit ConvolutionFilterBlur(float r);
  /// Destructor
  virtual ~ConvolutionFilterBlur();

  /** Override the function from supper class.
  Computer the kernel for Gaussian blur. */
  FloatMatrix* CreateKernel() override;

 private:
  float radius_;
};
}  /// namespace image_tools

#endif  // IMAGETOOLS_CONVOLUTION_BLUR_H_
