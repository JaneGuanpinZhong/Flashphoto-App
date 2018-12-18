/**
This file is part of the CSCI-3081W Project Code, which was developed
at the University of Minnesota.
Copyright (c) 2018 Jane/Guanpin Zhong at the University of Minnesota.
Original Author(s) of this File:
  Jane/Guanpin Zhong, 11/01/18, University of Minnesota
*/

#ifndef IMAGETOOLS_CONVOLUTION_MOTIONBLUR_H_
#define IMAGETOOLS_CONVOLUTION_MOTIONBLUR_H_

#include "imagetools/convolution.h"
#include <cmath>
#include <cstdlib>
#include <map>
#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"
#include "imagetools/float_matrix.h"

namespace image_tools {
  /** @brief
  Main purpose:
  Blur the image by convolving it with an appropriate motion-blurring kernel
  Support four possible blurring direstions and blur according to the amount
  specifies in the GUI.
  */
class ConvolutionFilterMotionBlur: public ConvolutionFilter {
 public:
  /// Define an enum type
  enum MBlurDir { MBLUR_DIR_N_S, MBLUR_DIR_E_W, MBLUR_DIR_NE_SW,
          MBLUR_DIR_NW_SE };
  /// Define a variable representing the direction
  MBlurDir dir_;

  /// constructor
  ConvolutionFilterMotionBlur();

  /// Constructor
  ConvolutionFilterMotionBlur(float rad, MBlurDir dir);
  /// Destructor
  virtual ~ConvolutionFilterMotionBlur();

  /** @brief
  Override the function from super class. Create a kernel for
  MotionBlur filter, based on input parameters. The direction
  decides which way there is non=zero values, and radius decides
  what how big the kernel will be. */
  FloatMatrix* CreateKernel() override;

 private:
  float rad_;
};
}  /// namespace image_tools

#endif  // IMAGETOOLS_CONVOLUTION_MOTIONBLUR_H_
