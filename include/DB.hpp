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
	 	vector<Image> images_;
		std::map<string, int> folderSizes_;
		DIR *directory_path_;
	public:
	    DB();
		void loadImages(string directory, vector<string> folders);
	    void saveImages();
		void printInvalidImageInformation(vector<int> invalidImages, string folder, int nImages);
		vector<Image> getImageDatabase();
		Image getImage(int n);
		Mat getImageMat(int n);
};
 
#endif