/**
This file is part of the CSCI-3081W Project Code, which was developed
at the University of Minnesota.
Copyright (c) 2018 Jane/Guanpin Zhong at the University of Minnesota.
Original Author(s) of this File:
  Jane/Guanpin Zhong, 11/01/18, University of Minnesota
*/

#ifndef IMAGETOOLS_CONVOLUTION_H_
#define IMAGETOOLS_CONVOLUTION_H_

#include <cstdlib>
#include <cmath>
#include "imagetools/filter.h"
#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {
  /// @brief A super class of multiple convolution filters, which uses kernel
  /// Also a subclass of Filter.
class ConvolutionFilter: public Filter {
 public:
  ConvolutionFilter();  /// Deafult constructor
  virtual ~ConvolutionFilter();  /// Destructor

  /// Pure virtual to reserve for specific definition in subclasses.
  virtual FloatMatrix* CreateKernel() = 0;

  /**
  Override the function from the superclass.
  Set the value the private variable kernel_ points to as what we get
  from CreateKernel().
  */
  void SetupFilter() override;

  /** @brief
  Override the function from the superclass. Here it applies the
  kernel to a specific position on canvas, through special
  calculating methods.
  */
  ColorData CalculaterFilteredPixel(PixelBuffer *buffer,
        int x, int y) override;

  /** @brief
  Delete the pointer after use.
  Override the function from the superclass.
  */
  void CleanupFilter() override;

  /** @brief
  The default value of this function for convolution filters
  is false, so later we have to copy the pointer.
  */
  bool can_copy_in_place() override;

  /** @brief For some filters it makes sense to convolve R,G,B and A. For
  others it only makes sense to convolve R,G,B.  In this case, alpha remains
  unchanged. The default implementation returns false. */
  virtual bool convolve_alpha() const;

 private:
  FloatMatrix* kernel_;
};  /// class ConvolutionFilter
}  /// namespace image_tools

#endif  // IMAGETOOLS_CONVOLUTION_H_
