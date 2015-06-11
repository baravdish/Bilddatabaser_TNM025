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
	const int SIZE_OF_PATCH = 32; // (32x32 large patches)
	Mat image_source; // This image source
	Mat image_result; // The mosaic

	// Set the images for this mosaic to a DB
	void setImagesDB();
	DB imagesDB;

	

public:
	// Constructor
	Mosaic(Mat image);

	// Save the image to JPG
	void saveImage(string image_name); // Saves the desired image to desktop as JPG

	// Image histogram matching
	Mat queryImageHistogram(Mat histogram, int index); // Get histogram for query image
	Mat similiarImagePCA(Mat histogram, Mat queryImage); // Get the similar image
	void pushSimilarImage(Mat similarImage); // Push back the similar image to similar image vector

	// Set functions
	void reconstructImageFromDB(DB matched_images_DB, string image_name); // Construct an image from the matched DB and source image

	// Get functions
	Mat getImageSource();

};

#endif