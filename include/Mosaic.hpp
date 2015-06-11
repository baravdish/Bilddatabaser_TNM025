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
	Mat image_source;
	DB images;

public:
	// Constructor
	Mosaic(Mat image);

	// Set functions

	// Get functions
	Mat getImageSource();

};

#endif