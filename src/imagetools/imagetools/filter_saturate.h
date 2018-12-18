/**
This file is part of the CSCI-3081W Project Code, which was developed
at the University of Minnesota.
Copyright (c) 2018 Jane/Guanpin Zhong at the University of Minnesota.
Original Author(s) of this File:
  Jane/Guanpin Zhong, 11/01/18, University of Minnesota
*/

#ifndef IMAGETOOLS_FILTER_SATURATE_H_
#define IMAGETOOLS_FILTER_SATURATE_H_

#include "imagetools/filter.h"
#include <cmath>
#include <cstdlib>
#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {
  /** @brief Main purpose: Change the colorfulness of images. */
class FilterSaturate: public Filter {
 public:
  /// Default constructor
  FilterSaturate();
  /// Constructor
  explicit FilterSaturate(float p);

  /// Nothing inside, as only useful for convolution filters.
  void SetupFilter() override;

  /// Nothing inside, as only useful for convolution filters.
  void CleanupFilter() override;

  /// Destructor
  virtual ~FilterSaturate();

  /// Get the percentage value
  float scale_factor();

  void set_scale_factor(float s);


  /** @brief
  Return the color after changes, through using Lerp() function to
  linearly interpolate between the grayscale version of the color
  and the color. */
  ColorData CalculaterFilteredPixel(PixelBuffer *buffer,
        int x, int y) override;

 private:
  float percent_;
};  /// class FilterSaturate

}  /// namespace image_tools

#endif  // IMAGETOOLS_FILTER_SATURATE_H_
