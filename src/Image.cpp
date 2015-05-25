#include "Image.hpp"
 
// Constructor
Image::Image(Mat image_src) :
img(image_src)
{
	//There are no grayscaled images in current database
	//if (image_src.type() != 16)
		//cvtColor(image_src, img, CV_GRAY2BGR);

	// Convert to double
	img.convertTo(img, CV_64FC3);
}

void Image::generateCorrelationMatrixRGB(Mat image_src)
{
	// Reshape matrix to 3xN
	// TODO: Test this!! should be 3xN * Nx3 =====> check if pixel_values_mat_RGB is 3xN!!!
	pixel_values_mat_RGB = image_src.reshape(1, 3).t();
	correlation_matrix_RGB = pixel_values_mat_RGB.t()*pixel_values_mat_RGB;
}

// Return correlation matrix for this image
Mat Image::getCorrelationMatrixRGB()
{
	return correlation_matrix_RGB;
}

// Return this image matrix
Mat Image::getImage()
{
	return img;
}

// Return eigenvalues
Mat Image::getEigenvalues()
{
	return eigenvalues;
}

// Return eigenvectors
Mat Image::getEigenvectors()
{
	return eigenvectors;
}

void Image::calculateEigvalAndEigvec()
{
	eigen(correlation_matrix_RGB, eigenvalues, eigenvectors);
}

// Calculate histogram
void Image::generateHistograms(Mat image_src, int hist_size, float range[])
{
	vector<Mat> bgr_planes;
	split(image_src, bgr_planes);
	const float* histRange = { range };

	// ============> TODO: Do we need to normalize this? <=============
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &hist_size, &histRange, true, false);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &hist_size, &histRange, true, false);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &hist_size, &histRange, true, false);
}

// Prints the pixel values of this image and imshow the image
void Image::print()
{
	// Show the image
	if (!img.data)        // Check for invalid input
	{
		std::cout << "Could not open or find the image" << std::endl;
	}
	cv::imshow("Image", img);
	cv::waitKey(10);

	// Print the matrix
	for(int i=0; i < img.rows; i++)
	{
		for(int j=0; j < img.cols; j++)
    	{
			std::cout << (int)img.at<Vec3b>(i, j)[0] << " "
				      << (int)img.at<Vec3b>(i, j)[1] << " "
					  << (int)img.at<Vec3b>(i, j)[2] << " | ";
    	}
		std::cout << std::endl;
	}	
}

void Image::print(int x, int y)
{
	std::cout << img.at<Vec3b>(x, y) << std::endl;
}

