/**
This file is part of the CSCI-3081W Project Code, which was developed
at the University of Minnesota.
Copyright (c) 2018 Jane/Guanpin Zhong at the University of Minnesota.
Original Author(s) of this File:
  Jane/Guanpin Zhong, 11/01/18, University of Minnesota
*/

#include "imagetools/convolution_edge.h"
#include <cmath>
#include <cstdlib>
#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"
#include "imagetools/image_tools_math.h"

namespace image_tools {
  /// Default constructor. No real use.
  ConvolutionFilterEdge::ConvolutionFilterEdge() {}

  /// Destructor
  ConvolutionFilterEdge::~ConvolutionFilterEdge() {}

  /** @brief It is fixed 3*3 matrix, unlike kernels for other filters.
  Except the central pixel with value 8.0, others are all -1.0 */
  FloatMatrix* ConvolutionFilterEdge::CreateKernel() {
    FloatMatrix *fm = new FloatMatrix(3, 3);
    fm->Scale(-1.0);
    fm->set_value(1, 1, 8.0);
    return fm;
  }

}  /// namespace image_tools
