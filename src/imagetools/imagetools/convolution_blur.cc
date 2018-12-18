/**
This file is part of the CSCI-3081W Project Code, which was developed
at the University of Minnesota.
Copyright (c) 2018 Jane/Guanpin Zhong at the University of Minnesota.
Original Author(s) of this File:
  Jane/Guanpin Zhong, 11/01/18, University of Minnesota
*/

#include "imagetools/convolution_blur.h"
#include <cmath>
#include <cstdlib>
#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"
#include "imagetools/image_tools_math.h"


namespace image_tools {
  /// Default constructor
  ConvolutionFilterBlur::ConvolutionFilterBlur() {
      radius_ = 1.0;
    }

  /// Constructor. Set the radius as user input.
  ConvolutionFilterBlur::ConvolutionFilterBlur(float r) {
    radius_ = r;
  }

  /// Destructor
  ConvolutionFilterBlur::~ConvolutionFilterBlur() {}

  /// Computer the kernel for Gaussian blur
  FloatMatrix* ConvolutionFilterBlur::CreateKernel() {
    FloatMatrix* kernel =
      new FloatMatrix(round(radius_ * 2.0) + 1, round(radius_ * 2.0) + 1);

    for (int j = 0; j < kernel->height(); j++) {
      for (int i = 0; i < kernel->width(); i++) {
        int x = i - kernel->width() / 2;
        int y = j - kernel->height() / 2;
        float dist = sqrt(x * x + y * y);
        float intensity = ImageToolsMath::Gaussian(dist, radius_);
        kernel->set_value(i, j, intensity);
      }
    }
    kernel->Normalize();

    return kernel;
  }
}  /// namespace image_tools
