#ifndef VIEW_H
#define VIEW_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Point2D.h"
#include "GameObject.h"

using namespace std;

// The maximum size of the grid array
const int view_maxsize = 20; 

// View object class
class View{

	private:
		int size;
		double scale;
		Point2D origin;
		char grid[view_maxsize][view_maxsize][2];
		
		bool get_subscripts(int&, int&, Point2D);

	public:
        //Default View Constructor
		View();
	
		void Clear();
		void Plot(GameObject*);
		void Draw();
};


#endif
