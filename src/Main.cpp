#include <iostream>
#include <opencv2/opencv.hpp>

#include "DB.hpp"
#include "Image.hpp"
#include "CorrelationMatrix.hpp"

int main()
{
	// Setup directory and folder paths, no recursive solution yet

	// ----> Directory for: KRISTOFER <-----
	//string mainDirectory = "C:/Users/StoffesBok/Bilddatabaser_TNM025/dataset/";
	// ----> Directory for: GABRIEL <-----
	string mainDirectory = "C:/Users/Gabriel/Desktop/Bildatabaser/Bilddatabaser_TNM025/dataset/";
	
	vector<string> inputFolders = { "animal2", "beach2", "cat2", "colorful2",
								    "doll2", "elegant2", "flower2", "food2", "formal2", "garden2" };
	vector<string> testFolder = { "animal2" };

	// Initilize the database
	DB database = DB(mainDirectory, testFolder);

	system("pause");
	return 0;
}