/**
This file is part of the CSCI-3081W Project Code, which was developed
at the University of Minnesota.
Copyright (c) 2018 Jane/Guanpin Zhong at the University of Minnesota.
Original Author(s) of this File:
  Jane/Guanpin Zhong, 11/01/18, University of Minnesota
*/

#ifndef IMAGETOOLS_FILTER_CHANNELS_H_
#define IMAGETOOLS_FILTER_CHANNELS_H_

#include "imagetools/filter.h"
#include <cmath>
#include <cstdlib>
#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {

  /** @brief
  Main purpose:
  Change the color, through multiplying
  given input scale values and original color values. */
class FilterChannel: public Filter {
 public:
  /// Default constructor
  FilterChannel();
  /// Constructor
  FilterChannel(float r, float g, float b);

  /// Destructor
  virtual ~FilterChannel();

  /// Nothing inside, as only useful for convolution filters.
  void SetupFilter() override;

  /// Nothing inside, as only useful for convolution filters.
  void CleanupFilter() override;

  /** @brief
  Return the pixel after changing the color, through multiplying
  given input scale values and original color values. */
  ColorData CalculaterFilteredPixel(PixelBuffer* buffer,
        int x, int y) override;

 private:
  float r_;
  float g_;
  float b_;
};  /// class FilterChannel

}  /// namespace image_tools

#endif  // IMAGETOOLS_FILTER_CHANNELS_H_
