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
	string mainDirectory = "C:/Users/StoffesBok/Bilddatabaser_TNM025/dataset/";
	cv::Mat image_temp = imread("C:/Users/StoffesBok/Bilddatabaser_TNM025/dataset/zlatan/zlatan_blue_background_1920x1080.jpg", 1);

	// ----> Directory for: GABRIEL <-----

	//string mainDirectory = "C:/Users/Gabriel/Desktop/Bildatabaser/Bilddatabaser_TNM025/dataset/";
	//cv::Mat image_temp = imread("C:/Users/Gabriel/Desktop/Bildatabaser/Bilddatabaser_TNM025/dataset/zlatan/" + image_name, 1);

	if (!image_temp.data){
		cout << "Zlatan is too big!" << endl; return -1;
	}
	
	vector<string> inputFolders = { "animal2", "beach2", "cat2", "colorful2",
								    "doll2", "elegant2", "flower2", "food2", "formal2", "garden2" };
	vector<string> animalFolder = { "animal2" };

	// Initilize the database
	DB database = DB();
	//database.loadImages(mainDirectory, inputFolders);
	//
	//Mosaic zlatan = Mosaic(image_temp);
	//zlatan.reconstructImageFromDB(database);
	//zlatan.saveImage(image_name);

	Mat src = imread("test.png", 1);
	int histSize[3];
	float hranges[2];
	const float* ranges[3];
	int channels[3];
	// Prepare arguments for a color histogram
	histSize[0] = histSize[1] = histSize[2] = 4;
	hranges[0] = 0.0; // BRG range
	hranges[1] = 256.0;
	ranges[0] = hranges; // all channels have the same range
	ranges[1] = hranges;
	ranges[2] = hranges;
	channels[0] = 0; // the three channels
	channels[1] = 1;
	channels[2] = 2;
	Mat hist;
	cv::calcHist(&src, 1, channels, cv::Mat(), hist, 3, histSize, ranges, true, false);
	
	cout << hist.size[0] << "x" << hist.size[1] << "x" << hist.size[2] << endl;
	cout << hist.channels() << endl;
	cout << hist.total() << endl;
	hist = hist / src.total();
	//cout << x;
	float sum = 0;
	for (int i = 0; i < 4; i++)
	for (int j = 0; j < 4; j++)
	for (int k = 0; k < 4; k++)
	{
		cout << hist.at<float>(i, j, k) << ", ";
		sum = sum + hist.at<float>(i, j, k);
	}

	Mat x = hist.reshape(1);
	cout << x.size() << endl;
	//PCA pca(hist, Mat(), CV_PCA_DATA_AS_ROW, 10);
	//cout << pca.eigenvectors.size;

	cout << endl << "SUM: " << sum << endl;
	
	system("pause");
	return 0;
}