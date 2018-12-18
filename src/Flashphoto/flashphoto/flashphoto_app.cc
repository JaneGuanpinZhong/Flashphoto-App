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
  Jane/Guanpin Zhong, 2018, UMN
*/

#include "flashphoto/flashphoto_app.h"
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

/// use enums from ConvolutionFilterMotionBlur
const std::map<ConvolutionFilterMotionBlur::MBlurDir, std::string>
  FlashPhotoApp::mblur_dir_names_ = {
    {ConvolutionFilterMotionBlur::MBLUR_DIR_N_S,   "North/South"},
    {ConvolutionFilterMotionBlur::MBLUR_DIR_E_W,   "East/West"},
    {ConvolutionFilterMotionBlur::MBLUR_DIR_NE_SW, "Northeast/Southwest"},
    {ConvolutionFilterMotionBlur::MBLUR_DIR_NW_SE, "Northwest/Southeast"}
};

FlashPhotoApp::FlashPhotoApp(int width, int height,
                             const ColorData &background_color)
    : GraphicsApp(width, height, "FlashPhoto"),
      tool_name_(ToolPen::name()),
      painting_(false),
      tool_color_(ColorData(0.8, 0.2, 0.2)),
      tool_radius_(5.0),
      blur_radius_(5.0),
      mblur_radius_(5.0),
      mblur_dir_(ConvolutionFilterMotionBlur::MBLUR_DIR_N_S),
      sharpen_radius_(5.0),
      thresh_cutoff_(0.5),
      sat_value_(1.0),
      chan_r_(1.0),
      chan_g_(1.0),
      chan_b_(1.0),
      quant_bins_(5) {
  PixelBuffer *buffer = new PixelBuffer(width, height, background_color);
  image_editor = new ImageEditor(buffer);
}

FlashPhotoApp::~FlashPhotoApp() {}

void FlashPhotoApp::InitNanoGUI() {
  /// Setup the GUI window
  nanogui::Window *window = new nanogui::Window(screen(), "Flash Photo");
  window->setPosition(Eigen::Vector2i(10, 10));
  window->setSize(Eigen::Vector2i(200, 100));
  window->setLayout(new nanogui::GroupLayout(4, 4, 8, 8));

  nanogui::Button *b;

  /// FILE Section

  new nanogui::Label(window, "File", "sans-bold");

  nanogui::Widget *file_io = new nanogui::Widget(window);
  file_io->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal,
                                            nanogui::Alignment::Middle, 0, 6));
  b = new nanogui::Button(file_io, "Open");
  b->setFixedSize({72, 20});
  b->setCallback([this] {
    std::string fname =
        nanogui::file_dialog({{"png", "Portable Network Graphics"}}, false);
    if (fname != "") {
      image_editor->LoadFromFile(fname);
      ResizeWindow(image_editor->pixel_buffer()->width(),
                   image_editor->pixel_buffer()->height());
    }
  });
  b = new nanogui::Button(file_io, "Save");
  b->setFixedSize({72, 20});
  b->setCallback([this] {
    std::string fname =
        nanogui::file_dialog({{"png", "Portable Network Graphics"}}, true);
    if (fname != "") {
      image_editor->SaveToFile(fname);
    }
  });


  /// EDIT Section

  new nanogui::Label(window, "Edit", "sans-bold");

  nanogui::Widget *undo_redo = new nanogui::Widget(window);
  undo_redo->setLayout(new nanogui::BoxLayout(
      nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6));
  undo_btn_ = new nanogui::Button(undo_redo, "Undo");
  undo_btn_->setFixedSize({72, 20});
  undo_btn_->setIcon(ENTYPO_ICON_REPLY);
  undo_btn_->setCallback([this]() {
    if (image_editor->can_undo()) {
      image_editor->Undo();
      ResizeWindow(image_editor->pixel_buffer()->width(),
      image_editor->pixel_buffer()->height());
    }
  });
  redo_btn_ = new nanogui::Button(undo_redo, "Redo");
  redo_btn_->setFixedSize({72, 20});
  redo_btn_->setIcon(ENTYPO_ICON_FORWARD);
  redo_btn_->setCallback([this]() {
    if (image_editor->can_redo()) {
      image_editor->Redo();
      ResizeWindow(image_editor->pixel_buffer()->width(),
      image_editor->pixel_buffer()->height());
    }
  });

  /// TOOLS Section

  new nanogui::Label(window, "Tools", "sans-bold");

  nanogui::Widget *tools = new nanogui::Widget(window);
  tools->setLayout(new nanogui::GroupLayout(4, 4, 8, 8));

  /// Pen
  b = new nanogui::Button(tools);
  b->setFlags(nanogui::Button::RadioButton);
  b->setFixedSize({150, 20});
  b->setCaption(ToolPen::name());
  b->setCallback([this]() { tool_name_ = ToolPen::name(); });
  b->setPushed(true);

  /// Caligraphy Pen
  b = new nanogui::Button(tools);
  b->setFlags(nanogui::Button::RadioButton);
  b->setFixedSize({150, 20});
  b->setCaption(ToolCalligraphyPen::name());
  b->setCallback([this]() { tool_name_ = ToolCalligraphyPen::name(); });

  /// Chalk
  b = new nanogui::Button(tools);
  b->setFlags(nanogui::Button::RadioButton);
  b->setFixedSize({150, 20});
  b->setCaption(ToolChalk::name());
  b->setCallback([this]() { tool_name_ = ToolChalk::name(); });

  /// Highlighter
  b = new nanogui::Button(tools);
  b->setFlags(nanogui::Button::RadioButton);
  b->setFixedSize({150, 20});
  b->setCaption(ToolHighlighter::name());
  b->setCallback([this]() { tool_name_ = ToolHighlighter::name(); });

  /// Spray Can
  b = new nanogui::Button(tools);
  b->setFlags(nanogui::Button::RadioButton);
  b->setFixedSize({150, 20});
  b->setCaption(ToolSprayCan::name());
  b->setCallback([this]() { tool_name_ = ToolSprayCan::name(); });

  /// Blur
  b = new nanogui::Button(tools);
  b->setFlags(nanogui::Button::RadioButton);
  b->setFixedSize({150, 20});
  b->setCaption(ToolBlur::name());
  b->setCallback([this]() { tool_name_ = ToolBlur::name(); });

  /// Eraser
  b = new nanogui::Button(tools);
  b->setFlags(nanogui::Button::RadioButton);
  b->setFixedSize({150, 20});
  b->setCaption(ToolEraser::name());
  b->setCallback([this]() { tool_name_ = ToolEraser::name(); });

  /// Tool Color
  new nanogui::Label(tools, "Tool Color:", "sans-bold");
  ColorData col = tool_color_;
  nanogui::ColorPicker *cp1 = new nanogui::ColorPicker(
      tools, nanogui::Color(col.red(), col.green(), col.blue(), col.alpha()));
  cp1->setFixedSize({150, 20});
  cp1->setFinalCallback([this](const nanogui::Color &c) {
    tool_color_ = ColorData(c.r(), c.g(), c.b(), c.w());
  });

  /// Tool Radius
  new nanogui::Label(tools, "Tool Size:", "sans-bold");
  nanogui::Slider *tr_slider = new nanogui::Slider(tools);
  tr_slider->setRange(std::make_pair(0, 40));
  tr_slider->setValue(tool_radius_);
  tr_slider->setFixedWidth(150);
  tr_slider->setCallback([this](float value) { tool_radius_ = value; });
  tr_slider->setFinalCallback([this](float value) { tool_radius_ = value; });

  /// FILTERS Section
  nanogui::GridLayout *params_layout = new nanogui::GridLayout(
      nanogui::Orientation::Horizontal, 2, nanogui::Alignment::Middle, 15, 5);
  params_layout->setColAlignment(
      {nanogui::Alignment::Maximum, nanogui::Alignment::Fill});
  params_layout->setSpacing(0, 10);

  new nanogui::Label(window, "Filters", "sans-bold");

  nanogui::Widget *filters = new nanogui::Widget(window);
  filters->setLayout(new nanogui::GroupLayout(4, 4, 8, 8));

  /// BLUR
  nanogui::PopupButton *blur_pb = new nanogui::PopupButton(filters, "Blur");
  blur_pb->setFixedSize({150, 20});

  nanogui::Popup *blur_win = blur_pb->popup();
  blur_win->setLayout(new nanogui::GroupLayout(4, 4, 8, 8));

  nanogui::Widget *blur_params = new nanogui::Widget(blur_win);
  blur_params->setLayout(params_layout);

  new nanogui::Label(blur_params, "Blur Amount:", "sans-bold");
  nanogui::Widget *blur_param1 = new nanogui::Widget(blur_params);
  blur_param1->setLayout(new nanogui::BoxLayout(
      nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6));
  nanogui::Slider *br_slider = new nanogui::Slider(blur_param1);
  br_slider->setRange(std::make_pair(0, 10));
  br_slider->setValue(blur_radius_);
  br_slider->setFixedWidth(150);
  nanogui::TextBox *br_text = new nanogui::TextBox(blur_param1);
  br_text->setFixedSize({60, 20});
  br_text->setFontSize(18);
  br_text->setAlignment(nanogui::TextBox::Alignment::Right);
  br_text->setValue(std::to_string(static_cast<int>(blur_radius_)));
  br_slider->setCallback([this, br_text](float value) {
    br_text->setValue(std::to_string(static_cast<int>(value)));
    blur_radius_ = value;
  });
  b = new nanogui::Button(blur_win, "Apply");
  b->setFixedSize({150, 30});
  b->setCallback([this] { image_editor->ApplyBlurFilter(blur_radius_); });

  /// MOTION BLUR
  nanogui::PopupButton *m_blur_pb =
      new nanogui::PopupButton(filters, "Motion Blur");
  m_blur_pb->setFixedSize({150, 20});

  nanogui::Popup *m_blur_win = m_blur_pb->popup();
  m_blur_win->setLayout(new nanogui::GroupLayout(4, 4, 8, 8));

  nanogui::Widget *m_blur_params = new nanogui::Widget(m_blur_win);
  m_blur_params->setLayout(params_layout);

  new nanogui::Label(m_blur_params, "Blur Amount:", "sans-bold");
  nanogui::Widget *m_blur_param1 = new nanogui::Widget(m_blur_params);
  m_blur_param1->setLayout(new nanogui::BoxLayout(
      nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6));
  nanogui::Slider *mbr_slider = new nanogui::Slider(m_blur_param1);
  mbr_slider->setRange(std::make_pair(0, 10));
  mbr_slider->setValue(mblur_radius_);
  mbr_slider->setFixedWidth(150);
  nanogui::TextBox *mbr_text = new nanogui::TextBox(m_blur_param1);
  mbr_text->setFixedSize({60, 20});
  mbr_text->setFontSize(18);
  mbr_text->setAlignment(nanogui::TextBox::Alignment::Right);
  mbr_text->setValue(std::to_string(static_cast<int>(mblur_radius_)));
  mbr_slider->setCallback([mbr_text, this](float value) {
    mbr_text->setValue(std::to_string(static_cast<int>(value)));
    mblur_radius_ = value;
  });

  new nanogui::Label(m_blur_params, "Direction:", "sans-bold");

  nanogui::ComboBox *mbr_cb =
      new nanogui::ComboBox(m_blur_params, {
        MotionBlurDirectionName(ConvolutionFilterMotionBlur::MBLUR_DIR_N_S),
        MotionBlurDirectionName(ConvolutionFilterMotionBlur::MBLUR_DIR_E_W),
        MotionBlurDirectionName(ConvolutionFilterMotionBlur::MBLUR_DIR_NE_SW),
        MotionBlurDirectionName(ConvolutionFilterMotionBlur::MBLUR_DIR_NW_SE)});

  /// nanogui::ComboBox *mbr_cb = new nanogui::ComboBox(
  ///     m_blur_params, {MotionBlurDirectionName(MBLUR_DIR_N_S),
  ///                     MotionBlurDirectionName(MBLUR_DIR_E_W),
  ///                     MotionBlurDirectionName(MBLUR_DIR_NE_SW),
  ///                     MotionBlurDirectionName(MBLUR_DIR_NW_SE)});

  mbr_cb->setFixedSize({216, 20});
  mbr_cb->setSelectedIndex(static_cast<int>(mblur_dir_));
  mbr_cb->setCallback([this](float value) {
    (void)value;
  int intValue = static_cast<int>(value);
    mblur_dir_ = static_cast<ConvolutionFilterMotionBlur::MBlurDir>(intValue);
    /// int intValue = static_cast<int>(value);
    /// mblur_dir_ = static_cast<MBlurDir>(intValue);
  });

  b = new nanogui::Button(m_blur_win, "Apply");
  b->setFixedSize({150, 30});
  b->setCallback([this] { image_editor->ApplyMotionBlurFilter(mblur_radius_,
    mblur_dir_); });

  /// SHARPEN
  nanogui::PopupButton *sharp = new nanogui::PopupButton(filters, "Sharpen");
  sharp->setFixedSize({150, 20});

  nanogui::Popup *sharp_win = sharp->popup();
  sharp_win->setLayout(new nanogui::GroupLayout(4, 4, 8, 8));

  nanogui::Widget *sharp_params = new nanogui::Widget(sharp_win);
  sharp_params->setLayout(params_layout);

  new nanogui::Label(sharp_params, "Amount:", "sans-bold");
  nanogui::Widget *sharp_param1 = new nanogui::Widget(sharp_params);
  sharp_param1->setLayout(new nanogui::BoxLayout(
      nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6));
  nanogui::Slider *sh_slider = new nanogui::Slider(sharp_param1);
  sh_slider->setRange(std::make_pair(0, 10));
  sh_slider->setValue(sharpen_radius_);
  sh_slider->setFixedWidth(150);
  nanogui::TextBox *sh_text = new nanogui::TextBox(sharp_param1);
  sh_text->setFixedSize({60, 20});
  sh_text->setFontSize(18);
  sh_text->setAlignment(nanogui::TextBox::Alignment::Right);
  sh_text->setValue(std::to_string(static_cast<int>(sharpen_radius_)));
  sh_slider->setCallback([this, sh_text](float value) {
    sh_text->setValue(std::to_string(static_cast<int>(value)));
    sharpen_radius_ = value;
  });

  b = new nanogui::Button(sharp_win, "Apply");
  b->setFixedSize({150, 30});
  b->setCallback([this] { image_editor->ApplySharpenFilter(sharpen_radius_); });

  /// EDGE DETECT
  nanogui::PopupButton *edge = new nanogui::PopupButton(filters, "Edge Detect");
  edge->setFixedSize({150, 20});

  nanogui::Popup *edge_win = edge->popup();
  edge_win->setLayout(params_layout);
  b = new nanogui::Button(edge_win, "Apply");
  b->setFixedSize({150, 30});
  b->setCallback([this] { image_editor->ApplyEdgeDetectFilter(); });

  /// THRESHOLD
  nanogui::PopupButton *thresh = new nanogui::PopupButton(filters, "Threshold");
  thresh->setFixedSize({150, 20});

  nanogui::Popup *thresh_win = thresh->popup();
  thresh_win->setLayout(new nanogui::GroupLayout(4, 4, 8, 8));

  nanogui::Widget *thresh_params = new nanogui::Widget(thresh_win);
  thresh_params->setLayout(params_layout);

  new nanogui::Label(thresh_params, "Cutoff Value:", "sans-bold");
  nanogui::Widget *thresh_param1 = new nanogui::Widget(thresh_params);
  thresh_param1->setLayout(new nanogui::BoxLayout(
      nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6));
  nanogui::Slider *th_slider = new nanogui::Slider(thresh_param1);
  th_slider->setRange(std::make_pair(0, 1));
  th_slider->setValue(thresh_cutoff_);
  th_slider->setFixedWidth(150);
  nanogui::TextBox *th_text = new nanogui::TextBox(thresh_param1);
  th_text->setFixedSize({60, 20});
  th_text->setFontSize(18);
  th_text->setAlignment(nanogui::TextBox::Alignment::Right);
  std::stringstream stream;
  stream << std::fixed << std::setprecision(2) << thresh_cutoff_;
  th_text->setValue(stream.str());
  th_slider->setCallback([this, th_text](float value) {
    std::stringstream innerStream;
    innerStream << std::fixed << std::setprecision(2) << value;
    th_text->setValue(innerStream.str());
    thresh_cutoff_ = value;
  });
  b = new nanogui::Button(thresh_win, "Apply");
  b->setFixedSize({150, 30});
  b->setCallback([this]
    { image_editor->ApplyThresholdFilter(thresh_cutoff_); });

  /// SATURATE
  nanogui::PopupButton *sat = new nanogui::PopupButton(filters, "Saturate");
  sat->setFixedSize({150, 20});

  nanogui::Popup *sat_win = sat->popup();
  sat_win->setLayout(new nanogui::GroupLayout(4, 4, 8, 8));

  nanogui::Widget *sat_params = new nanogui::Widget(sat_win);
  sat_params->setLayout(params_layout);

  new nanogui::Label(sat_params, "Amount:", "sans-bold");
  nanogui::Widget *sat_param1 = new nanogui::Widget(sat_params);
  sat_param1->setLayout(new nanogui::BoxLayout(
      nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6));
  nanogui::Slider *sa_slider = new nanogui::Slider(sat_param1);
  sa_slider->setRange(std::make_pair(0, 10));
  sa_slider->setValue(sat_value_);
  sa_slider->setFixedWidth(150);
  nanogui::TextBox *sa_text = new nanogui::TextBox(sat_param1);
  sa_text->setFixedSize({60, 20});
  sa_text->setFontSize(18);
  sa_text->setAlignment(nanogui::TextBox::Alignment::Right);
  stream.str("");
  stream << std::fixed << std::setprecision(2) << sat_value_;
  sa_text->setValue(stream.str());
  sa_slider->setCallback([this, sa_text](float value) {
    std::stringstream innerStream;
    innerStream << std::fixed << std::setprecision(2) << value;
    sa_text->setValue(innerStream.str());
    sat_value_ = value;
  });

  b = new nanogui::Button(sat_win, "Apply");
  b->setFixedSize({150, 30});
  b->setCallback([this] { image_editor->ApplySaturateFilter(sat_value_); });

  /// CHANNELS
  nanogui::PopupButton *channels =
      new nanogui::PopupButton(filters, "Adjust R,G,B");
  channels->setFixedSize({150, 20});

  nanogui::Popup *chan_win = channels->popup();
  chan_win->setLayout(new nanogui::GroupLayout(4, 4, 8, 8));

  nanogui::Widget *chan_params = new nanogui::Widget(chan_win);
  chan_params->setLayout(params_layout);

  new nanogui::Label(chan_params, "Red:", "sans-bold");
  nanogui::Widget *chan_red = new nanogui::Widget(chan_params);
  chan_red->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal,
                                             nanogui::Alignment::Middle, 0, 6));
  nanogui::Slider *rslider = new nanogui::Slider(chan_red);
  rslider->setRange(std::make_pair(0, 10));
  rslider->setValue(chan_r_);
  rslider->setFixedWidth(150);
  nanogui::TextBox *rtext = new nanogui::TextBox(chan_red);
  rtext->setFixedSize({60, 20});
  rtext->setFontSize(18);
  rtext->setAlignment(nanogui::TextBox::Alignment::Right);
  stream.str("");
  stream << std::fixed << std::setprecision(2) << chan_r_;
  rtext->setValue(stream.str());
  rslider->setCallback([this, rtext](float value) {
    std::stringstream innerStream;
    innerStream << std::fixed << std::setprecision(2) << value;
    rtext->setValue(innerStream.str());
    chan_r_ = value;
  });

  new nanogui::Label(chan_params, "Green:", "sans-bold");
  nanogui::Widget *chan_grn = new nanogui::Widget(chan_params);
  chan_grn->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal,
                                             nanogui::Alignment::Middle, 0, 6));
  nanogui::Slider *gslider = new nanogui::Slider(chan_grn);
  gslider->setRange(std::make_pair(0, 10));
  gslider->setValue(chan_g_);
  gslider->setFixedWidth(150);
  nanogui::TextBox *gtext = new nanogui::TextBox(chan_grn);
  gtext->setFixedSize({60, 20});
  gtext->setFontSize(18);
  gtext->setAlignment(nanogui::TextBox::Alignment::Right);
  stream.str("");
  stream << std::fixed << std::setprecision(2) << chan_g_;
  gtext->setValue(stream.str());
  gslider->setCallback([this, gtext](float value) {
    std::stringstream innerStream;
    innerStream << std::fixed << std::setprecision(2) << value;
    gtext->setValue(innerStream.str());
    chan_g_ = value;
  });

  new nanogui::Label(chan_params, "Blue:", "sans-bold");
  nanogui::Widget *chan_blu = new nanogui::Widget(chan_params);
  chan_blu->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal,
                                             nanogui::Alignment::Middle, 0, 6));
  nanogui::Slider *bslider = new nanogui::Slider(chan_blu);
  bslider->setRange(std::make_pair(0, 10));
  bslider->setValue(chan_b_);
  bslider->setFixedWidth(150);
  nanogui::TextBox *btext = new nanogui::TextBox(chan_blu);
  btext->setFixedSize({60, 20});
  btext->setFontSize(18);
  btext->setAlignment(nanogui::TextBox::Alignment::Right);
  stream.str("");
  stream << std::fixed << std::setprecision(2) << chan_b_;
  btext->setValue(stream.str());
  bslider->setCallback([this, btext](float value) {
    std::stringstream innerStream;
    innerStream << std::fixed << std::setprecision(2) << value;
    btext->setValue(innerStream.str());
    chan_b_ = value;
  });
  b = new nanogui::Button(chan_win, "Apply");
  b->setFixedSize({150, 30});
  b->setCallback([this]
    { image_editor->ApplyChannelsFilter(chan_r_, chan_g_, chan_b_); });

  /// QUANTIZE
  nanogui::PopupButton *quant_pb =
      new nanogui::PopupButton(filters, "Quantize");
  quant_pb->setFixedSize({150, 20});

  nanogui::Popup *quant_win = quant_pb->popup();
  quant_win->setLayout(new nanogui::GroupLayout(4, 4, 8, 8));

  nanogui::Widget *quant_params = new nanogui::Widget(quant_win);
  quant_params->setLayout(params_layout);

  new nanogui::Label(quant_params, "Number of Bins:", "sans-bold");
  nanogui::Widget *quant_param1 = new nanogui::Widget(quant_params);
  quant_param1->setLayout(new nanogui::BoxLayout(
      nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6));
  nanogui::Slider *q_slider = new nanogui::Slider(quant_param1);
  q_slider->setRange(std::make_pair(1, 256));
  q_slider->setValue(quant_bins_);
  q_slider->setFixedWidth(150);
  nanogui::TextBox *q_text = new nanogui::TextBox(quant_param1);
  q_text->setFixedSize({60, 20});
  q_text->setFontSize(18);
  q_text->setAlignment(nanogui::TextBox::Alignment::Right);
  q_text->setValue(std::to_string(quant_bins_));
  q_slider->setCallback([this, q_text](float value) {
    q_text->setValue(std::to_string(static_cast<int>(value)));
    quant_bins_ = static_cast<int>(value);
  });

  b = new nanogui::Button(quant_win, "Apply");
  b->setFixedSize({150, 30});
  b->setCallback(
      [this] {
        image_editor->ApplyQuantizeFilter(static_cast<int>(quant_bins_)); });

  screen()->performLayout();
}

void FlashPhotoApp::InitOpenGL() {
  display_texture_.InitFromFloats(image_editor->pixel_buffer()->width(),
                                  image_editor->pixel_buffer()->height(),
                                  image_editor->pixel_buffer()->data());
}

void FlashPhotoApp::DrawUsingNanoVG(NVGcontext *ctx) {
  nvgBeginPath(ctx);
  nvgCircle(ctx, tool_x_, tool_y_, tool_radius_);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 128));
  nvgStroke(ctx);
}

void FlashPhotoApp::DrawUsingOpenGL() {
  if (display_texture_.initialized()) {
    display_texture_.UpdateFromFloats(image_editor->pixel_buffer()->data());
    ColorData bg = image_editor->pixel_buffer()->background_color();
    glClearColor(bg.red(), bg.blue(), bg.green(), 1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    quick_shapes_.DrawFullscreenTexture(mingfx::Color(1, 1, 1),
                                        display_texture_);
  }
}

void FlashPhotoApp::OnMouseMove(const mingfx::Point2 &pos,
                                const mingfx::Vector2 &delta) {
  (void)delta;
  tool_x_ = pos[0];
  tool_y_ = pos[1];
}

void FlashPhotoApp::OnLeftMouseDown(const mingfx::Point2 &pos) {
  tool_x_ = pos[0];
  tool_y_ = pos[1];
  image_editor->StartStroke(tool_name_,
    tool_color_, tool_radius_, tool_x_, tool_y_);
  painting_ = true;
}

void FlashPhotoApp::OnLeftMouseDrag(const mingfx::Point2 &pos,
                                    const mingfx::Vector2 &delta) {
  (void)delta;
  /// note: AddToStroke() is called inside UpdateSimulation to support tools
  /// like the spray can that accumulate paint over time when the mouse is held
  /// down even if not actually moving.
  tool_x_ = pos[0];
  tool_y_ = pos[1];
}

void FlashPhotoApp::OnLeftMouseUp(const mingfx::Point2 &pos) {
  tool_x_ = pos[0];
  tool_y_ = pos[1];
  image_editor->EndStroke(tool_x_, tool_y_);
  painting_ = false;
}

void FlashPhotoApp::UpdateSimulation(double dt) {
  (void)dt;
  if (painting_) {
    image_editor->AddToStroke(tool_x_, tool_y_);
  }
}

void FlashPhotoApp::OnWindowResize(int new_width, int new_height) {
  image_editor->pixel_buffer()->Resize(new_width, new_height);
  display_texture_ = mingfx::Texture2D();
  display_texture_.InitFromFloats(image_editor->pixel_buffer()->width(),
                                  image_editor->pixel_buffer()->height(),
                                  image_editor->pixel_buffer()->data());
}

} /* namespace image_tools */
