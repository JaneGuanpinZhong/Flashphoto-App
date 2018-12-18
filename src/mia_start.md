Mia Started   {#miastart}
===========
# Welcome to Mia!

Hi! This is a tutorial for users like you to learn more about **Mia**
application and how to use it. Basically it discusses loading images and
annotating them. Please go through it step by step, and you can also manipulate
the application at the same time.


# Overview

**Mia** is a medical imaging analysis application with filters and special tools. It can
be used to edit medical images and make some special marks.

Firstly we are going to load a image to the buffer, since loading files is one
of the most important usages of Mia application. Here we use an X-ray teeth
image as an example.

## Open a file
You can open a picture through clicking **Open** button, then choosing a file
from a local folder.
![](../../docs/images/teeth.png)

## Save a file
You can save any picture with or without edition by clicking **Save** button,
then choosing a folder and naming the image.
![](../../docs/images/opensave.png)

## Undo
You can undo any behavior through clicking **Undo** button.

## Redo
You can undo any behavior through clicking **Redo** button.
![](../../docs/images/undoredo.png)

**After loading the image to the buffer, we can choose tools and filters to
annotate them.**

# Tools
We have two tools "mark" and "pen", and they are introduced below.

## Pen
This tool is designed to look like a pen. It makes an opaque, circular mark
with constant intensity. This means that when the pen is applied to the canvas
the digital ink from the pen completely covers any color that had previously
been applied to the canvas at that position. The color of the pen can be set
interactively using the GUI.

For example, here we circle the areas which we want to emphasize.
![](../../docs/images/penteeth.png)

## Mark
It is a red stamp that can emphasize some areas of the images, so that other
users can see them as well. It increases the efficiency of the assessment for
patients.

For example, here we put the stamps at the areas which we want to emphasize.
![](../../docs/images/markteeth.png)


# Filters
## Threshold Filter
Each of the color channels will be rounded up to the maximum value of 1.0 or
down to the minimum value of 0.0 based on whether the pixel’s value is greater
or less than the GUI input value, respectively. Below is the result using
cutoff value of 0.5.
![](../../docs/images/threshold0.5teeth.png)


## Quantize Filter
Reduce the number of colors in the image by binning. If using 4 bins, there
will only be 4 possible intensity values for each color channel, spaced evenly:
0%, 33%, 66%, and 100%. Adjust each color channel value R, G, and B to put it
into the nearest bin. Below is the result using number of bins of 5.
![](../../docs/images/quantize5teeth.png)


## Blur Filter
Use a Gaussian Blur image convolution kernel to blur the image in proportion to
the amount specified in the GUI. Below is the result using blur amount of 5.
![](../../docs/images/blur5teeth.png)

## Sharpen Filter
Sharpen the image (accentuate the edges of shapes) in proportion to the amount
specified in the GUI by convolving the image with an appropriate sharpening
kernel. Below is the result using amount of 5.
![](../../docs/images/sharpen5teeth.png)


## Edge Detection Filter
Transform the image into one that only shows the edges of shapes by convolving
it with a 3x3 edge detection kernel. Pixels on the border of differently
colored regions will be bright, while pixels in areas of low change will be
dark.
![](../../docs/images/edgeteeth.png)

## Another button: Tool color
You can choose your color for tools here.
![](../../docs/images/toolcolor.png)

# Command Line mode
Mia has an interesting characteristic, that it can be manipulated by command
lines. You can just type something in the terminal, and immediately get the
output image file at the corresponding directory.

You can go to build/bin/mia after you make it, and then type the image you want
to edit, whatever filters you want to use, and the name of output image. Please
notice that there can be multiple filters between the input and output, but
they must be typed properly. For instance, type "-" before the filter name, and
add the parameter in most cases, except "-edgedetect". Another important point
is that the images must be in ".png" form, otherwise there will be errors. And
also, it is good to know that the output file can exist already, so when you
run those commands, there will be a new version, which will cover the old
one.   

If you do not follow those requirements, say typing illegal commands, you will
get error message, which is also help message, that can suggest what you should
type. Below is what you will see if you want the help message on purpose,
through typing "mia -h".
![](../../docs/images/help.png)

Take saturate filter as an example. Type "build/bin/mia resources/input.png
-saturate 3 resources/output.png". Hit "Enter", then you can see a new  
output.png in resources directory.
![](../../docs/images/ex.png)

[Go back to User Tutorial](@ref usertutorial)
