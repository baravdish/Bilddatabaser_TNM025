#ifndef DB_H
#define DB_H
#include "Image.hpp"
#include <vector>

class DB
{
	private:
	 	vector<Image> Images;
	public:
	    DB();
	    void loadImages();
	    void saveImages();
};
 
#endif