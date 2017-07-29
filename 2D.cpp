#include <iostream>
#include <cmath>

struct dimensions
{
	 int x;
	 int y;
};

struct point
{
	double x;
	double y;
};

void draw(bool **grid, dimensions length, point *target, int arLength)
{
	for(int i = 0; i < arLength; ++ i)
	{
        double x1 = target[i].x;
        double x2;

        //loops back to the first vertex's x coordinate
        if(i == arLength - 1)
            x2 = target[0].x;
        else
            x2 = target[i+1].x;

        double y1 = target[i].y;
        double y2;

        //loops back to the first vertex's y coordinate
        if(i == arLength - 1)
            y2 = target[0].y;
        else
            y2 = target[i+1].y;

        //makes sure the line starts with the point with the smallest x value
        if(x1 > x2)
        {
            double temp = x1;
            x1 = x2;
            x2 = temp;

            temp = y1;
            y1 = y2;
            y2 = temp;
        }


        //checks for undefined slope
        int dx = x2 - x1;

        //draws undefined slope
        if(dx == 0)
        {
            int x = std::round(x1);
            int y = std::round(y1);

            if(y2 > y1)
                for(;y <= y2; ++y)
                {
                    grid[x][y] = true;
                }
            else
                for(;y >= y2; --y)
                {
                    grid[x][y] = true;
                }

        }
        else
        {
            //slope of the line
            double m = (y2 - y1)/dx;

            if((std::abs(m) <= 1.0) && (std::abs(m) >= 0.0))
            {
                double trueY = y1;
                int intY = std::round(y1);

                for(int x = x1; x <= x2; ++x)
                {
                    grid[x][intY] = true;
                    trueY = trueY + m;
                    intY = round(trueY);
                }
            }

            else
            {
                double trueX = x1;
                int intX = std::round(x1);

                if(m > 0.0)
                    for(int y = y1; y <= y2; ++y)
                    {
                        grid[intX][y] = true;
                        trueX = trueX + (1.0/m);
                        intX = std::round(trueX);
                    }

                else
                    for(int y = y1; y >= y2; --y)
                    {
                        grid[intX][y] = true;
                        trueX = trueX + (1.0/std::abs(m));
                        intX = std::round(trueX);
                    }
            }
        }
    }
}

void dispGraph(bool **grid, dimensions length)
{
	for(int y = length.y-1; y >= 0; --y)
	{
		for(int x = 0; x < length.x; ++x)
		{
            if(grid[x][y])
                std::cout << static_cast<char>(219) << static_cast<char>(219);
            else
                std::cout << "  ";
		}
		std::cout << '\n';
	}
}

int main()
{
	dimensions length{40, 40};

	bool **grid = new bool*[length.x];
	for(int i = 0; i < length.x; ++i)
	{
		grid[i] = new bool[length.y]{false};
	}

    point triangle[] {{5,5},{5,10},{10,10},{10,5}};
    draw(grid, length, triangle, 4);

	dispGraph(grid, length);

    for(int i = 0; i < length.y; ++i)
    {
        delete[] grid[i];
    }
	delete[] grid;

    return 0;
}
