#include "View.h"

View::View()
{
    size = 11;
    scale = 2;
    origin = Point2D(0, 0);
}
bool View::get_subscripts(int& out_x, int& out_y, Point2D location)
{
    out_x = (int)((location.x - origin.x) / scale);
	out_y = (int)((location.y - origin.y) / scale);
	
	if (out_x <= 20 && out_y <= 20 && out_x >= 0 && out_y >= 0)
    {
        return true;
    }
	else
    {
		cout << "An object is outside the display." << endl;
		return false;
	}
}

void View::Clear()
{
    for (int i = 0; i < view_maxsize; i++)
    {
		for (int j = 0; j < view_maxsize; j++)
        {
			grid[i][j][0] = '.';
			grid[i][j][1] = ' ';
		}
	}
}
void View::Plot(GameObject* ptr)
{
    int x, y;
	bool toPlot = get_subscripts(x, y, ptr->GetLocation());
	if (toPlot){
		if(grid[x][y][0] != '.'){
			grid[x][y][0] = '*';
			grid[x][y][1] = ' ';
		}	
		else {
			ptr->DrawSelf(grid[x][y]);
			cout << setw(2);
		}	
	}	
}
void View::Draw()
{
    for (int j = size - 1; j >= -1; j--)
    {
        for (int i = -1; i <= size - 1; i++)
        {
            //grid axis
            if (i == -1 && j%2 == 0)
            {
                cout << j*2;
                if (j/5 == 0)
                {
                    cout << " ";
                }
            }
            else if (i == -1 && j%2 !=0)
            {
                cout << "  ";
            }
            else if (j == -1 && i%2 == 0)
            {
                cout << i*2;
                if (i/5 == 0)
                {
                    cout << "  ";
                }
                cout << " ";
            }
            //draw objects
            if (i >= 0 && j >= 0)
            {
                cout << grid[i][j][0] << grid[i][j][1];
            }
        }
        cout << endl;
    }
}