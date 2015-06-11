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
		const int N_EIGENVECTORS = 5;

	 	vector<Image> images_; // Vector containing all the image objects in this DB
		std::map<string, int> folderSizes_;
		int nImages; // Number of images in this DB
		Mat histogramMatrix; // A matrix of size (nImages x nBin^3)
		Mat correlationMatrix; // A matrix of size (nBin^3 x nBin^3)
		Mat eigenVectors; // A matrix of size (nBin^3 x nImages). NB! nImages can be changed (e.g 20) depending on how many of the largest eigenvalues we want for PCA.
		Mat HistoEig; // A matrix of size (nImages x nEigenVectors)
		DIR *directory_path_;

	public:
		// Constructors
	    DB(); // Create a new empty DB without source Image

		// Image to DB initialization
		void loadImages(string directory, vector<string> folders); // Loads images from folders
		void printInvalidImageInformation(vector<int> invalidImages, string folder, int nImages);

		// Set functions
		void setHistogramMatrix(vector<Image> imageMatrices); // sets the histogram matrix
		void setCorrelationMatrix(Mat H); // sets the correlation matrix
		void setEigenVectors(Mat C); // sets the eigenvectors
		void setHistoEig(Mat H, Mat E); // sets the PCA
		void pushBack(Image I); // Pushes a image to the vector
		
		// Get functions
		int getNImages(); // Returns the number of images in this DB
		vector<Image> getImageDatabase(); // Returns the images vector
		Image getImage(int n); // Returns the image object at position n in images vector
		Mat getImageMat(int n); // Returns the mat from the image object at position n in images vector
		Mat getHistogramMatrix(); // Returns the Histogram Matrix
		Mat getCorrelationMatrix(); // Returns the Correlation Matrix
		Mat getEigenVectors(); // Returns the eigenVectors
		Mat getHistoEig(); // Returns the PCA
};
 
#endif