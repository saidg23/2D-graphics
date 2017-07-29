#include <iostream>
#include <cmath>

struct dimensions
{
	 const int x;
	 const int y;
};

struct line
{
	double x1;
	double y1;
	double x2;
	double y2;
};

void draw(bool **grid, dimensions length, line target)
{
	//checks for undefined slope
	int zerocheck = target.x2 - target.x1;
	
	//draws undefined slope
	if(zerocheck == 0)
	{
		int x = std::round(target.x1);
		int y = std::round(target.y1);
		
		if(target.y2 > target.y1)
			for(;y <= target.y2; ++y)
			{
				grid[x][y] = true;
			}
		else
			for(;y >= target.y2; --y)
			{
				grid[x][y] = true;
			}
			
		return;
	}
	
	//slope of the line
	double m = (target.y2 - target.y1)/zerocheck;
	
	if((std::abs(m) <= 1.0) && (std::abs(m) >= 0.0))
	{
		double trueY = target.x1;
		int intY = std::round(target.x1);
		
		for(int x = target.x1; x <= target.x2; ++x)
		{
			trueY = trueY + m;
			intY = round(trueY);
			grid[x][intY] = true;
		}
	}
	
	else
	{
		double trueX = target.x1;
		int intX = std::round(target.x1);
		
		if(m > 0)
			for(int y = target.y1; y <= target.y2; ++y)
			{
				trueX = trueX + (1.0/m);
				intX = std::round(trueX);
				grid[intX][y] = true;
			}
		
		else
			for(int y = target.y1; y >= target.y2; --y)
			{
				trueX = trueX + (1.0/std::abs(m));
				intX = std::round(trueX);
				grid[intX][y] = true;
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
				std::cout << "# ";
			else
				std::cout << "  ";
		}
		std::cout << '\n';
	}
}

int main()
{
	dimensions length{20, 20};
	
	bool **grid = new bool*[length.x];
	for(int i = 0; i < length.x; ++i)
	{
		grid[i] = new bool[length.y]{false};
	}
    
	line test{2.0, 4.0, 18.0, 4.0};
    draw(grid, length, test);
	
	line test2{3.0, 18.0, 3.0, 0.0};
	draw(grid, length, test2);
	
	dispGraph(grid, length);
    
	
	delete grid;
	
    return 0;
}
