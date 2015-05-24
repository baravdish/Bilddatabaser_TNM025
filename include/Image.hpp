#ifndef IMAGE_H
#define IMAGE_H
#include "CorrelationMatrix.hpp"
#include <iostream>
#include <vector>
#include <opencv2\opencv.hpp>

class Image
{
	private:
	 	Mat img;
	 	vector<CorrelationMatrix> correlation_mat_RGB;
	 	vector<CorrelationMatrix> correlation_mat_IC2;
	public:
	    Image(Mat image_src);
	    void print(); // Prints the pixel values of this image and imshow the image
	    CorrelationMatrix generateCorrelationMatrix();
};
 
#endif