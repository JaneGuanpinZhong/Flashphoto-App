Flashphoto Started    {#flashphotostart}
===========
# Welcome to Flashphoto!

Hi! This is a tutorial for users like you to learn more about **Flashphoto**
application and how to use it. Basically it discusses brushes and filters.
Please go through it step by step, and you can also manipulate the application
at the same time.


# Overview

**Flashphoto** is a painting application with filters and special tools. It can
be used to draw and edit some images and make some changes. There are totally
seven tools and eight filters. Below are detailed introductions.


# Tools

## Pen

This tool is designed to look like a pen. It makes an opaque, circular mark
with constant intensity. This means that when the pen is applied to the canvas
the digital ink from the pen completely covers any color that had previously
been applied to the canvas at that position. The color of the pen can be set
interactively using the GUI.
![](../../docs/images/pen.png)

## Calligraphy Pen

This tool is designed to look like a calligraphy pen. It works almost the same
way as the Pen tool. Like the Pen tool, it is completely opaque and it covers
up any “paint” that was flashphotoalready applied to the canvas. However, the
difference with the Calligraphy Pen is that the mask is an oval tilted at a
30-degree angle. The color of the highlighter can be set interactively using
the GUI.
![](../../docs/images/caligraphy.png)

## Chalk

This tool is designed to look like a piece of chalk dragged across a bumpy
surface. It has a circular mask, but about 40% of the pixels within the circle
are randomly chosen to be completely transparent. This creates the bumpy
effect. The chalk color can be set interactively using the GUI.
![](../../docs/images/chalk.png)

## Highlighter

This tool is designed to look like a highlighter marker. It uses an oval mask
similar to the Calligraphy Pen, but the oval is oriented vertically, and the
intensity of the mask is set to make the mark semi-transparent. The color
applied to the canvas is approximately 40% the color of the highlighter and 60%
whatever color is already on the canvas; however, a special color blending
function is used for the highlighter so that dark colors show through more than
light colors. The color of the highlighter’s ink can be set interactively using
the GUI.
![](../../docs/images/highlighter.png)

## Spray Can

This tool is designed to mimic the look of paint from a spray can. It uses a
special mask that is circular in shape but has a linear falloff to mimic the
dispersion of color from the spray. The intensity is strongest at the center
pixel and falls off linearly to zero intensity at the edge of the circle. The
specific paint color can be set interactively using the GUI.
![](../../docs/images/spraycan.png)

## Eraser
This tool erases the digital canvas and returns it to its original background
color. It has a circular mask, and eraser’s color cannot be changed through the
GUI because there is currently no user interface for changing the canvas
background color. You can see the image below where the eraser moves something.
![](../../docs/images/eraser.png)


# Filters
In order to show the changes clearly, here we draw something and take it as the
original image. And see specific filter influence under each subsection.
![](../../docs/images/original.png)

## Threshold Filter
Each of the color channels will be rounded up to the maximum value of 1.0 or
down to the minimum value of 0.0 based on whether the pixel’s value is greater
or less than the GUI input value, respectively. Below is the result using
cutoff value of 0.5.
![](../../docs/images/threshold.png)

## Saturation Filter
Increase or decrease the colorfulness of the image. Below is the result using
amount of 3.71.
![](../../docs/images/saturate.png)

## Channels Filter
Independently scale up or down the intensity of each color channel (red, green,
and blue). Below is the result using R, G, B channels of 2.35, 1.00 and 1.29
correspondingly.
![](../../docs/images/channels.png)

## Quantize Filter
Reduce the number of colors in the image by binning. If using 4 bins, there
will only be 4 possible intensity values for each color channel, spaced evenly:
0%, 33%, 66%, and 100%. Adjust each color channel value R, G, and B to put it
into the nearest bin. Below is the result using number of bins of 6.
![](../../docs/images/quantize.png)

## Blur Filter
Use a Gaussian Blur image convolution kernel to blur the image in proportion to
the amount specified in the GUI. Below is the result using blur amount of 5.
![](../../docs/images/blur.png)

## Motion Blur Filter
Blur the image by convolving it with an appropriate motion-blurring kernel.
Support four possible blurring directions (North-to-South, East-to-West,
Northeast-to-Southwest, and Northwest-to-Southeast) and blur according to the
amount specified in the GUI. Below is the result using blur amount of 5 and
direction of North/South.
![](../../docs/images/motion.png)
Below is the result using blur amount of 5 and direction of East/West.
![](../../docs/images/motionew.png)
Below is the result using blur amount of 5 and direction of Northeast/Southwest.
![](../../docs/images/motionne-ws.png)
Below is the result using blur amount of 5 and direction of NorthWest/Southeast.
![](../../docs/images/motionnw-se.png)


## Sharpen Filter
Sharpen the image (accentuate the edges of shapes) in proportion to the amount
specified in the GUI by convolving the image with an appropriate sharpening
kernel. Below is the result using amount of 5.
![](../../docs/images/sharpen.png)

## Edge Detection Filter
Transform the image into one that only shows the edges of shapes by convolving
it with a 3x3 edge detection kernel. Pixels on the border of differently
colored regions will be bright, while pixels in areas of low change will be
dark.
![](../../docs/images/edge.png)

# Other buttons
There are four more buttons which play fundamental roles in the application.

## Tool color
You can choose your color for tools here.
![](../../docs/images/toolcolor.png)

## Tool size
You can choose your tool size here.
![](../../docs/images/toolsize.png)

## Open a file
You can open a picture through clicking **Open** button, then choosing a file
from a local folder.

## Save a file
You can save any picture with or without edition by clicking **Save** button,
then choosing a folder and naming the image.
![](../../docs/images/opensave.png)

## Undo
You can undo any behavior through clicking **Undo** button.

## Redo
You can undo any behavior through clicking **Redo** button.
![](../../docs/images/undoredo.png) <br/>

[Go back to User Tutorial](@ref usertutorial)
