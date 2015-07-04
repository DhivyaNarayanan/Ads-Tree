#include"RTree.h"
#include<iostream>
using namespace std;

void RTree::hilbertSort(std::vector<IPoint *>& points)
{
	
	std::vector<long long int> dist_pt;
	long long int max_x = 0, max_y = 0;
	long long int max_xy;
	long long int w;

	for (long long int i = 0; i < points.size(); i++)
	{
		if (points[i]->getX() > max_x)
			max_x = points[i]->getX();

		if (points[i]->getY() > max_y)
			max_y = points[i]->getY();

	}

	max_xy = max_x;
	if (max_y > max_x)
	max_xy = max_y;

	if (is_power_2(max_xy) != true)
	{
		max_xy = nxt_power_2(max_xy);
	}
	

	for (long long int i = 0; i < points.size(); i++)
	{
		 w = max_xy/2;
		long long int xx = points[i]->getX();
		long long int yy = points[i]->getY();
		long long int x_new, y_new;
		x_new = xx;
		y_new = yy;
		long long int quad;
		long long int d = 0;
	
		while (w != 0)
		{
			quad = find_quadrant(x_new, y_new, w);
			d += quad*w*w;
			if (quad == 0)
			{
				int tmp = x_new;
				x_new = y_new;
				y_new = tmp;
			}
			else if (quad == 1)
			{
				y_new = y_new - w;
			}
			else if (quad == 2)
			{
				x_new = x_new - w;
				y_new = y_new - w;
			}
			else if (quad == 3)
			{
				int tmp1 = x_new;
				int tmp2 = y_new;
				x_new = w - tmp2 - 1;
				y_new = (w * 2) - tmp1 - 1;
			
			}
			w = w / 2;
		}
		dist_pt.push_back(d);

	}
	
	for (long long int j = 0; j < dist_pt.size(); ++j)
	{
		long long int k = dist_pt[j];
		IPoint* kp = points[j];
		long long int i = j - 1;
		while (i >= 0 && dist_pt[i] > k)
		{
			dist_pt[i + 1] = dist_pt[i];
			points[i + 1] = points[i];
			--i;
		}
		dist_pt[i + 1] = k;
		points[i + 1] = kp;
	}

	for (int i = 0; i < 10; i++)
	{
		std::cout << dist_pt[i] << "\t";
	}
	std::cout << "\n\n";
	for (int i = 0; i < 10; i++)
	{
		std::cout << "(" << points[i]->getX() <<"," << points[i]->getY() <<")"<< "\t";
	}

		
}

long long int RTree::find_quadrant( long long int xx, long long int yy, long long int w)
{
	
	long long int quad=0;
	if (xx < w && yy < w)
		quad = 0;
	else if (xx < w && yy >= w)
		quad = 1;
	else if (xx >= w && yy >= w)
		quad = 2;
	else if (xx >= w && yy < w)
		quad = 3;

	return quad;
	
}

bool RTree::is_power_2(long long int xy)
{
	if (xy > 0)
		return !(xy &(xy - 1));
	else
		return 0;
}

unsigned long long int RTree::nxt_power_2(unsigned long long int xy)
{
	xy--;
	xy |= xy >> 1;
	xy |= xy >> 2;
	xy |= xy >> 4;
	xy |= xy >> 8;
	xy |= xy >> 16;
	xy++;
	return xy;
}


void RTree::bulkInsert(std::vector<IPoint *>& points)
{
	for (int i = 0; i < points.size(); i++)
	{
		temp.push_back(points[i]);
	}

}
std::vector<IPoint *> RTree::findWithin(IPoint * top_left, IPoint * bottom_right)
{
	std::vector<IPoint*> pts_within;
	int tx;
	int ty;
	int tlx = top_left->getX();
	int tly = top_left->getY();
	int brx = bottom_right->getX();
	int bry = bottom_right->getY();

	for (int i = 0; i < temp.size(); i++)
	{
		tx = temp[i]->getX();
		ty = temp[i]->getY();
		if (tx <= brx && tx >= tlx)
		{
			if (ty <= bry && ty >= tly)
			{
				pts_within.push_back(temp[i]);
			}
			
		}
	}

	return pts_within;

}