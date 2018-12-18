/**
This file is part of the CSCI-3081W Project Code, which was developed
at the University of Minnesota.
Copyright (c) 2018 Jane/Guanpin Zhong at the University of Minnesota.
Original Author(s) of this File:
  Jane/Guanpin Zhong, 11/01/18, University of Minnesota
*/

#include "imagetools/filter_saturate.h"
#include <cmath>
#include <cstdlib>
#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"
#include "imagetools/image_tools_math.h"

namespace image_tools {
    /// Default constructor
    FilterSaturate::FilterSaturate() {
      percent_ = 1;
    }

    /// Constructor
    FilterSaturate::FilterSaturate(float p) {
      percent_ = p;
    }

    /// Nothing inside, as only useful for convolution filters.
    void FilterSaturate::SetupFilter() {}

    /// Nothing inside, as only useful for convolution filters.
    void FilterSaturate::CleanupFilter() {}

    /// Destructor
    FilterSaturate::~FilterSaturate() {}

    float FilterSaturate::scale_factor() { return percent_; }

    void FilterSaturate::set_scale_factor(float s) { percent_ = s; }

    /** @brief
    Return the color after changes, through using Lerp() function to
    linearly interpolate between the grayscale version of the color
    and the color.
    */
    ColorData FilterSaturate::CalculaterFilteredPixel(PixelBuffer *buffer,
      int x, int y) {
      ColorData color = buffer->pixel(x, y);

      /// Create a grayscale pixel.
      float scale = color.Luminance();
      ColorData gray(scale, scale, scale);
      color = ImageToolsMath::Lerp(gray, color, percent_);
      color.Clamp();  /// Keep it in range (0,1).
      return color;
    }
}  /// namespace image_tools
