#ifndef DB_H
#define DB_H
#include <vector>
#include "Image.hpp"

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