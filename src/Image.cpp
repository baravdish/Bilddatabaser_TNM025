#include "Image.hpp"
 
// Constructor
Image::Image(Mat image_src) :
img(image_src)
{
	//There are no grayscaled images in current database
	//if (image_src.type() != 16)
		//cvtColor(image_src, img, CV_GRAY2BGR);

	img.convertTo(img, CV_64FC3);
	pixel_values_mat_RGB = img.reshape(1, 3).t();

	generateCorrelationMatrixRGB(pixel_values_mat_RGB);
}

void Image::generateCorrelationMatrixRGB(Mat img_pixel_values)
{
	correlation_matrix_RGB = img_pixel_values.t()*img_pixel_values;
}

// Return correlation matrix for this image
Mat Image::getCorrelationMatrixRGB()
{
	return correlation_matrix_RGB;
}

// Return this image matrix
Mat Image::getImage()
{
	return img;
}

// Return eigenvalues
Mat Image::getEigenvalues()
{
	return eigenvalues;
}

// Return eigenvectors
Mat Image::getEigenvectors()
{
	return eigenvectors;
}

void Image::calculateEigvalAndEigvec()
{
	eigen(correlation_matrix_RGB, eigenvalues, eigenvectors);
}

void generateHistogram()
{

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

void Image::print(int x, int y)
{
	std::cout << img.at<Vec3b>(x, y) << std::endl;
}

