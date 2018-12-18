/**
This file is part of the CSCI-3081W Project Code, which was developed
at the University of Minnesota.
Copyright (c) 2018 Jane/Guanpin Zhong at the University of Minnesota.
Original Author(s) of this File:
  Jane/Guanpin Zhong, 11/01/18, University of Minnesota
*/

#include "imagetools/filter_quantize.h"
#include <cmath>
#include <cstdlib>
#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {
  /// constructor
  FilterQuantize::FilterQuantize() : num_bins(8) {}

  /// Constructor
  FilterQuantize::FilterQuantize(int n) {
    num_bins = n;
  }

  /// Destructor
  FilterQuantize::~FilterQuantize() {}

  /// Nothing inside, as only useful for convolution filters.
  void FilterQuantize::SetupFilter() {}

  /// Nothing inside, as only useful for convolution filters.
  void FilterQuantize::CleanupFilter() {}

  /// Return the pixel after changing the color, through binning.
  ColorData FilterQuantize::CalculaterFilteredPixel(PixelBuffer *buffer,
    int x, int y) {
    ColorData color = buffer->pixel(x, y);
    int num_steps = num_bins-1;
    if (num_steps > 0) {
      color.set_red((round(color.red()*num_steps))/num_steps);
      color.set_green((round(color.green()*num_steps))/num_steps);
      color.set_blue((round(color.blue()*num_steps))/num_steps);
      color.Clamp();  /// Keep values within range (0,1).
      return color;
    } else {
      return ColorData(0.0, 0.0, 0.0);
    }
  }

}  /// namespace image_tools
