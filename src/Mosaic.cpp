#include "Mosaic.hpp"

// Constructor
Mosaic::Mosaic(Mat image) :
image_source(image)
{
	setImagesDB();
}

Mat Mosaic::getImageSource()
{
	return image_source;
}

void Mosaic::setImagesDB()
{
	// Initiate rows, cols and Image.
	int rows = image_source.rows;
	int cols = image_source.cols;

	// Resize image so that it has mod(Y, size_of_patch) == 0
	if (rows % SIZE_OF_PATCH != 0)
	{
		resize(image_source, image_source, Size(cols, rows - (rows % SIZE_OF_PATCH)), 0, 0, INTER_AREA);
		rows = image_source.rows; //update rows!
	}

	// Resize image so that it has mod(X, size_of_patch) == 0
	if (cols % SIZE_OF_PATCH != 0)
	{
		resize(image_source, image_source, Size(cols - (cols % SIZE_OF_PATCH), rows), 0, 0, INTER_AREA);
		cols = image_source.cols; //update cols!
	}

	// Get the number of patches in X and Y.
	int nPatchesX = cols / SIZE_OF_PATCH;
	int nPatchesY = rows / SIZE_OF_PATCH;
	Mat patch;

	// Splices the image into patches and puts them in a DB
	for (int y = 0; y < nPatchesY; y++)
	{
		for (int x = 0; x < nPatchesX; x++)
		{
			patch = cv::Mat(image_source, cv::Rect(x*SIZE_OF_PATCH, y*SIZE_OF_PATCH, SIZE_OF_PATCH, SIZE_OF_PATCH)); // (roiLeft, roiTop, roiWidth, roiHeight)
			Image temp_img = Image(patch);
			imagesDB.pushBack(temp_img);
		}
	}
}

// TODO: Maybe send in a vector with matched images instead of DB?
void Mosaic::reconstructImageFromDB(DB matched_images_DB)
{
	// Initiates sizes and numbers
	int size_of_patch = imagesDB.getImage(0).getImageMat().rows;
	int nPatchesX = image_source.cols / size_of_patch;
	int nPatchesY = image_source.rows / size_of_patch;

	// Make a copy of the Source Image matrix and initiate a patch
	Mat constructedImage(image_source);
	Mat patch;

	// Replace the image with desired patches
	for (int y = 0; y < nPatchesY; y++)
	{
		for (int x = 0; x < nPatchesX; x++)
		{
			matched_images_DB.getImageMat(x + y*nPatchesX).copyTo(constructedImage(cv::Rect(x*size_of_patch, y*size_of_patch, size_of_patch, size_of_patch))); // (roiLeft, roiTop, roiWidth, roiHeight)
		}
	}

	// Save the constructed image as result
	image_result = constructedImage;
}

Mat Mosaic::queryImageHistogram(Mat histogram, int index)
{
	// TODO: Get histogram for query image, maybe call on function from Image class...
	return histogram;
}

Mat Mosaic::similiarImagePCA(Mat histogram, Mat queryImage)
{
	// TODO: Get the similar image
	return histogram;
}

void Mosaic::pushSimilarImage(Mat similarImage)
{
	// TODO: Push back the similar image to the vector
}

DB Mosaic::getImagesDB()
{
	return imagesDB;
}

// Saves the image to result folder
void Mosaic::saveImage(string image_name)
{
	imwrite("../result/" + image_name, image_result);

	cout << endl << "======================================================" << endl;
	cout << "The reconstruced image is saved to: ../result/" + image_name << endl;
	cout << "======================================================" << endl << endl;
}