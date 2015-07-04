#include"Interfaces04.h"

class Point :public IPoint
{
	int x;
	int y;
public:
	Point() {}
	~Point() {}
	int getX();
	int getY();
	void setX(int value);
	void setY(int value);
};
