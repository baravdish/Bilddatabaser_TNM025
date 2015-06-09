#ifndef DB_H
#define DB_H
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Image.hpp"
#include "dirent.h"

//using namespace std;
using namespace cv;

class DB
{
	private:
	 	vector<Image> images; // Vector containing all the image objects in this DB
		std::map<string, int> folderSizes;
		Mat image; // A source image. Only used with second constructor. Null if initiated without source image.
		DIR *directory_path_;
	public:
	    DB(); // Create a new empty DB without source Image
	    DB(Mat img_source, int size_of_patches); // Create a new DB from a source Image
		void loadImages(string directory, vector<string> folders); // Loads images from folders
	    void saveImage(); // Saves the desired image to desktop as JPG
		void printInvalidImageInformation(vector<int> invalidImages, string folder, int nImages);
		vector<Image> getImageDatabase(); // Returns the images vector
		Image getImage(int n); // Returns the image object at position n in images vector
		Mat getImageMat(int n); // Returns the mat from the image object at position n in images vector
		void reconstructImageFromDB(DB matched_images_DB); // Construct an image from the matched DB and source image
};
 
#endif