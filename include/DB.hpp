#ifndef DB_H
#define DB_H
 
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