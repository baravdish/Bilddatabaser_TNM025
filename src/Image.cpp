#include "Image.hpp"
 
// Constructor
Image::Image(Mat image_src) :
image_mat_(image_src)
{
	// Initiate RGB and HSV for this image
	setRGB(image_src);
	setHSV(image_src);

	// Set the histogram of this Image
	setHistogram(image_src);
}

Mat Image::getImageMat()
{
	return image_mat_;
}

// Calculate histogram for an image
void Image::setHistogram(Mat image_src)
{
	int histSize[3] = { BIN_SIZE, BIN_SIZE, BIN_SIZE };
	const float hranges[2] = { 0.0, 256.0 };
	const float* ranges[3] = { hranges, hranges, hranges };
	int channels[3] = { 0, 1, 2 };

	calcHist(&image_src, 1, channels, Mat(), histogram_, 3, histSize, ranges, true, false);

	histogram_ = histogram_ / image_src.total();

	vector<float> histogramVec(pow(BIN_SIZE, 3));
	int count = 0;

	// TODO: Check if the program is slow, if so; check this part
	for (int i = 0; i < BIN_SIZE; i++) {
		for (int j = 0; j < BIN_SIZE; j++) {
			for (int k = 0; k < BIN_SIZE; k++) {
				histogramVec[count] = histogram_.at<float>(i, j, k);
				count++;
			}
		}
	}

	Mat temp(histogramVec);
	histogram_ = temp.clone();
}

Mat Image::getHistogram()
{
	return histogram_;
}

void Image::setRGB(Mat image_src)
{
	// TODO: set the RGB values of this image
}

Mat Image::getRGB()
{
	return pixel_values_mat_RGB_;
}

void Image::setHSV(Mat image_src)
{
	// TODO: set the HSV values of this image
}

Mat Image::getHSV()
{
	return pixel_values_mat_IC2_;
}

void Image::show()
{
	if (!image_mat_.data)
	{
		std::cout << "Could not open or find the image" << std::endl;
	}
	cv::imshow("Image", image_mat_);
	cv::waitKey(10);
}

void Image::print()
{
	for (int i = 0; i < image_mat_.rows; i++)
	{
		for (int j = 0; j < image_mat_.cols; j++)
    	{
			std::cout << (int)image_mat_.at<Vec3b>(i, j)[0] << " "
				   	  << (int)image_mat_.at<Vec3b>(i, j)[1] << " "
					  << (int)image_mat_.at<Vec3b>(i, j)[2] << " | ";
    	}
		std::cout << std::endl;
	}	
}

void Image::print(int x, int y)
{
	std::cout << image_mat_.at<Vec3b>(x, y) << std::endl;
}

