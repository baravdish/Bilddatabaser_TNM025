#ifndef IMAGE_H
#define IMAGE_H
#include <iostream>
#include <vector>
#include <opencv2\opencv.hpp>

class Image
{
	private:
	 	Mat img; // This is image_src.
		Mat pixel_values_mat_RGB; // A mat containing all the RGB values of that image in a Nx3 matrix
		Mat pixel_values_mat_IC2; // ^... but for IC2

		vector<double> eigenvectors;
		vector<double> eigenvalues;
		Mat histogram_RGB;
		Mat histogram_IC2;
		Mat correlation_matrix;

	public:
	    Image(Mat image_src); // Constructor, image matrix needed
		Mat getImage(); // Return this image matrix
	    void print(); // Prints the pixel values of this image and imshow the image

		Mat generateCorrelationMatrixRGB(Mat RGB_pixels);
		void calculateEigenvectors();
		void calculateEigenvalues();
		void print(int x, int y); // Prints the pixel value (RGB/IC2) in specific pixel
};
 
#endif