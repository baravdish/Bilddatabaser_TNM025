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
	 	vector<Image> images_; // Vector containing all the image objects in this DB
		std::map<string, int> folderSizes_;
		int nImages; // Number of images in this DB
		Mat image; // A source image. Only used with second constructor. Null if initiated without source image.
		vector<Image> similar_images; // Vector containing similar images to the source image
		Mat reconstrucedImage; // A reconstruced large image from similar smallar images. Same size as source image-matrix.
		Mat histogramMatrix; // A matrix of size (nImages x nBin^3)
		Mat correlationMatrix; // A matrix of size (nBin^3 x nBin^3)
		Mat eigenVectors; // A matrix of size (nBin^3 x nImages). NB! nImages can be changed (e.g 20) depending on how many of the largest eigenvalues we want for PCA.
		Mat PCA; // A matrix of size (nImages x nEigenVectors)
		DIR *directory_path_;

	public:
		// Constructors
	    DB(); // Create a new empty DB without source Image
	    DB(Mat img_source, int size_of_patches); // Create a new DB from a source Image

		// Image to DB initialization
		void loadImages(string directory, vector<string> folders); // Loads images from folders
		void saveImage(Mat image, string image_name); // Saves the desired image to desktop as JPG
		void printInvalidImageInformation(vector<int> invalidImages, string folder, int nImages);

		// Image histogram matching
		Mat queryImageHistogram(Mat histogram, int index); // Get histogram for query image
		Mat similiarImagePCA(Mat histogram, Mat queryImage); // Get the similar image
		void saveSimilarImage(Mat similarImage); // Push back the similar image to similar image vector

		// Set functions
		void reconstructImageFromDB(DB matched_images_DB, string image_name); // Construct an image from the matched DB and source image
		void setHistogramMatrix(vector<Image> imageMatrices); // sets the histogram matrix
		void setCorrelationMatrix(Mat histogram); // sets the correlation matrix
		void setEigenVectors(Mat C); // sets the eigenvectors
		void setPCA(Mat E); // sets the PCA
		
		// Get functions
		int getNImages(); // Returns the number of images in this DB
		vector<Image> getImageDatabase(); // Returns the images vector
		vector<Image> getSimilarImages(); // Returns similar images
		Image getImage(int n); // Returns the image object at position n in images vector
		Mat getImageMat(int n); // Returns the mat from the image object at position n in images vector
		Mat getHistogramMatrix(); // Returns the Histogram Matrix
		Mat getCorrelationMatrix(); // Returns the Correlation Matrix
		Mat getEigenVectors(); // Returns the eigenVectors
		Mat getPCA(); // Returns the PCA
};
 
#endif