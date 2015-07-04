#include"Interfaces04.h"

class RTree : public IRTree
{
	std::vector<IPoint *> temp;
public:
	RTree() {}
	~RTree() {}
	void hilbertSort(std::vector<IPoint *>& points);
	void bulkInsert(std::vector<IPoint *>& points);
	std::vector<IPoint *> findWithin(IPoint * top_left, IPoint * bottom_right);
	long long int find_quadrant(long long int xx, long long int yy, long long int w);
	bool is_power_2(long long int xy);
	unsigned long long int nxt_power_2(unsigned long long int xy);


};