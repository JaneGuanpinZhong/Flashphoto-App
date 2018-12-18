
/**
This file is part of the CSCI-3081W Project Code, which was developed
at the University of Minnesota.
Copyright (c) 2018 Jane/Guanpin Zhong at the University of Minnesota.
Original Author(s) of this File:
  Jane/Guanpin Zhong, 11/01/18, University of Minnesota
*/

#ifndef IMAGETOOLS_FILTER_H_
#define IMAGETOOLS_FILTER_H_

#include <string>
#include "imagetools/color_data.h"
#include "imagetools/float_matrix.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {

  /** @brief
  Introduction:
  Includes two subparts, which represent simple or convolution filters.
  */
class Filter {
 public:
  /// Default constructor
  Filter();
  /// Destructor
  virtual ~Filter();

  /// Used to apply results to our buffer.
  void ApplyToBuffer(PixelBuffer* buffer);

  /// Pure Virtual as only used for convolution filters.
  virtual void SetupFilter() = 0;

  /** @brief
  Compute the pixel after applying some filter.
  Pure virtual for different types of filters.
  */
  virtual ColorData CalculaterFilteredPixel(PixelBuffer *buffer,
        int x, int y) = 0;

  /// Delete pointer after use.
  virtual void CleanupFilter() = 0;

  /** @brief
  Represent the type of filters, with true for simple ones,
  and false for convolution filters. */
  virtual bool can_copy_in_place();
};
}  /// namespace image_tools

#endif  // IMAGETOOLS_FILTER_H_
