/**
This file is part of the CSCI-3081W Project Code, which was developed
at the University of Minnesota.
Copyright (c) 2018 Jane/Guanpin Zhong at the University of Minnesota.
Original Author(s) of this File:
  Jane/Guanpin Zhong, 11/14/18, University of Minnesota
*/

#include "imagetools/image_editor.h"
#include <assert.h>
#include <mingfx.h>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <utility>
#include "imagetools/color_data.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {
/** The ImageEditor requires a current pixel buffer, so this is the preferred
 constructor. */
ImageEditor::ImageEditor(PixelBuffer *buffer): tool_color_(ColorData(0.8,
  0.2, 0.2)), tool_radius_(5.0) {
  current_buffer_ = buffer;
}

/** Creates an editor with a NULL pixel buffer.  You will need to set the
 pixel buffer before performing any editing operations. */
ImageEditor::ImageEditor() {
  current_buffer_ = NULL;
}

/** Deletes the current pixel buffer if not null. */
ImageEditor::~ImageEditor() {
  if (current_buffer_ != NULL) {
    delete current_buffer_;
    current_buffer_ = NULL;
  }
}

Tool *ImageEditor::GetToolByName(const std::string &name) {
  if (name == t_blur_.name()) {
    return &t_blur_;
  } else if (name == t_calligraphy_pen_.name()) {
    return &t_calligraphy_pen_;
  } else if (name == t_chalk_.name()) {
    return &t_chalk_;
  } else if (name == t_eraser_.name()) {
    return &t_eraser_;
  } else if (name == t_highlighter_.name()) {
    return &t_highlighter_;
  } else if (name == t_pen_.name()) {
    return &t_pen_;
  } else if (name == t_spray_can_.name()) {
    return &t_spray_can_;
  } else if (name == t_stamp_.name()) {
    return &t_stamp_;
  } else {
    return NULL;
  }
}

void ImageEditor::StartStroke(const std::string &tool_name,
                                const ColorData &color, float radius, int x,
                                int y) {
  current_tool_ = GetToolByName(tool_name);
  tool_color_ = color;
  tool_radius_ = radius;
  if ((current_tool_) && (current_buffer_)) {
    SaveStateForPossibleUndo();
    current_tool_->StartStroke(current_buffer_, x, y, tool_color_,
                               tool_radius_);
  }
}

void ImageEditor::AddToStroke(int x, int y) {
  if ((current_tool_) && (current_buffer_)) {
    current_tool_->AddToStroke(x, y);
  }
}

void ImageEditor::EndStroke(int x, int y) {
  if ((current_tool_) && (current_buffer_)) {
    current_tool_->EndStroke(x, y);
  }
}

void ImageEditor::LoadFromFile(const std::string &filename) {
  if (current_buffer_ != NULL) {
    SaveStateForPossibleUndo();
    current_buffer_->LoadFromFile(filename);
  } else {
    current_buffer_ = new PixelBuffer(filename);
  }
}

void ImageEditor::SaveToFile(const std::string &filename) {
  current_buffer_->SaveToFile(filename);
}

/// Applying filters
void ImageEditor::ApplyBlurFilter(float radius) {
  SaveStateForPossibleUndo();
  image_tools::ConvolutionFilterBlur cfBlur = ConvolutionFilterBlur(radius);
  cfBlur.ApplyToBuffer(current_buffer_);
}

void ImageEditor::ApplyMotionBlurFilter(float radius,
        ConvolutionFilterMotionBlur::MBlurDir dir) {
  SaveStateForPossibleUndo();
  ConvolutionFilterMotionBlur cfmBlur =
    ConvolutionFilterMotionBlur(radius, dir);
  cfmBlur.ApplyToBuffer(current_buffer_);
}

void ImageEditor::ApplySharpenFilter(float radius) {
  SaveStateForPossibleUndo();
  image_tools::ConvolutionFilterSharpen cfSharpen =
    ConvolutionFilterSharpen(radius);
  cfSharpen.ApplyToBuffer(current_buffer_);
}

void ImageEditor::ApplyEdgeDetectFilter() {
  SaveStateForPossibleUndo();
  image_tools::ConvolutionFilterEdge cfEdge = ConvolutionFilterEdge();
  cfEdge.ApplyToBuffer(current_buffer_);
}

void ImageEditor::ApplyThresholdFilter(float cutoff_value) {
  SaveStateForPossibleUndo();
  image_tools::FilterThreshold fthreshold = FilterThreshold(cutoff_value);
  fthreshold.ApplyToBuffer(current_buffer_);
}

void ImageEditor::ApplySaturateFilter(float scale_factor) {
  SaveStateForPossibleUndo();
  image_tools::FilterSaturate fsaturate = FilterSaturate(scale_factor);
  fsaturate.ApplyToBuffer(current_buffer_);
}

void ImageEditor::ApplyChannelsFilter(float red_scale,
  float green_scale, float blue_scale) {
  SaveStateForPossibleUndo();
  image_tools::FilterChannel fchannel = FilterChannel(red_scale,
    green_scale, blue_scale);
  fchannel.ApplyToBuffer(current_buffer_);
}

void ImageEditor::ApplyQuantizeFilter(int num_bins) {
  SaveStateForPossibleUndo();
  image_tools::FilterQuantize fquantize = FilterQuantize(num_bins);
  fquantize.ApplyToBuffer(current_buffer_);
}

bool ImageEditor::can_undo() { return saved_states_.size(); }

bool ImageEditor::can_redo() { return undone_states_.size(); }

void ImageEditor::Undo() {
  if (can_undo()) {
    /// save state for a possilbe redo
    undone_states_.push_front(current_buffer_);

    /// make the top state on the undo stack the current one
    current_buffer_ = saved_states_.front();
    saved_states_.pop_front();
  }
}

void ImageEditor::Redo() {
  if (can_redo()) {
    /// save state for a possible undo
    saved_states_.push_front(current_buffer_);

    /// make the top state on the redo stack the current one
    current_buffer_ = undone_states_.front();
    undone_states_.pop_front();
  }
}

void ImageEditor::SaveStateForPossibleUndo() {
  PixelBuffer *buffer_copy = new PixelBuffer(*current_buffer_);
  saved_states_.push_front(buffer_copy);

  /// remove the oldest undos if we've over our limit
  while (saved_states_.size() > max_undos_) {
    delete saved_states_.back();
    saved_states_.pop_back();
  }

  /**
  Committing a new state invalidates the states saved in the redo stack,
  so, we simply clear out this stack.
  */
  while (!undone_states_.empty()) {
    delete undone_states_.back();
    undone_states_.pop_back();
  }
}

PixelBuffer *ImageEditor::pixel_buffer() { return current_buffer_; }

void ImageEditor::set_pixel_buffer(PixelBuffer *buffer) {
  current_buffer_ = buffer;
}

} /* namespace image_tools */
