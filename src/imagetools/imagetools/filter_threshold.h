/**
This file is part of the CSCI-3081W Project Code, which was developed
at the University of Minnesota.
Copyright (c) 2018 Jane/Guanpin Zhong at the University of Minnesota.
Original Author(s) of this File:
  Jane/Guanpin Zhong, 11/01/18, University of Minnesota
*/

#ifndef IMAGETOOLS_FILTER_THRESHOLD_H_
#define IMAGETOOLS_FILTER_THRESHOLD_H_

#include "imagetools/filter.h"
#include <cmath>
#include <cstdlib>
#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {
  /** @brief
  Main purpose:
  Turn any pixel with an average intensity value greater than the
  threshold parameter set in the GUI to white; otherwise turn the
  pixel black.
  */
class FilterThreshold: public Filter {
 public:
  /// constructor
  FilterThreshold();

  /// Constructor
  explicit FilterThreshold(float v);

  /// Destructor
  virtual ~FilterThreshold();

  /// Nothing inside, as only useful for convolution filters.
  void SetupFilter() override;

  /// Nothing inside, as only useful for convolution filters.
  void CleanupFilter() override;

  /// Return color after changes, through comparisons.
  ColorData CalculaterFilteredPixel(PixelBuffer *buffer,
        int x, int y) override;

 private:
  float value_;
};  /// class FilterThreshold

}  /// namespace image_tools

#endif  // IMAGETOOLS_FILTER_THRESHOLD_H_
