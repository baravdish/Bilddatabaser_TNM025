#include "Mosaic.hpp"

// Constructor
Mosaic::Mosaic(Mat image) :
image_source_(image)
{
	setImagesDB();
}

Mat Mosaic::getImageSource()
{
	return image_source_;
}

void Mosaic::setImagesDB()
{
	// Initiate rows, cols and Image.
	int rows = image_source_.rows;
	int cols = image_source_.cols;

	// Resize image so that it has mod(Y, size_of_patch) == 0
	if (rows % SIZE_OF_PATCH != 0)
	{
		resize(image_source_, image_source_, Size(cols, rows - (rows % SIZE_OF_PATCH)), 0, 0, INTER_AREA);
		rows = image_source_.rows; //update rows!
	}

	// Resize image so that it has mod(X, size_of_patch) == 0
	if (cols % SIZE_OF_PATCH != 0)
	{
		resize(image_source_, image_source_, Size(cols - (cols % SIZE_OF_PATCH), rows), 0, 0, INTER_AREA);
		cols = image_source_.cols; //update cols!
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
			patch = cv::Mat(image_source_, cv::Rect(x*SIZE_OF_PATCH, y*SIZE_OF_PATCH, SIZE_OF_PATCH, SIZE_OF_PATCH)); // (roiLeft, roiTop, roiWidth, roiHeight)
			Image temp_img = Image(patch);
			imagesDB.pushBack(temp_img);
		}
	}
	imagesDB.setHistogramMatrix(imagesDB.getImageDatabase());
}

// TODO: Maybe send in a vector with matched images instead of DB?
void Mosaic::reconstructImageFromDB()
{
	// Initiates sizes and numbers
	int size_of_patch = imagesDB.getImage(0).getImageMat().rows;
	int nPatchesX = image_source_.cols / size_of_patch;
	int nPatchesY = image_source_.rows / size_of_patch;

	// Make a copy of the Source Image matrix and initiate a patch
	Mat constructedImage(image_source_);
	Mat patch;

	// Replace the image with desired patches
	int count = 0;
	for (int y = 0; y < nPatchesY; y++)
	{
		for (int x = 0; x < nPatchesX; x++)
		{
			Mat similar_patch = similar_image_[count].getImageMat();
			similar_patch.copyTo(constructedImage(cv::Rect(x*size_of_patch, y*size_of_patch, size_of_patch, size_of_patch))); // (roiLeft, roiTop, roiWidth, roiHeight)
			count++;
		}
	}

	// Save the constructed image as result
	image_result_ = constructedImage;
}

//TODO: If not correct, check previous sizes (cols,rows)
void Mosaic::matchSimiliarImage(DB database)
{

	Mat queryHistoEig = imagesDB.getHistogramMatrix()*database.getEigenVectors().t();
	Mat histoEig = database.getHistoEig().t();

	int qRows = queryHistoEig.rows;
	int qCols = queryHistoEig.cols;

	int rows = histoEig.rows;
	int cols = histoEig.cols;
	int index = -1;
	for (int i = 0; i < qRows; i++)
	{		
		index = L2Norm(queryHistoEig(Rect(0, i, qCols, 1)), histoEig);
		pushSimilarImage(database.getImage(index));
	}
}

int Mosaic::L2Norm(Mat qHistoEigVec, Mat histoEig)
{
	Mat qHistoEigRep = repeat(qHistoEigVec, histoEig.rows, 1);
	Mat diff = qHistoEigRep - histoEig;
	Mat diffPow = diff.mul(diff);
	Mat L2Sum;
	reduce(diffPow, L2Sum, 1, CV_REDUCE_SUM,-1);
	double min, max;
	Point min_loc, max_loc;
	minMaxLoc(L2Sum, &min, &max, &min_loc, &max_loc);

	return min_loc.y;
}

void Mosaic::pushSimilarImage(Image similarImage)
{
	similar_image_.push_back(similarImage);
}

DB Mosaic::getImagesDB()
{
	return imagesDB;
}

// Saves the image to result folder
void Mosaic::saveImage(string image_name)
{
	imwrite("../result/" + image_name, image_result_);

	cout << endl << "======================================================" << endl;
	cout << "The reconstruced image is saved to: ../result/" + image_name << endl;
	cout << "======================================================" << endl << endl;
}