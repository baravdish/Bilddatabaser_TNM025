#ifndef IMAGE_H
#define IMAGE_H
#include "CorrelationMatrix.hpp"
#include <iostream>
#include <vector>
#include <opencv2\opencv.hpp>
#include <CorrelationMatrix.hpp>

class Image
{
	private:
	 	Mat img;
	 	vector<CorrelationMatrix> correlation_mat_RGB;
	 	vector<CorrelationMatrix> correlation_mat_IC2;
	public:
	    Image(Mat image_src); // Constructor, image matrix needed
		Mat getImage(); // Return this image matrix
	    void print(); // Prints the pixel values of this image and imshow the image
		void print(int x, int y); // Prints the pixel value (RGB/IC2) in specific pixel
	    CorrelationMatrix generateCorrelationMatrix();
};
 
#endif