#ifndef DB_H
#define DB_H
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Image.hpp"
#include "dirent.h"

// Visual studio complains about collision with std and cv...
//using namespace std;

// A simple solution
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

using namespace cv;

class DB
{
	private:
	 	vector<Image> images;
	public:
	    DB(string directory, vector<string> folders);
	    void loadImages();
	    void saveImages();
		void printInvalidImageInformation(vector<int> invalidImages, string folder, int nImages);
		vector<Mat> image_vector;
};
 
#endif