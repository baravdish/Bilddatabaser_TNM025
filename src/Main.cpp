#include <iostream>
#include <opencv2/opencv.hpp>

#include "DB.hpp"
#include "Image.hpp"
#include "CorrelationMatrix.hpp"


int main()
{
	// Setup directory and folder paths, no recursive solution yet
	string mainDirectory = "C:/Users/StoffesBok/Bilddatabaser_TNM025/dataset/";
	vector<string> inputFolders = { "animal2", "beach2", "cat2", "colorful2",
								    "doll2", "elegant2", "flower2", "food2", "formal2", "garden2" };

	// Initilize the database
	DB database = DB(mainDirectory, inputFolders);

	Mat I = imread("C:/Users/StoffesBok/Bilddatabaser_TNM025/dataset/cat2/1.jpg", 1);
	Image img = Image(I);
	cout << "Type of image: " << I.type() << endl;
	img.print();
	
	system("pause");
	return 0;
}