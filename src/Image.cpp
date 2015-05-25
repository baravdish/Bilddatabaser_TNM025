#include "Image.hpp"
 
// Constructor
Image::Image(Mat image_src) :
img(image_src)
{

}

CorrelationMatrix Image::generateCorrelationMatrix()
{

}

// Prints the pixel values of this image and imshow the image
void Image::print()
{
	// Show the image
	imshow(img);

	// Print the matrix
	for(int i=0; i < img.rows; i++)
	{
		for(int j=0; j < img.cols; j++)
    	{
    		cout << img.at<Vec3b>(i,j)[0] << " " 
				 << img.at<Vec3b>(i,j)[1] << " " 
				 << img.at<Vec3b>(i,j)[2] << " | ";
    	}
    	cout << endl;
	}	
}

