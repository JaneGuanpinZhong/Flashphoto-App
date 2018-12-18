/**
This file is part of the CSCI-3081W Project Code, which was developed
at the University of Minnesota.
Copyright (c) 2018 Jane/Guanpin Zhong at the University of Minnesota.
Original Author(s) of this File:
  Jane/Guanpin Zhong, 11/01/18, University of Minnesota
*/

#include "imagetools/filter.h"
#include <cmath>
#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {
  /// Default constructor
  Filter::Filter() {}

  /// Destructor
  Filter::~Filter() {}

  /** @brief
  There are two situations. For the four simple filters, we just change
  directly each pixel in the buffer. However, for convolution filters,
  we copy it at first, then apply it to CalculaterFilteredPixel
  function to get new values, and finally set the original buffer as it.
  */
  void Filter::ApplyToBuffer(PixelBuffer* buffer) {
    PixelBuffer *source = buffer;
    PixelBuffer *dest = buffer;

    if (!can_copy_in_place()) {
      /// create a temporary source buffer
      source = new PixelBuffer(*buffer);
    }

    SetupFilter();

    for (int i = 0; i < source->width(); i++) {
      for (int j = 0; j < source->height(); j++) {
        ColorData p = CalculaterFilteredPixel(source, i, j);
        p.Clamp();
        dest->set_pixel(i, j, p);
      }
    }

    CleanupFilter();

    if (!can_copy_in_place()) {
      delete source;
    }
}

  /** @brief
  The value of this function for simple filters is true, so we do not
  need to copy it later.
  */
  bool Filter::can_copy_in_place() {
    return true;
  }
}  /// namespace image_tools
