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

void DB::loadImages(string directory, vector<string> inputFolders)
{

	struct dirent *dirp;
	string temp = directory;
	for (size_t n = 0; n < inputFolders.size(); n++)
	{
		// Track invalid images
		vector<int> invalidImages;
		int invImages = 0;

		int nr_of_Images = 0;
		directory = temp + inputFolders[n];

		// Open directory path
		directory_path_ = opendir(directory.c_str());
		
		cout << "Loading images in folder: " << inputFolders[n] << "..." << endl;
		if (directory_path_ == NULL)
			cout << "Error opening directory. Not valid." << endl;
		else
		{
			string filepath;
			
			// Start read a folder
			while ((dirp = readdir(directory_path_)))
			{
				filepath = directory + "/" + dirp->d_name;
				cv::Mat image_temp = imread(filepath, 1);
				if (!image_temp.data)
				{
					//cout << "Could not read data in " << filepath << endl;
					// Track invalid images
					invalidImages.push_back(invImages);
				}
				else
				{
					Image img(image_temp);
					pushBack(img);
					nr_of_Images++;
				}
				invImages++;
			}
		} // END OF: image iterations

		// Connect each folder name with its size
		folderSizes_[inputFolders[n]] = nr_of_Images;

		//printInvalidImageInformation(invalidImages, folders[n], images.size());
		closedir(directory_path_);

	} // END OF: folder iteration
	cout << endl << endl << "Total number of loaded images in the database: " << images_.size() << endl;
	
	cout << "==============================================" << endl;
	for (auto elem : folderSizes_)
	{
		std::cout << elem.first << " has " << elem.second << " images " "\n";
	}

	initializeMatrices();
}

int DB::getNImages()
{
	return nImages;
}

void DB::initializeMatrices()
{
	// Initiate the H (nImages x nBin^3)
	setHistogramMatrix(images_);
	
	// Initiate the C (nBin^3 x nBin^3)
	setCorrelationMatrix(histogramMatrix_);

	// Initiate the PCA (nImages x nEigenVectors)
	setEigenVectors(histogramMatrix_);

	// Initiate the HE (nImages x nBin^3) * (nBin^3 x nEigvectors)
	setHistoEig(histogramMatrix_, eigenVectors_);

	// Should take parameters: nClusters, nAttempts, nRuns
	setKMeans(nClusters_, nAttempts_);
}

void DB::setKMeans(int nClusters, int nAttempts)
{
	double t = (double)getTickCount();
	// Run K-means
	cv::kmeans(histoEig_.t(),
		nClusters,
		labels_,
		TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 100, 1.0),
		nAttempts,
		KMEANS_RANDOM_CENTERS,
		centers_);

	// Create a map of label indexes
	// Create cluster
	clusters_.resize(nClusters);
	labelIndexes_.resize(nClusters);

	Mat H = histoEig_.t();
	for (int i = 0; i < labels_.size(); i++){
		clusters_[labels_[i]].push_back((H(Rect(0, i, N_EIGENVECTORS, 1))));
		labelIndexes_[labels_[i]].push_back(i);
	}

	for (int i = 0; i < clusters_.size(); i++)
		cout << "Cluster " << i << " has " << clusters_[i].rows << " images" << endl;
	
	double b = (double)getTickCount();
	t = (b - t) / getTickFrequency();

	cout << endl << "K-MEANS CLUSTERING IS DONE" << endl;
	cout << endl << "TIME FOR K-MEANS: " << t << endl;
	cout << "--------------------------------------------";
}

void DB::setHistogramMatrix(vector<Image> imageMatrices)
{
	// H - A matrix of size (nImages x nBin^3)
	Mat H(pow(BIN_SIZE, 3), nImages, CV_32F, Scalar(0.0));

	for (int i = 0; i < nImages; i++)
	{
		Mat h(imageMatrices[i].getHistogram());
		h.copyTo(H(Rect(i, 0, 1, pow(BIN_SIZE, 3))));
	}

	//H = H.t();
	//histogramMatrix_ = H.clone();
	histogramMatrix_ = H.t();
	//cout << endl << "--------------------------------------------";
	//cout << endl << "HISTOGRAM MATRIX H IS DONE" << endl;
	//cout << "--------------------------------------------";

}

Mat DB::getHistogramMatrix()
{
	return histogramMatrix_;
}

void DB::setCorrelationMatrix(Mat H)
{
	// H - A matrix of size (nImages x nBin^3)
	correlationMatrix_ = H.t() * H;
} 

Mat DB::getCorrelationMatrix()
{
	return correlationMatrix_;
}

// TODO: Check if normalizing is done correctly
void DB::setEigenVectors(Mat H)
{
	// Perform PCA
	PCA pca(H, Mat(), CV_PCA_DATA_AS_ROW, N_EIGENVECTORS);

	// E - A matrix of size (nBin^3 x nImages)
	// Get the best eigenvectors and save them
	eigenVectors_ = pca.eigenvectors.clone();

	//cout << endl << "--------------------------------------------";
	//cout << endl << "PCA IS DONE" << endl;
	//cout << "--------------------------------------------";
}

Mat DB::getEigenVectors()
{
	return eigenVectors_;
}

void DB::setHistoEig(Mat H, Mat E)
{
	// H - A matrix of size (nImages x nBin^3)
	// E - A matrix of size (nBin^3 x nEigvectors)
	histoEig_ = E*H.t();
}

Mat DB::getHistoEig()
{
	return histoEig_;
}

void DB::pushBack(Image I)
{
	images_.push_back(I);
	nImages++;
}