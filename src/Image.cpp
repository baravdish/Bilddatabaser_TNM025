#include "Image.hpp"
 
// Constructor
Image::Image(Mat image_src) :
img(image_src)
{

}

CorrelationMatrix Image::generateCorrelationMatrix()
{
	CorrelationMatrix corr_mat = CorrelationMatrix();
	return corr_mat;
}

// Prints the pixel values of this image and imshow the image
void Image::print()
{
	// Show the image
	if (!img.data)        // Check for invalid input
	{
		std::cout << "Could not open or find the image" << std::endl;
	}
	cv::imshow("Image", img);
	cv::waitKey(10);

	// Print the matrix
	for(int i=0; i < img.rows; i++)
	{
		for(int j=0; j < img.cols; j++)
    	{
			std::cout << (int)img.at<Vec3b>(i, j)[0] << " "
				      << (int)img.at<Vec3b>(i, j)[1] << " "
					  << (int)img.at<Vec3b>(i, j)[2] << " | ";
    	}
		std::cout << std::endl;
	}
	
}

