#include "Mosaic.hpp"

// Constructor
Mosaic::Mosaic(Mat image) :
image_source(image)
{

}

Mat Mosaic::getImageSource()
{
	return image_source;
}
