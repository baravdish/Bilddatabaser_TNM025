#include <iostream>
#include <opencv2/opencv.hpp>

#include "DB.hpp"
#include "Image.hpp"

int main()
{
	/*

	// Setup directory and folder paths, no recursive solution yet

	// ----> Directory for: KRISTOFER <-----
	//string mainDirectory = "C:/Users/StoffesBok/Bilddatabaser_TNM025/dataset/";
	//cv::Mat image_temp = imread("C:/Users/StoffesBok/Bilddatabaser_TNM025/dataset/zlatan/zlatan_blue_background_1920x1080.jpg", 1);

	// ----> Directory for: GABRIEL <-----
	cv::Mat image_temp = imread("C:/Users/Gabriel/Desktop/Bildatabaser/Bilddatabaser_TNM025/dataset/zlatan/zlatan_blue_background_1920x1080.jpg", 1);
	string mainDirectory = "C:/Users/Gabriel/Desktop/Bildatabaser/Bilddatabaser_TNM025/dataset/";

	if (!image_temp.data){
		cout << "Zlatan is too big!" << endl; return -1;
	}
	
	vector<string> inputFolders = { "animal2", "beach2", "cat2", "colorful2",
								    "doll2", "elegant2", "flower2", "food2", "formal2", "garden2" };
	vector<string> animalFolder = { "animal2" };

	// Initilize the database
	DB database = DB();
	database.loadImages(mainDirectory, inputFolders);
	
	DB zlatan_DB = DB(image_temp, 32);
	zlatan_DB.reconstructImageFromDB(database);
	*/

	// A test for color histogram
	Mat src = imread("beach.jpg", 1);
	Mat fake = imread("beach.jpg", 1);
	//imshow("indow", src);
	//cvWaitKey(0);
	//imshow("indow", fake);
	//cvWaitKey(0);

	Mat hsv;
	Mat hsv2;

	cout << "Total: " << src.total() << endl;
	cvtColor(src, hsv, COLOR_BGR2HSV);
	cvtColor(fake, hsv2, COLOR_BGR2HSV);
	int h_bins = 50; int s_bins = 60;
	int histSize[] = { h_bins, s_bins };

	// hue varies from 0 to 179, saturation from 0 to 255
	float h_ranges[] = { 0, 180 };
	float s_ranges[] = { 0, 256 };

	const float* ranges[] = { h_ranges, s_ranges };

	int channels[] = { 0, 1 };
	MatND hist_base;
	MatND hist_base2;

	calcHist(&hsv, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false);
	normalize(hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat());
	
	calcHist(&hsv2, 1, channels, Mat(), hist_base2, 2, histSize, ranges, true, false);
	normalize(hist_base2, hist_base2, 0, 1, NORM_MINMAX, -1, Mat());

	/*
	double error = 0.0;
	int match_index;
	for (int i = 0; i < 3600; i++)
	{
		for (int j = 0; j < 34000; j++)
		{
			double temp_error = compareHist(hist_base, hist_base2, CV_COMP_CORREL);
			if (temp_error > error)
			{
				error = temp_error;
				match_index = j;
			}
		}
		new_zlatan_db.push(db(match_index));
	}
	return new_zlatan_vector;
	*/
	

	system("pause");
	return 0;
}