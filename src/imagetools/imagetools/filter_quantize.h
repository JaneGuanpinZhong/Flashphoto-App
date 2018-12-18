/**
This file is part of the CSCI-3081W Project Code, which was developed
at the University of Minnesota.
Copyright (c) 2018 Jane/Guanpin Zhong at the University of Minnesota.
Original Author(s) of this File:
  Jane/Guanpin Zhong, 11/01/18, University of Minnesota
*/

#ifndef IMAGETOOLS_FILTER_QUANTIZE_H_
#define IMAGETOOLS_FILTER_QUANTIZE_H_

#include "imagetools/filter.h"
#include <cmath>
#include <cstdlib>
#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {
  /** @brief
  Main purpose:
  Reduce the number of colors in the image by binning.
  Adjust each color channel value to put it into the nearest bin. */
class FilterQuantize: public Filter{
 public:
  /// constructor
  FilterQuantize();

  /// constructor
  explicit FilterQuantize(int n);

  /// destructor
  virtual ~FilterQuantize();

  /** @brief
  Override the function in super class.
  Nothing inside, as only useful for convolution filters. */
  void SetupFilter() override;

  /// Nothing inside, as only useful for convolution filters.
  void CleanupFilter() override;
  /// Return the pixel after changing the color, through binning.
  ColorData CalculaterFilteredPixel(PixelBuffer *buffer,
        int x, int y) override;

 private:
  int num_bins;
};  /// class FilterQuantize

}  /// namespace image_tools

#endif  // IMAGETOOLS_FILTER_QUANTIZE_H_
