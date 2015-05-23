#include <iostream>
#include <opencv2/opencv.hpp>

#include "Image.h"
#include "CorrelationMatrix.h" // To have objects of matrices
 
// Constructor
Image::Image()
{
	image_matrix = null;
	image_size[0] = null;
   	image_size[1] = null;
}

int Image::getSize()
{
	return image_size;
}

// cout the pixel values of this image and imshow the image
void Image::print()
{

}

