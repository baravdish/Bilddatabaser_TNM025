#ifndef IMAGE_H
#define IMAGE_H
#include <iostream>
#include <vector>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;

class Image
{
	private:
		const int BIN_SIZE = 4; // The size of bins
		Mat pixel_values_mat_RGB_; // A mat containing all the RGB values of that image in a Nx3 matrix
		Mat pixel_values_mat_IC2_; // ^... but for IC2
		Mat histogram_;
		Mat image_mat_; // This is image_src.

	public:
		// Constructor
	    Image(Mat image_src); // Constructor, image matrix needed
		// Set functions
		void setRGB(Mat image_src);
		void setHSV(Mat image_src);
		void setHistogram(Mat image_src);

		// Get functions
		Mat getImageMat();
		Mat getHistogram();
		Mat getRGB();
		Mat getHSV();
		
		// Trace
		void show(); // Imshow the image
		void print(); // Prints the pixel values of this image and imshow the image
		void print(int x, int y); // Prints the pixel value (RGB/IC2) in specific pixel
};
 
#endif