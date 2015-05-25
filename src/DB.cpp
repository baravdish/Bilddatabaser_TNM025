#include "DB.hpp"

// Constructor
DB::DB()
{

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
	return images;
}

Mat DB::getImage(int n)
{
	return images[n].getImage();
}

void DB::loadImages(string directory, vector<string> folders)
{
	DIR *directory_path;
	struct dirent *dirp;
	string temp = directory;

	for (size_t n = 0; n < folders.size(); n++)
	{
		vector<int> invalidImages;
		int nImages = 0;
		int invImages = 0;
		directory = temp + folders[n];
		directory_path = opendir(directory.c_str());

		cout << "Loading images in folder: " << folders[n] << "..." << endl;
		if (directory_path == NULL)
			cout << "Error opening directory. Not valid." << endl;
		else
		{
			string filepath;
			while ((dirp = readdir(directory_path)))
			{
				filepath = directory + "/" + dirp->d_name;
				cv::Mat image = imread(filepath, 1);
				Image img(image);
				if (!image.data)
				{
					//cout << "Could not read data" << endl;
					invalidImages.push_back(invImages);
				}
				else
				{
					images.push_back(img);
					nImages++;
				}
				invImages++;
			}
		} // END OF: image iterations

		// Connect each folder name with its size
		folderSizes[folders[n]] = nImages;

		printInvalidImageInformation(invalidImages, folders[n], images.size());

		closedir(directory_path);

	} // END OF: folder iteration

	cout << endl << endl << "Total number of loaded images in the database: " << images.size() << endl;

	cout << "==============================================" << endl;
	for (auto elem : folderSizes)
	{
		std::cout << elem.first << " has " << elem.second << " images " "\n";
	}
}

void DB::saveImages()
{

}