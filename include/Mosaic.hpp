#ifndef MOSAIC_H
#define MOSAIC_H
#include <iostream>
#include <vector>
#include <opencv2\opencv.hpp>
#include "DB.hpp"
#include "Image.hpp"

using namespace std;
using namespace cv;

class Mosaic
{
private:
	const int SIZE_OF_PATCH;// (32x32 large patches)
	const int BIN_SIZE = 4;
	Mat image_source_; // This image source
	
	vector<Image> similar_image_; // Contains similar images in the same order as the DB

	// Set the images for this mosaic to a DB
	void setImagesDB();
	DB imagesDB;

public:
	Mat image_result_; // The mosaic
	// Constructor
	Mosaic(Mat image, int patch_size);

	// Save the image to JPG
	void saveImage(string image_name); // Saves the result image to desktop as JPG
	
	// Image histogram matching
	void matchSimiliarImage(DB database); // Get the similar image
	void pushSimilarImage(Image similarImage); // Push back the similar image to similar image vector

	// Set functions
	void reconstructImageFromDB(); // Construct an image from the matched DB and source image
	
	// Calculate L2-norm between a query vector and row-wise vectors in matrix
	int L2Norm(Mat qHistoEigVec, Mat histoEig);
	int L1Norm(Mat qHistoEigVec, Mat histoEig);

	// Get functions
	Mat getImageSource();
	Mat getImageResult();
	DB getImagesDB();

};

#endif