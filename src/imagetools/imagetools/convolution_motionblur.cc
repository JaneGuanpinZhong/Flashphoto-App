/**
This file is part of the CSCI-3081W Project Code, which was developed
at the University of Minnesota.
Copyright (c) 2018 Jane/Guanpin Zhong at the University of Minnesota.
Original Author(s) of this File:
  Jane/Guanpin Zhong, 11/01/18, University of Minnesota
*/

#include "imagetools/convolution_motionblur.h"
#include <cmath>
#include <cstdlib>
#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"
#include "imagetools/image_tools_math.h"
#include "imagetools/float_matrix.h"

namespace image_tools {
  // constructor
  ConvolutionFilterMotionBlur::ConvolutionFilterMotionBlur() {
    rad_ = 5.0;
    dir_ = MBLUR_DIR_N_S;
  }

  /// Constructor
  ConvolutionFilterMotionBlur::ConvolutionFilterMotionBlur(float rad,
    MBlurDir dir) {
    rad_ = rad;
    dir_ = dir;
  }

  /// Destructor
  ConvolutionFilterMotionBlur::~ConvolutionFilterMotionBlur() {}

  /// Create the kernel for MotionBlur filter.
  FloatMatrix* ConvolutionFilterMotionBlur::CreateKernel() {
    FloatMatrix* kernel =
      new FloatMatrix(round(rad_ * 2.0) + 1, round(rad_ * 2.0) + 1);

    for (int j = 0; j < kernel->height(); j++) {
      for (int i = 0; i < kernel->width(); i++) {
        int x = i - kernel->width() / 2;
        int y = j - kernel->height() / 2;

        float intensity = 0.0;
        switch (dir_) {
          case MBLUR_DIR_N_S:
            intensity = (x == 0) ? 1 : 0;
            break;
          case MBLUR_DIR_E_W:
            intensity = (y == 0) ? 1 : 0;
            break;
          case MBLUR_DIR_NE_SW:
            intensity = (y == -x) ? 1 : 0;
            break;
          case MBLUR_DIR_NW_SE:
            intensity = (y == x) ? 1 : 0;
            break;
          default:
            break;
        }
        kernel->set_value(i, j, intensity);
      }
    }
    kernel->Normalize();

    return kernel;
  }

}  /// namespace image_tools
