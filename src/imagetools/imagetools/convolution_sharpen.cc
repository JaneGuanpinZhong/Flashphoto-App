/**
This file is part of the CSCI-3081W Project Code, which was developed
at the University of Minnesota.
Copyright (c) 2018 Jane/Guanpin Zhong at the University of Minnesota.
Original Author(s) of this File:
  Jane/Guanpin Zhong, 11/01/18, University of Minnesota
*/

#include "imagetools/convolution_sharpen.h"
#include <cmath>
#include <cstdlib>
#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"
#include "imagetools/image_tools_math.h"

namespace image_tools {
  /// Constructor
  ConvolutionFilterSharpen::ConvolutionFilterSharpen() : rad_(5.0) {}

  /// Constructor
  ConvolutionFilterSharpen::ConvolutionFilterSharpen(float rad) {
    rad_ = rad;
  }

  /// Destructor
  ConvolutionFilterSharpen::~ConvolutionFilterSharpen() {}

  /** @brief
  Only the central pixel has a value equal to the number of
  pixels inside the kernel, other pixels are all -1.0. */
  FloatMatrix* ConvolutionFilterSharpen::CreateKernel() {
    FloatMatrix* kernel =
    new FloatMatrix(round(rad_ * 2.0) + 1, round(rad_ * 2.0) + 1);

    for (int j = 0; j < kernel->height(); j++) {
      for (int i = 0; i < kernel->width(); i++) {
        int x = i - kernel->width() / 2;
        int y = j - kernel->height() / 2;
        float dist = sqrt(x * x + y * y);
        float intensity = ImageToolsMath::Gaussian(dist, rad_);
        kernel->set_value(i, j, intensity);
      }
    }
    kernel->Normalize();

    /// Negate all the values
    kernel->Scale(-1.0);

    /// Add two to the middle
    float middle_value = kernel->value(kernel->width() / 2,
    kernel->height() / 2);
    kernel->set_value(kernel->width() / 2, kernel->height() / 2,
                      middle_value + 2.0);

    return kernel;
  }
}  /// namespace image_tools
