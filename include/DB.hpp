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
		
	public:
	    DB();
		void loadImages(string directory, vector<string> folders);
	    void saveImages();
		void printInvalidImageInformation(vector<int> invalidImages, string folder, int nImages);
		vector<Image> getImageDatabase();
		Mat getImage(int n);
};
 
#endif