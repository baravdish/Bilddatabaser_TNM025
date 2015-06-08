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
	 	vector<Image> images;
		std::map<string, int> folderSizes;
		Mat image; // Loaded image that is remade to a DB
		
	public:
	    DB();
	    DB(Mat img_source, int size_of_patches); // Create a DB from an Image
		void loadImages(string directory, vector<string> folders);
	    void saveImages();
		void printInvalidImageInformation(vector<int> invalidImages, string folder, int nImages);
		vector<Image> getImageDatabase();
		Image getImage(int n);
		Mat getImageMat(int n);
};
 
#endif