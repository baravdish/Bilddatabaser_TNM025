#ifndef IMAGE_H
#define IMAGE_H
#include "CorrelationMatrix.hpp"
#include <iostream>
#include <vector>
#include <opencv2\opencv.hpp>

class Image
{
	private:
	 	Mat image_matrix;
	 	vector<CorrelationMatrix> correlation_mat_RGB;
	 	vector<CorrelationMatrix> correlation_mat_IC2;
	public:
	    Image();
	    void print(); // cout the pixel values of this image and imshow the image
};
 
#endif