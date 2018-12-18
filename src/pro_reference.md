Programming Reference  {#proreference}
===========

All codes in the project:

If you want to see the classes at an alphabetical order,
[**go to Class Index**](classes.html).

Otherwise below is a summary of major classes.

# Inside the library
There is a library **imagetools** that holds the common codes that can be used for both
applications. <br/>

**image_tools::ImageEditor** includes many methods that use almost all
the classes in the library, like applying various filters and tools.

## Tools
image_tools::Tool <br/>
image_tools::ToolStamp <br/>
image_tools::ToolChalk <br/>
image_tools::ToolSprayCan <br/>
image_tools::ToolPen <br/>
image_tools::ToolHighlighter <br/>
image_tools::ToolEraser <br/>
image_tools::ToolCalligraphyPen <br/>
image_tools::ToolBlur

## Basic structure
image_tools::PixelBuffer <br/>
image_tools::MaskFactory <br/>
image_tools::FloatMatrix

## Filters
image_tools::Filter <br/>
image_tools::FilterThreshold <br/>
image_tools::FilterSaturate <br/>
image_tools::FilterQuantize <br/>
image_tools::FilterChannel <br/>
image_tools::ConvolutionFilterSharpen <br/>
image_tools::ConvolutionFilterMotionBlur <br/>
image_tools::ConvolutionFilterEdge <br/>
image_tools::ConvolutionFilterBlur <br/>
image_tools::ConvolutionFilter


# Outside the library
## App classes and codes that use the library
image_tools::FlashPhotoApp <br/>
image_tools::MiaApp

## Command Line Mode for Mia
image_tools::CommandLineProcessor <br/>
image_tools::ImageEditorCommand <br/>


[Go back to Developer Tutorial](@ref devtutorial)
