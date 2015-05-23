#ifndef CORRELATIONMATRIX_H
#define CORRELATIONMATRIX_H
 
class CorrelationaMatrix
{
	private:
	 	vector<double>[] eigenvectors;
	 	double eigenvalues[];
	 	Mat histogram_RGB;
	 	Mat histogram_IC2;
	public:
	    CorrelationaMatrix();
	    void generateHistogram();
	    void print();
};
 
#endif