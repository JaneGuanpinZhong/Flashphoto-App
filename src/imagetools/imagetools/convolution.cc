/**
This file is part of the CSCI-3081W Project Code, which was developed
at the University of Minnesota.
Copyright (c) 2018 Jane/Guanpin Zhong at the University of Minnesota.
Original Author(s) of this File:
  Jane/Guanpin Zhong, 11/01/18, University of Minnesota
*/

#include "imagetools/convolution.h"
#include <cstdlib>
#include <cmath>
#include "imagetools/filter.h"
#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"
#include "imagetools/image_tools_math.h"

namespace image_tools {
    /// Default constructor
    ConvolutionFilter::ConvolutionFilter() {}

    /// Destructor
    ConvolutionFilter::~ConvolutionFilter() {}

    /// Set the value the private variable kernel_ points to as what we get
    /// from CreateKernel(), and then normalize it, which is very important.
    void ConvolutionFilter::SetupFilter() {
      kernel_ = CreateKernel();
    }

    /** @brief
    Apply the kernel to a specific position on canvas, through special
    calculating methods. See details below.
    */
    ColorData ConvolutionFilter::CalculaterFilteredPixel(PixelBuffer *buffer,
      int x, int y) {
      int half_width = kernel_->width() / 2;
      int half_height = kernel_->height() / 2;
      int buffer_width = buffer->width();
      int buffer_height = buffer->height();
      ColorData result(0, 0, 0, buffer->pixel(x, y).alpha());

    #pragma omp for
      for (int i = 0; i < kernel_->width(); i++) {
        for (int j = 0; j < kernel_->height(); j++) {
          int c_x = x + i - half_width;
          int c_y = y + j - half_height;
          c_y = ImageToolsMath::Clamp(c_y, 0, buffer_height - 1);
          c_x = ImageToolsMath::Clamp(c_x, 0, buffer_width - 1);

          ColorData original = buffer->pixel(c_x, c_y);
          float a = original.alpha();
          ColorData premult = original * a;
          premult.set_alpha(a);

          ColorData weight = premult * kernel_->value(i, j);
          if (!convolve_alpha()) {
            weight.set_alpha(a);
          }
          result = result + weight;
        }
      }
      result.Clamp();
      return result;
    }

    /// After use, we delete the pointer and make it point to NULL
    void ConvolutionFilter::CleanupFilter() {
      delete kernel_;
      kernel_ = NULL;
    }

    /** @brief
    The default value of this function for convolution filters
    is false, so later we have to copy the pointer.
    */
    bool ConvolutionFilter::can_copy_in_place() {
      return false;
    }

    bool ConvolutionFilter::convolve_alpha() const { return false; }

  }  /// namespace image_tools
