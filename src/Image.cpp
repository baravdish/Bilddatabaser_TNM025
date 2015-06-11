#include "Image.hpp"
 
// Constructor
Image::Image(Mat image_src) :
image_mat_(image_src)
{
	//There are no grayscaled images in the current database
	//if (image_src.type() != 16)
		//cvtColor(image_src, img, CV_GRAY2BGR);

	// Convert to double
	//image_mat_.convertTo(image_mat_, CV_64FC3);

	// Initiate RGB and HSV for this image
	setRGB(image_src);
	setHSV(image_src);

	// Set the histogram of this Image
	setHistogram(image_src, BIN_SIZE);
}

Mat Image::getImageMat()
{
	return image_mat_;
}

// TODO: Calculate histogram of this image
void Image::setHistogram(Mat image_src, int bin_size)
{
	//vector<Mat> bgr_planes;
	//split(image_src, bgr_planes);
	//const float* histRange = { range };
	//Save to 1x64 histogram
	// ============> TODO: Do we need to normalize this? <=============
	//calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist_, 1, &hist_size, &histRange, true, false);
	//calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist_, 1, &hist_size, &histRange, true, false);
	//calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist_, 1, &hist_size, &histRange, true, false);
}

Mat Image::getHistogram()
{
	return histogram;
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

