#include "Image.hpp"
 
// Constructor
Image::Image(Mat image_src)
{
	// The image matrix
	image_matrix = image_src;

	// The size of the matrix
	int rows = image_matrix.rows;
	int cols = image_matrix.cols;
	Size s = image_matrix.size();
	size_x = s.width;
	size_y = s.height;
}

// cout the pixel values of this image and imshow the image
void Image::print()
{
	// Show the image
	imshow(image_matrix);

	// Print the matrix
	cout << "Image matrix = " << endl << " " << image_matrix << endl << endl;
}

