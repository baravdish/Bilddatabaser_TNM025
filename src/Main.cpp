#include <iostream>
#include <opencv2/opencv.hpp>

#include "DB.hpp"
#include "Image.hpp"
#include "Mosaic.hpp"

using namespace std;
using namespace cv;

int main()
{
	// Setup directory and folder paths, no recursive solution yet
	string image_name = "zlatan_blue_background_1920x1080.jpg";

	// ----> Directory for: KRISTOFER <-----
	//string mainDirectory = "C:/Users/StoffesBok/Bilddatabaser_TNM025/dataset/";
	//cv::Mat image_temp = imread("C:/Users/StoffesBok/Bilddatabaser_TNM025/dataset/zlatan/zlatan_blue_background_1920x1080.jpg", 1);

	// ----> Directory for: GABRIEL <-----
	string mainDirectory = "C:/Users/Gabriel/Desktop/Bildatabaser/Bilddatabaser_TNM025/dataset/";
	Mat image_temp = imread("C:/Users/Gabriel/Desktop/Bildatabaser/Bilddatabaser_TNM025/dataset/zlatan/" + image_name, 1);

	if (!image_temp.data){
		cout << "Zlatan is too big!" << endl; return -1;}
	
	string extension = "4"; // 4 => 8x8 3 => 16x16 2 => 32x32

	vector<string> inputFolders = { "animal", "beach", "cat", "colorful",
								    "doll", "elegant", "flower", "food", "formal", "garden" };
	
	for (int i = 0; i < inputFolders.size(); i++)
		inputFolders[i] += extension;



	vector<string> animalFolder = { "animal4" };

	// Initilize the database
	DB database = DB();
	database.loadImages(mainDirectory, inputFolders);
	
	// Choose mode: 
	// 0 if you want to see zlatan
	// 1 if you want to start the cam
#define CAM 1

	if (CAM)
	{
		VideoCapture cap(0);
		char *name = "Window";
		namedWindow(name, CV_WINDOW_FULLSCREEN);
		if (!cap.isOpened())
		{
			cout << "Could not open the camera! " << endl;
			return -1;
		}

		while (true)
		{
			Mat frame;
			
			// Grab a frame from camera
			cap >> frame;
			
			// Create a database of patches from a query image
			Mosaic zlatan = Mosaic(frame);
			
			// Match similar images in the mosaic with the database with PCA/KLT and L2-norm
			zlatan.matchSimiliarImage(database);

			// Reconstruct the matched images
			zlatan.reconstructImageFromDB();

			imshow(name, zlatan.getImageResult());
			cvWaitKey(1);
		}
	}
	else
	{
		// Create a database of patches from a query image
		Mosaic zlatan = Mosaic(image_temp);

		// Match similar images in the mosaic with the database with PCA/KLT and L2-norm
		zlatan.matchSimiliarImage(database);

		// Reconstruct the matched images
		zlatan.reconstructImageFromDB();

		// Write and save the reconstructed image
		zlatan.saveImage(image_name);
	}

	system("pause");
	return 0;
}