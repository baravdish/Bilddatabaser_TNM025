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
		const int N_EIGENVECTORS = 25; 
		const int BIN_SIZE = 4; // (4x4x4)
		const int nClusters_ = 100; // Golden rule nClusters = sqrt(nImages/2)
		const int nAttempts_ = 20;

	 	vector<Image> images_; // Vector containing all the image objects in this DB
		std::map<string, int> folderSizes_;
		int nImages; // Number of images in this DB
		Mat histogramMatrix_; // A matrix of size (nImages x nBin^3)
		Mat correlationMatrix_; // A matrix of size (nBin^3 x nBin^3)
		Mat eigenVectors_; // A matrix of size (nBin^3 x nImages). NB! nImages can be changed (e.g 20) depending on how many of the largest eigenvalues we want for PCA.
		Mat histoEig_; // A matrix of size (nImages x nEigenVectors)
		DIR *directory_path_; // A pointer to a 'directory-object' to read files in folder

	public:
		vector<int> labels_;
		Mat centers_;
		vector<vector<int>> labelIndexes_;
		vector<Mat> clusters_;

		// Constructors
	    DB(); // Create a new empty DB without source Image
		// Image to DB initialization
		void loadImages(string directory, vector<string> inputFolders); // Loads images from folders
		void printInvalidImageInformation(vector<int> invalidImages, string folder, int nImages); // Print information about images that were not successfully loaded
		void initializeMatrices(); // Initializes all the matrices in this DB - corr, eig, hist...

		// Set functions
		void setHistogramMatrix(vector<Image> imageMatrices); // sets the histogram matrix
		void setCorrelationMatrix(Mat H); // sets the correlation matrix
		void setEigenVectors(Mat H); // sets the eigenvectors
		void setHistoEig(Mat H, Mat E); // sets the PCA
		void setKMeans(int nClusters, int nAttempts); // sets the K-means cluster for the database
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