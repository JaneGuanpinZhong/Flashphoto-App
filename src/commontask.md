Common Tasks  {#commontask}
============

This is a tutorial written for other programmers that describes what
they would need to do in order to add a new filter to the project.

* 1. Create the class under "imagetools" directory, including the head files
and implementation files. Put it in the image_tools namespace of course.

  * Complete the constructor, destructor, and other necessary functions.
Details can be different, depending on what you want the filter to do.
However, please remember to match the major functions in supperclasses
image_tools::Filter and/or image_tools::ConvolutionFilter. For instance,
you can look at how function ApplyToBuffer(PixelBuffer* buffer) works
before you start constructing your new filter.

  * Take the saturate filter as an example. As you can see in the picture below,
the basic functions are like those.
![](../../docs/images/satex.png)
And also have a taste of how to implement them, like below:
![](../../docs/images/satexample.png)

* 2. Add the usage function inside class image_tools::ImageEditor, like
"ApplyxxxFilter". Inside it create a new object of the new filter class
with the given parameter, and then apply it to the buffer.

  * See the example of saturate filter below:
![](../../docs/images/applysat.png)

* 3. You are able to use it now. Just call relative usage function from
image_tools::ImageEditor based on an ImageEditor object.

  * Below is an example of applying saturate filter in the Flashpohoto App:
![](../../docs/images/callsat.png)


[Go back to Developer Tutorial](@ref devtutorial)
