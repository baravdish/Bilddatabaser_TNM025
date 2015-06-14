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
	string mainDirectory = "C:/Users/StoffesBok/Bilddatabaser_TNM025/dataset/";
	cv::Mat image_temp = imread("C:/Users/StoffesBok/Bilddatabaser_TNM025/dataset/zlatan/zlatan_blue_background_1920x1080.jpg", 1);

	// ----> Directory for: GABRIEL <-----
	//string mainDirectory = "C:/Users/Gabriel/Desktop/Bildatabaser/Bilddatabaser_TNM025/dataset/";
	//Mat image_temp = imread("C:/Users/Gabriel/Desktop/Bildatabaser/Bilddatabaser_TNM025/dataset/zlatan/" + image_name, 1);

	if (!image_temp.data){
		cout << "Zlatan is too big!" << endl; return -1;
	}
	
	vector<string> inputFolders = { "andy_warhol4", "claude_monet4", "animal4", "beach4", "cat4", "colorful4",
								    "doll4", "elegant4", "flower4", "food4", "formal4", "garden4" };
	vector<string> animalFolder = { "animal2" };

	// Initilize the database
	DB database = DB();
	database.loadImages(mainDirectory, inputFolders);
	
	// Create a database of patches from a query image
	Mosaic zlatan = Mosaic(image_temp);

	// Match similar images in the mosaic with the database 
	// with PCA/KLT and L2-norm
	zlatan.matchSimiliarImage(database);

	// Reconstruct the matched images
	zlatan.reconstructImageFromDB();

	// Write and save the reconstructed image
	zlatan.saveImage(image_name);
	
	system("pause");
	return 0;
}