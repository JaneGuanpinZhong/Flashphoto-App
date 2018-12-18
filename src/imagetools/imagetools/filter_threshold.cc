/**
This file is part of the CSCI-3081W Project Code, which was developed
at the University of Minnesota.
Copyright (c) 2018 Jane/Guanpin Zhong at the University of Minnesota.
Original Author(s) of this File:
  Jane/Guanpin Zhong, 11/01/18, University of Minnesota
*/

#include "imagetools/filter_threshold.h"
#include <assert.h>
#include <algorithm>
#include <cmath>
#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {
  /// Constructor
  FilterThreshold::FilterThreshold(float v) {
    value_ = v;
  }

  /// constructor
  FilterThreshold::FilterThreshold() : value_(0.5) {}

  /// Nothing inside, as only useful for convolution filters.
  void FilterThreshold::SetupFilter() {}

  /// Nothing inside, as only useful for convolution filters.
  void FilterThreshold::CleanupFilter() {}

  /// Destructor
  FilterThreshold::~FilterThreshold() {}

  /// Return the color after changes.
  ColorData FilterThreshold::CalculaterFilteredPixel(PixelBuffer *buffer,
    int x, int y) {
    ColorData c = buffer->pixel(x, y);
    float avg = (c.red() + c.green() + c.blue()) / 3.0f;
    if (c.alpha() < 1.0) {
      ColorData c_bg = buffer->background_color();
      float avg_bg = (c_bg.red() + c_bg.green() + c_bg.blue()) / 3.0f;
      avg = avg * c.alpha() + avg_bg * (1.0 - c.alpha());
    }
    /// Deal with the alpha thing in particular.
    if (avg < value_) {
      return ColorData(0.0f, 0.0f, 0.0f);
    } else {
      return ColorData(1.0f, 1.0f, 1.0f);
    }
  }
}  /// namespace image_tools
