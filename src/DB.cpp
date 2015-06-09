#include "DB.hpp"

// Constructor
DB::DB()
{
	image.data = NULL;
}

// Create DB from an Image
DB::DB(Mat img_source, int size_of_patch)
{
	// Initiate rows, cols and Image.
	int rows = img_source.rows;
	int cols = img_source.cols;
	image = img_source;

	// Resize image so that it has mod(Y, size_of_patch) == 0
	if (rows % size_of_patch != 0)
	{
		resize(img_source, image, Size(cols, rows - (rows % size_of_patch)), 0, 0, INTER_AREA);
		rows = image.rows; //update rows!
	}

	// Resize image so that it has mod(X, size_of_patch) == 0
	if (cols % size_of_patch != 0)
	{
		resize(img_source, image, Size(cols - (cols % size_of_patch), rows), 0, 0, INTER_AREA);
		cols = image.cols; //update cols!
	}

	// Get the number of patches in X and Y.
	int nPatchesX = cols / size_of_patch;
	int nPatchesY = rows / size_of_patch; 
	Mat patch;
	
	// Splices the image into patches and puts them in a DB
	for (int y = 0; y < nPatchesY; y++)
	{
		for (int x = 0; x < nPatchesX; x++)
		{
			patch = cv::Mat(img_source, cv::Rect(x*size_of_patch, y*size_of_patch, size_of_patch, size_of_patch)); // (roiLeft, roiTop, roiWidth, roiHeight)
			Image temp_img = Image(patch);
			images_.push_back(temp_img);
		}
	}
}

// TODO: Maybe send in a new DB with matched images?
void DB::reconstructImageFromDB(DB matched_images_DB, string image_name)
{
	// Check if the DB has an Image source
	if (image.data == NULL)
	{
		std::cout << "ERROR: This DB does not have any source-Image, use 'DB(Mat img_source, int size_of_patch)' constructor instead." << std::endl;
	}

	else
	{
		// Initiates sizes and numbers
		int size_of_patch = getImage(0).getImageMat().rows;
		int nPatchesX = image.cols / size_of_patch;
		int nPatchesY = image.rows / size_of_patch;

		// Make a copy of the Source Image matrix and initiate a patch
		Mat constructedImage(image);
		Mat patch;

		// Replace the image with desired patches
		for (int y = 0; y < nPatchesY; y++)
		{
			for (int x = 0; x < nPatchesX; x++)
			{
				matched_images_DB.getImageMat(x + y*nPatchesX).copyTo(constructedImage(cv::Rect(x*size_of_patch, y*size_of_patch, size_of_patch, size_of_patch))); // (roiLeft, roiTop, roiWidth, roiHeight)
			}
		}

		// Save the result to the computer
		saveImage(constructedImage, image_name);
		waitKey(10);
	}
}

void DB::printInvalidImageInformation(vector<int> invalidImages, string folder, int nImages)
{
	for (auto p : invalidImages)
	{
		if (p == 0)
			cout << "Invalid image at #" << p << " <-- This is an invisible parent file" << endl;
		else if (p == 1)
			cout << "Invalid image at #" << p << " <---This is also an invisible parent file" << endl;
		else if (p > 1000)
			cout << "Invalid image at #" << p << " <---- This is an invisible EndOFFile-file" << endl;
		else
			cout << "Invalid image at #" << p << " <----- DON'T KNOW WHAT THIS IS, PLEASE CHECK THIS" << endl;
	}

	cout << "----------------------------------------" << endl << endl << endl;
}

vector<Image> DB::getImageDatabase()
{
	return images_;
}

Image DB::getImage(int n)
{
	return images_[n];
}

Mat DB::getImageMat(int n)
{
	return images_[n].getImageMat();
}

void DB::loadImages(string directory, vector<string> folders)
{
	
	struct dirent *dirp;
	string temp = directory;

	for (size_t n = 0; n < folders.size(); n++)
	{
		vector<int> invalidImages;
		int nImages = 0;
		int invImages = 0;
		directory = temp + folders[n];
		directory_path_ = opendir(directory.c_str());
		
		cout << "Loading images in folder: " << folders[n] << "..." << endl;
		if (directory_path_ == NULL)
			cout << "Error opening directory. Not valid." << endl;
		else
		{
			string filepath;
			while ((dirp = readdir(directory_path_)))
			{
				filepath = directory + "/" + dirp->d_name;
				
				cv::Mat image_temp = imread(filepath, 1);
				if (!image_temp.data)
				{
					//cout << "Could not read data in " << filepath << endl;
					invalidImages.push_back(invImages);
				}
				else
				{
					Image img(image_temp);
					//img.calculateCorrelationMatrixRGB(img.getImageMat());
					//img.calculateEigvalAndEigvec();
					images_.push_back(img);
					nImages++;
				}

				invImages++;
			}
		} // END OF: image iterations

		// Connect each folder name with its size
		folderSizes_[folders[n]] = nImages;

		//printInvalidImageInformation(invalidImages, folders[n], images.size());

		closedir(directory_path_);

	} // END OF: folder iteration
	cout << endl << endl << "Total number of loaded images in the database: " << images_.size() << endl;
	
	cout << "==============================================" << endl;
	for (auto elem : folderSizes_)
	{
		std::cout << elem.first << " has " << elem.second << " images " "\n";
	}
}

// Saves the image to result folder
void DB::saveImage(Mat image, string image_name)
{
	imwrite("../result/" + image_name, image);

	cout << endl << "======================================================" << endl;
	cout << "The reconstruced image is saved to: ../result/" + image_name << endl;
	cout << "======================================================" << endl << endl;
}