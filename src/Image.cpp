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
}

Mat Image::getImageMat()
{
	return image_mat_;
}

void Image::calculateCorrelationMatrixRGB(Mat image_src)
{
	// Reshape matrix to 3xN
	// TODO: Test this!! should be 3xN * Nx3 =====> check if pixel_values_mat_RGB is 3xN!!!
	pixel_values_mat_RGB_ = image_src.reshape(1, 3).t();
	correlation_matrix_RGB_ = pixel_values_mat_RGB_.t()*pixel_values_mat_RGB_;
}

// Return correlation matrix for this image
Mat Image::getCorrelationMatrixRGB()
{
	return correlation_matrix_RGB_;
}

// Return eigenvalues
Mat Image::getEigenvalues()
{
	return eigenvalues_;
}

// Return eigenvectors
Mat Image::getEigenvectors()
{
	return eigenvectors_;
}

void Image::calculateEigvalAndEigvec()
{
	if (!correlation_matrix_RGB_.data)
		cout << "Error calculateEigvalAndEigvec()! Correlation matrix is undefined";
	else
		eigen(correlation_matrix_RGB_, eigenvalues_, eigenvectors_);
}

// Calculate histogram
void Image::calculateHistograms(Mat image_src, int hist_size, float range[])
{
	vector<Mat> bgr_planes;
	split(image_src, bgr_planes);
	const float* histRange = { range };

	// ============> TODO: Do we need to normalize this? <=============
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist_, 1, &hist_size, &histRange, true, false);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist_, 1, &hist_size, &histRange, true, false);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist_, 1, &hist_size, &histRange, true, false);
}

// Prints the pixel values of this image and imshow the image
void Image::print()
{
	// Show the image
	if (!image_mat_.data)        // Check for invalid input
	{
		std::cout << "Could not open or find the image" << std::endl;
	}
	cv::imshow("Image", image_mat_);
	cv::waitKey(10);

	// Print the matrix
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

