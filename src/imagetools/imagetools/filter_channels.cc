/**
This file is part of the CSCI-3081W Project Code, which was developed
at the University of Minnesota.
Copyright (c) 2018 Jane/Guanpin Zhong at the University of Minnesota.
Original Author(s) of this File:
  Jane/Guanpin Zhong, 11/01/18, University of Minnesota
*/

#include "imagetools/filter_channels.h"
#include <cmath>
#include <cstdlib>
#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {
  /// Default constructor
  FilterChannel::FilterChannel() {
    r_ = 1.0;
    g_ = 1.0;
    b_ = 1.0;
  }

  /// Constructor
  FilterChannel::FilterChannel(float r, float g, float b) {
      r_ = r;
      g_ = g;
      b_ = b;
  }

  /// Destructor
  FilterChannel::~FilterChannel() {}

  /// Nothing inside, as only useful for convolution filters.
  void FilterChannel::SetupFilter() {}

  /// Nothing inside, as only useful for convolution filters.
  void FilterChannel::CleanupFilter() {}

  /** @brief
  Return the pixel after changing the color, through multiplying
  given input scale values and original color values.
  */
  ColorData FilterChannel::CalculaterFilteredPixel(PixelBuffer* buffer,
    int x, int y) {
    ColorData color = buffer->pixel(x, y);
    /// Multiply the scale values and original values of color
    color.set_red(color.red()*r_);
    color.set_green(color.green()*g_);
    color.set_blue(color.blue()*b_);
    color.Clamp();  /// Make color values within the range (0,1).
    return color;
    }
}  /// namespace image_tools
