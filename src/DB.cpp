#include "DB.hpp"

// Constructor
DB::DB() 
{
	nImages = 0;
}

void DB::printInvalidImageInformation(vector<int> invalidImages, string folder, int nr_of_Images)
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
		int nr_of_Images = 0;
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
					pushBack(img);
					nr_of_Images++;
				}

				invImages++;
			}
		} // END OF: image iterations

		// Connect each folder name with its size
		folderSizes_[folders[n]] = nr_of_Images;

		//printInvalidImageInformation(invalidImages, folders[n], images.size());
		closedir(directory_path_);

	} // END OF: folder iteration
	cout << endl << endl << "Total number of loaded images in the database: " << images_.size() << endl;
	
	cout << "==============================================" << endl;
	for (auto elem : folderSizes_)
	{
		std::cout << elem.first << " has " << elem.second << " images " "\n";
	}

	// TODO: Activate when working.
	// initializeMatrices();
}

// TODO: Check that this works correctly in both LoadImages and Zlatan!
int DB::getNImages()
{
	return nImages;
}

void DB::initializeMatrices()
{
	// Initiate the H (nImages x nBin^3)
	setHistogramMatrix(images_);

	// Initiate the C (nBin^3 x nBin^3)
	setCorrelationMatrix(histogramMatrix);

	// Initiate the PCA (nImages x nEigenVectors)
	setEigenVectors(correlationMatrix);

	// Initiate the HE (nImages x nBin^3) * (nBin^3 x nEigvectors)
	setHistoEig(histogramMatrix, eigenVectors);
}

void DB::setHistogramMatrix(vector<Image> imageMatrices)
{
	// H - A matrix of size (nImages x nBin^3)
	Mat H(nImages, N_BIN^3, CV_32F, Scalar(0.0));

	// TODO: Copy images histogram to H with copyTo

	histogramMatrix = H;
}

Mat DB::getHistogramMatrix()
{
	return histogramMatrix;
}

void DB::setCorrelationMatrix(Mat H)
{
	// H - A matrix of size (nImages x nBin^3)
	correlationMatrix = H.t() * H;
}

Mat DB::getCorrelationMatrix()
{
	return correlationMatrix;
}

void DB::setEigenVectors(Mat C)
{
	// TODO: A matrix of size (nBin^3 x nImages). NB! nImages can be changed (e.g 20) depending on how many of the largest eigenvalues we want for PCA.
}

Mat DB::getEigenVectors()
{
	return eigenVectors;
}

void DB::setHistoEig(Mat H, Mat E)
{
	// H - A matrix of size (nImages x nBin^3)
	// E - A matrix of size (nBin^3 x nEigvectors)
	histoEig = H * E;
}

Mat DB::getHistoEig()
{
	return histoEig;
}

void DB::pushBack(Image I)
{
	images_.push_back(I);
	nImages++;
}