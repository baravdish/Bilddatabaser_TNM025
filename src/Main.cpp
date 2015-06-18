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
	string image_name = "zlatan_blue-yellow_background_1440x900.jpg";

	// ----> Directory for: KRISTOFER <-----
	//string mainDirectory = "C:/Users/StoffesBok/Bilddatabaser_TNM025/dataset/";
	//cv::Mat image_temp = imread("C:/Users/StoffesBok/Bilddatabaser_TNM025/dataset/zlatan/zlatan_blue_background_1920x1080.jpg", 1);

	// ----> Directory for: GABRIEL <-----
	string mainDirectory = "C:/Users/Gabriel/Desktop/Bildatabaser/Bilddatabaser_TNM025/dataset/";
	Mat image_temp = imread("C:/Users/Gabriel/Desktop/Bildatabaser/Bilddatabaser_TNM025/dataset/zlatan/" + image_name, 1);

	if (!image_temp.data){
		cout << "Zlatan is too big!" << endl; return -1;}
	
	string extension = "2"; // 2 => 32x32, 3 => 16x16, 4 => 8x8
	int patch_size = 32;

	vector<string> inputFolders = { "andy_warhol", "animal", "beach", "cat", "claude_monet", "colorful",
								    "doll", "elegant", "flower", "food", "formal", "garden" };
	
	vector<string> animalFolder = { "animal4", "garden4", "beach"};

	for (int i = 0; i < inputFolders.size(); i++)
		inputFolders[i] += extension;

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
		char *name = "Rendering";
		char *original = "Original";
		namedWindow(name, CV_WINDOW_FULLSCREEN);
		namedWindow(original, CV_WINDOW_FULLSCREEN);

		if (!cap.isOpened())
		{
			cout << "Could not open the camera! " << endl;
			return -1;
		}

		int count = 0;
		vector<double> times;
		while (true)
		{	
			double t = (double)getTickCount();
			Mat frame;
			
			// Grab a frame from camera
			cap >> frame;
			resize(frame, frame, Size(300, 300), 0, 0, INTER_AREA);
			imshow(original, frame);

			double a = (double)getTickCount();
			// Create a database of patches from a query image
			Mosaic zlatan = Mosaic(frame, patch_size);
			a = ((double)getTickCount() - a) / getTickFrequency();

			// Match similar images in the mosaic with the database with PCA/KLT and L2-norm
			zlatan.matchSimiliarImage(database);
			

			// Reconstruct the matched images
			zlatan.reconstructImageFromDB();

			double b = (double)getTickCount();
			t = (b - t) / getTickFrequency();
			count++;
			if (count % 1 == 0)
			{
				cout << "TOTAL TIME: " << t << endl;
				cout << "TIME FOR CONSTRUCTOR: " << a << endl;

				cout << "FPS: " << (double) (1.0 / t)<< endl;
				count = 0;
			}

			//resize(zlatan.image_result_, zlatan.image_result_, Size(200, 200), 0, 0, INTER_AREA);
			imshow(name, zlatan.image_result_);
			
			cvWaitKey(1);
		}
	}
	else
	{
		// Create a database of patches from a query image
		Mosaic zlatan = Mosaic(image_temp, patch_size);

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