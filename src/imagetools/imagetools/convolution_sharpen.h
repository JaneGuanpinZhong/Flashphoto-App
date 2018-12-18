/**
This file is part of the CSCI-3081W Project Code, which was developed
at the University of Minnesota.
Copyright (c) 2018 Jane/Guanpin Zhong at the University of Minnesota.
Original Author(s) of this File:
  Jane/Guanpin Zhong, 11/01/18, University of Minnesota
*/

#ifndef IMAGETOOLS_CONVOLUTION_SHARPEN_H_
#define IMAGETOOLS_CONVOLUTION_SHARPEN_H_

#include "imagetools/convolution.h"
#include <cmath>
#include <cstdlib>
#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {
  /** @brief
  Main purpose:
  Sharpen the image (accentuate the edges of shapes) in proportion to the
  amount specifies in the GUI by convolving the image with an appropriate
  sharpening kernel.
  */
class ConvolutionFilterSharpen: public ConvolutionFilter {
 public:
  ConvolutionFilterSharpen();
  explicit ConvolutionFilterSharpen(float r);  /// Constructor
  virtual ~ConvolutionFilterSharpen();  /// Destructor

  /** @brief
  Override the function from super class. Create the kernel for
  the sharpen filter, through accentuating the edges of shapes. */
  FloatMatrix* CreateKernel() override;

 private:
  float rad_;
};
}  /// namespace image_tools

#endif  // IMAGETOOLS_CONVOLUTION_SHARPEN_H_
