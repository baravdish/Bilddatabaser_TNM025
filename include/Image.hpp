#ifndef IMAGE_H
#define IMAGE_H
#include <iostream>
#include <vector>
#include <opencv2\opencv.hpp>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

using namespace cv;

class Image
{
	private:
		Mat pixel_values_mat_RGB_; // A mat containing all the RGB values of that image in a Nx3 matrix
		Mat pixel_values_mat_IC2_; // ^... but for IC2
		Mat b_hist_, g_hist_, r_hist_;
		Mat histogram_IC2_;
		Mat correlation_matrix_RGB_;
		Mat correlation_matrix_IC2_;
		Mat eigenvectors_;
		Mat eigenvalues_;
		Mat image_mat_; // This is image_src.
	public:
		
	    Image(Mat image_src); // Constructor, image matrix needed
		Mat getEigenvalues();
		Mat getEigenvectors();
		Mat getCorrelationMatrixRGB();
		Mat getImageMat();
		void calculateCorrelationMatrixRGB(Mat RGB_pixels);
		void calculateHistograms(Mat image_src, int hist_size, float range[]);
		void calculateEigvalAndEigvec();
		void print(); // Prints the pixel values of this image and imshow the image
		void print(int x, int y); // Prints the pixel value (RGB/IC2) in specific pixel
};
 
#endif