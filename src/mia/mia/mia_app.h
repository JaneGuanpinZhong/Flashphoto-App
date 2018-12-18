/**
This file is part of the CSCI-3081W Project Support Code, which was developed
at the University of Minnesota.

This code is to be used for student coursework.  It is not an open source
project.
Copyright (c) 2015-2018 Daniel Keefe, TAs, & Regents of the University of
Minnesota.

Original Author(s) of this File:
  Seth Johnson, 2/15/15, University of Minnesota

Author(s) of Significant Updates/Modifications to the File:
  Daniel Keefe, 2018, UMN -- ported to MinGfx
  ...
*/

#ifndef MIA_MIA_APP_H_
#define MIA_MIA_APP_H_

#include <mingfx.h>
#include <string>
#include <vector>
#include "imagetools/color_data.h"
#include "imagetools/image_editor.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {

/** @brief The Mia GUI. This class creates a graphics window to display
 the current PixelBuffer and a graphical user interface to interact with it
 using
 Tools and Filters. */
class MiaApp : public mingfx::GraphicsApp {
 public:
  MiaApp(int width, int height, const ColorData &background_color);
  virtual ~MiaApp();

  /** Called when the mouse moves but no mouse buttons are currently pressed. */
  void OnMouseMove(const mingfx::Point2 &pos,
                   const mingfx::Vector2 &delta) override;

  /** Called when the user pushes the mouse left button. */
  void OnLeftMouseDown(const mingfx::Point2 &pos) override;

  /** Called when the user moves the mouse with the left button depressed. */
  void OnLeftMouseDrag(const mingfx::Point2 &pos,
                       const mingfx::Vector2 &delta) override;

  /** Called when the user releases the left mouse button. */
  void OnLeftMouseUp(const mingfx::Point2 &pos) override;

  /** This function is called when the user drags the corner of the window
   to resize it.  We need to detect that operation because it requires us to
   resize the underlying pixel buffer. */
  void OnWindowResize(int new_width, int new_height) override;

  /** This function gets called once per frame.  If the user is in the middle
   of using a tool that applies more "paint" over time, like a spray can, then
   this function is used to repeatedly apply the tool to the pixel buffer. */
  void UpdateSimulation(double dt) override;

  /** Used to setup the 2D GUI. */
  void InitNanoGUI() override;

  /** Used to initialize OpenGL graphics, including the texture used to draw
   the pixel buffer to the screen. */
  void InitOpenGL() override;

  /** Used to draw the cursor for the tool once each frame. */
  void DrawUsingNanoVG(NVGcontext *ctx) override;

  /** Used to draw the PixelBuffer to the screen once each frame. */
  void DrawUsingOpenGL() override;

 private:
  void InitializeBuffers(ColorData initial_color, int width, int height);

  ImageEditor image_editor_;

  mingfx::Texture2D display_texture_;
  mingfx::QuickShapes quick_shapes_;

  nanogui::Button *undo_btn_;
  nanogui::Button *redo_btn_;

  /// Current state of the active tool as determined via user interaction
  std::string tool_name_;
  ColorData tool_color_;
  float tool_radius_;
  int tool_x_;
  int tool_y_;
  bool painting_;

  /// Variables updated by the GUI widgets
  float blur_radius_;
  float sharpen_radius_;
  float thresh_cutoff_;
  int quant_bins_;

  /* Copy/move assignment/construction disallowed */
  MiaApp(const MiaApp &rhs) = delete;
  MiaApp &operator=(const MiaApp &rhs) = delete;
};

}  /// namespace image_tools

#endif  // MIA_MIA_APP_H_
