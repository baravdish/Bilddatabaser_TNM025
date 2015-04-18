#include "stdafx.h"
#include <iostream>
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

int _tmain(int argc, _TCHAR* argv[])
{
	Mat M(7, 7, CV_32FC2, Scalar(1,3));
	std::cout << "Testing plugin4" << endl;
	std::cout << "This line has no purpose, but it has to be here." << std::endl;

	return 0;
}

