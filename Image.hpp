#ifndef IMAGE_H
#define IMAGE_H
 
class Image
{
	private:
	 	int image_size[2];
	 	Mat image_matrix;
	 	vector<CorrelationMatrix> correlation_mat_RGB;
	 	vector<CorrelationMatrix> correlation_mat_IC2;
	public:
	    Image();
	    void print(); // cout the pixel values of this image and imshow the image
	    int getSize();
};
 
#endif