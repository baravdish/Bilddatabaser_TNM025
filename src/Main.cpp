#include <iostream>
#include <opencv2/opencv.hpp>

#include "DB.hpp"
#include "Image.hpp"

int main()
{
	// Setup directory and folder paths, no recursive solution yet

	// ----> Directory for: KRISTOFER <-----
	string mainDirectory = "C:/Users/StoffesBok/Bilddatabaser_TNM025/dataset/";
	// ----> Directory for: GABRIEL <-----
	//string mainDirectory = "C:/Users/Gabriel/Desktop/Bildatabaser/Bilddatabaser_TNM025/dataset/";

	vector<string> inputFolders = { "animal2", "beach2", "cat2", "colorful2",
								    "doll2", "elegant2", "flower2", "food2", "formal2", "garden2" };
	vector<string> animalFolder = { "animal2" };

	// Initilize the database
	DB animal_database = DB();
	animal_database.loadImages(mainDirectory, inputFolders);
	
	cv::Mat image_temp = imread("C:/Users/StoffesBok/Bilddatabaser_TNM025/dataset/zlatan/zlatan_blue_background_1920x1080.jpg", 1);
	DB zlatan_DB = DB(image_temp, 32);
	zlatan_DB.reconstructImageFromDB(animal_database);

	//Image a = animal_database.getImage(1);
	//float range[] = { 0, 255 };
	//animal_database.getImage(1).generateHistograms(a.getImage(), 128, range);

	system("pause");
	return 0;
}