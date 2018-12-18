High-Level Design  {#highdesign}
===========

This page includes a discussion of the overall design of the project,
using UML-like diagrams to illustrate major classes so that new
developers can quickly understand the structure of the project.

Overall, there are three main parts in this project, which are imagetools,
flashphoto and mia. Generally, their relationship is like below:
![](../../docs/images/overall.png)
In details, part of the official UML diagram is like below, except the filters
part.
![](../../docs/images/edit.png)

# imagetools
It is a library that contains all the basic classes. Specifically, there are
some fundamental classes, a set of tool and filter classes, and a comprehensive
class that uses the former two types of stuff.

## Fundamental calsses
- image_tools::ColorData stores color in floating point format. The Red, Green,
Blue, and Alpha channels range from 0.0 to 1.0.
- image_tools::FloatMatrix holds a 2D array of floats that can be accessed by
(row,column). It also includes a number of utility functions for working with
the array, such as normalizing it or multiplying every element by some scale
factor.
- image_tools::ImageToolsMath A static class that holds several small
math-related functions that are useful for manipulating images, and it stores
all the useful math functions that will be used to implement other functions.
- image_tools::MaskFactory is used to create masks used by image editing tools.
Some of the masks are used by more than one tool.
- image_tools::PixelBuffer stores an array of ColorData, such as an image that
can be drawn to the screen.

## Tool classes
Overall, it uses factory pattern, which is a creational pattern that uses
factory methods to deal with the problem of creating objects without having to
specify the exact class of the object that will be created.

Specifically, here are more descriptions of them:
- image_tools::ToolBlur	serves as a mobile version of the blur filter,
functions much like the spray can, except with blurring neighboring pixels
rather than coloring them (linear falloff).
- image_tools::ToolCalligraphyPen	This tool simulates a Calligraphy Pen,
meaning it paints with a different thickness depending on which direction it is
moved. It has a oval mask tilted at an angle of 70 degrees counter-clockwise
from the x-axis and an elongation ratio of 0.333.
- image_tools::ToolChalk	This tool simulates chalk drawing on a rough paper.
The class overrides Tool's default color blending function to insert random
noise as the tool is moved around.
- image_tools::ToolEraser	This tool simulates an Eraser. It overrides the
Tool's StartStroke method to change the paint_color to be the canvas's
background color.
- image_tools::ToolHighlighter	This tool simulates a Highlighter. It has a
semi-transparent oval mask. It overrides the default Tool's color blend
function to make the blending dependent upon the luminance of the underlying
canvas color.
- image_tools::ToolPen	The simplest of tools, this has a mask that is a
completely opaque circle.
- image_tools::ToolSprayCan	This tool has a linear falloff so that it looks
like the paint has been sprayed onto the canvas. It also has the interesting
property that it continues to paint even when held stationary so paint
continues to accumulate on the canvas the longer you hold it still.
- image_tools::ToolStamp	Stamps a single X marks the spot.

- Below is a UML-like diagram that depicts the hierarchy of tools.
![](../../docs/images/toolpics.png)

## Filter classes
Overall, it uses template pattern, which is a behavioral design pattern that
defines the program skeleton of an algorithm in an operation, deferring some
steps to subclasses.

Specifically, here are more descriptions of them:
- image_tools::Filter	is the super class that includes two subparts, which
represent simple or convolution filters.
- image_tools::FilterChannel is a simpler filter that changes the color,
through multiplying given input scale values and original color values.
- image_tools::FilterQuantize	is a simpler filter that reduces the number of
colors in the image by binning. Adjust each color channel value to put it into
the nearest bin.
- image_tools::FilterSaturate	is a simpler filter that changes the colorfulness
of images.
- image_tools::FilterThreshold is a simpler filter that turns any pixel with an
average. intensity value greater than the threshold parameter set in the GUI to
white; otherwise turn the pixel black.

- image_tools::ConvolutionFilter is	a super class of multiple convolution
filters, which uses kernel Also a subclass of Filter.
- image_tools::ConvolutionFilterBlur is a convolution filter that uses a
Gaussian Blur image convolution kernel to blur the image in proportion to the
amount specified in the GUI.
- image_tools::ConvolutionFilterEdge is a convolution filter that transforms
the image into one that only shows the edges of shapes by convolving it with a
3x3 edge detection kernel. Pixels on the border of differently colored regions
will be bright, while pixels in areas of low change will be dark.
- image_tools::ConvolutionFilterMotionBlur is a convolution filter that blurs
the image by convolving it with an appropriate motion-blurring kernel Support
four possible blurring direstions and blur according to the amount specifies in
the GUI.
- image_tools::ConvolutionFilterSharpen	 is a convolution filter that sharpens
the image (accentuate the edges of shapes) in proportion to the amount
specifies in the GUI by convolving the image with an appropriate sharpening
kernel.

- Below is a UML-like diagram that depicts the hierarchy of filters.
![](../../docs/images/filterpic.png)
- And another more detailed one.
![](../../docs/images/cit.png)

## The comprehensive class
- image_tools::ImageEditor is the major class of the IMAGETOOLS application. In
the model-view-controller paradigm, we can think of this class as implementing
the model for an ImageEditor that could be controlled by various controllers
(e.g.,interactive mouse and keyboard, command line) and viewed different ways
(e.g.,interactively with a GUI, with files written to disk).
- Below is the UML diagram for ImageEditor, showing how it utilizes tools and
filters.


# flashphoto
There is only one major class actually used to manipulate Flashphoto
application.

**image_tools::FlashPhotoApp** is the FlashPhoto GUI, a graphics application
class. This class creates a graphics window to display the current PixelBuffer
and a graphical user interface to interact with it using Tools and Filters.

# mia
- Since mia has Command Line Mode, there is an essential class called
image_tools::CommandLineProcessor, which is a class used to create, store and
run all commands from user input.
* image_tools::ImageEditorCommand includes a set of subclasses that can be used
to apply different filters and execute the corresponding commands.
  * Below is a UML-like diagram showing the hierarchy.
![](../../docs/images/imageeditorcommand.png)

- image_tools::MiaApp	is the Mia GUI, a graphics application class. This class
creates a graphics window to display the current PixelBuffer and a graphical
user interface to interact with it using Tools and Filters.

Generally both falshphoto and mia are GraphicsApp.
![](../../docs/images/appuse.png)

**Citations:** <br/>
- [Filter Design
Workshop](https://umn.instructure.com/courses/73375/files?preview=4111233)
- [Template pattern](https://en.wikipedia.org/wiki/Template_method_pattern)
- [Factory pattern](https://en.wikipedia.org/wiki/Factory_method_pattern)


[Go back to Developer Tutorial](@ref devtutorial)
