#ifndef CORRELATIONMATRIX_H
#define CORRELATIONMATRIX_H
#include <vector>
#include <iostream>
#include <iterator>
#include <opencv2\opencv.hpp>

// Visual studio complains about collision with std and cv.
// A simple solution...
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::map;
using namespace cv;

class CorrelationMatrix
{
	private:
	 	vector<double> eigenvectors;
	 	vector<double> eigenvalues;
	 	Mat histogram_RGB;
	 	Mat histogram_IC2;
	public:
	    CorrelationMatrix();
	    void generateHistogram();
	    void print();
};
 
#endif