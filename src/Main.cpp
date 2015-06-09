#include <iostream>
#include <opencv2/opencv.hpp>

#include "DB.hpp"
#include "Image.hpp"

int main()
{
	// Setup directory and folder paths, no recursive solution yet

	// ----> Directory for: KRISTOFER <-----
	//string mainDirectory = "C:/Users/StoffesBok/Bilddatabaser_TNM025/dataset/";
	//cv::Mat image_temp = imread("C:/Users/StoffesBok/Bilddatabaser_TNM025/dataset/zlatan/zlatan_blue_background_1920x1080.jpg", 1);

	// ----> Directory for: GABRIEL <-----
	cv::Mat image_temp = imread("C:/Users/Gabriel/Desktop/Bildatabaser/Bilddatabaser_TNM025/dataset/zlatan/zlatan_blue_background_1920x1080.jpg", 1);
	string mainDirectory = "C:/Users/Gabriel/Desktop/Bildatabaser/Bilddatabaser_TNM025/dataset/";
	char a;
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
	
	// A test for color histogram
	/*Mat src = imread("test.png", 1)
	cout << "Total: " << src.total() << endl;

	int r_bins = 2;
	int g_bins = 2;
	int b_bins = 2;
	const int hist_size[] = { r_bins, g_bins, b_bins };

	float r_range[] = { 0, 255 };
	float g_range[] = { 0, 255 };
	float b_range[] = { 0, 255 };
	const float *hist_range[] = { r_range, g_range, b_range };

	cv::Mat histos;

	bool uniform = true;
	bool accumulate = false;
	int channels[] = { 0, 1, 2 };
	// Check if channels and dims is correct
	calcHist(&src, 1, channels, Mat(), histos, 3, hist_size, hist_range, uniform, accumulate);
	
	//cout << "size" << histos.size[0] << endl;
	//cout << " x " << histos.size[1] << endl;
	//cout << " x " << histos.size[2] << endl;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{	
				cout << "B: " << i << endl;
				cout << "G: " << j << endl;
				cout << "R: " << k << endl;
				cout << histos.at<Vec3b>(i, j, k) << " " << endl;
			}
		}		


	}
	*/

	system("pause");
	return 0;
}