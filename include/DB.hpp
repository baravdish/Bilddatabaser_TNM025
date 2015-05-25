#ifndef DB_H
#define DB_H
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Image.hpp"
#include "dirent.h"

//using namespace std;

// Visual studio complains about collision with std and cv.
// A simple solution...
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::map;
using namespace cv;

class DB
{
	private:
	 	vector<Image> images;
		vector<Mat> image_vector;
	public:
	    DB(string directory, vector<string> folders);
	    void loadImages();
	    void saveImages();
		void printInvalidImageInformation(vector<int> invalidImages, string folder, int nImages);
		vector<Mat> getImageDatabase();
};
 
#endif