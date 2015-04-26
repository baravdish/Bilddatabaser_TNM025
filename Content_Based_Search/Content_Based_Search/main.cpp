#include <iostream>
#include <vector>
#include "opencv2/highgui/highgui.hpp"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using namespace cv;

// How to a access pixel value in a tiny image (fast method): 
// blue = tiny_image.data[n*tiny_image.cols*tiny_image_channels + m*tiny_image_channels + 0]
// We might consider using LUT if the operations are running very slowly

// Hold image when showed until a key is pressed. 
void holdImshow(const char* window, Mat &src);

// Image type in database: 8UC3 = 8 bit unsigned char 3 channels = 0-255 RGB
int main()
{
	const int n_tiny_images = 100, tiny_image_row = 32, tiny_image_col = 32, n_channels = 3;
	const char* window = "Window";
	const char* image_path = "data/%d.jpg";	// Change path if you want.
	double a = getTickCount();
	vector<Mat> tiny_images_vec;

	
	// Abuse the cap() function in VideoCapture class to read multiple images in a sequence
	VideoCapture cap();
	while (cap.isOpened(image_path))
	{
		Mat src;
		cap.read(src);

		if (!src.data) {cout << "No image left in the folder to read. OR: Could not read image.";  break;}
		
		for (int i = 0; i < n_tiny_images; ++i)
		{
			for (int j = 0; j < n_tiny_images; ++j)
			{
				// Create a Mat pointer and let it point to a region of 32x32 pixels (a tiny image)
				Mat tiny_region_ptr = src.colRange(tiny_image_row*i, tiny_image_row*i + tiny_image_row).rowRange(tiny_image_col*j, tiny_image_col*j + tiny_image_col);
				Mat tiny_image;
				// Save that region - we work on tiny_image from now on
				tiny_region_ptr.copyTo(tiny_image);

				// Store each tiny image in a vector of tiny tiny images
				tiny_images_vec.push_back(tiny_image);

				// TODO: Process each pixel at current tiny image => Do stuff
				//for (int n = 0; n < tiny_image_col; ++n)
				//{
				//	for (int m = 0; m < tiny_image_row; ++m)
				//	{
				//		tiny_image.data[n*tiny_image.cols*n_channels + m*n_channels + 0] /= 2;
				//		tiny_image.data[n*tiny_image.cols*n_channels + m*n_channels + 1] /= 2;
				//		tiny_image.data[n*tiny_image.cols*n_channels + m*n_channels + 2] /= 2;
				//	}
				//}
				
				//holdImshow(window, tiny_image);

			} // END OF: for(n_tiny_images col)
		} // END OF: for(n_tiny_images row)
	} // END OF: while(cap.isOpen())

	a = getTickCount() - a;
	a /= getTickFrequency();
	cout << "\n========================= \n" 
		 << "Total time: " << a*1000 << " ms" << endl;

	return 0;
}

// Create a new window, show image on window and 
// hold it until a key is pressed
void holdImshow(const char* window, Mat &src)
{
	namedWindow(window, 1);
	imshow(window, src);
	waitKey(0);
}