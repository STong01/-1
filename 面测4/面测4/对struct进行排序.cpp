#include <iostream>
#include <vector>
#include <algorithm>

struct Point
{
	int x;
	int y;
};

int main()
{
	int x = 0;
	int y = 0;
	std::vector<Point> vec;
	while (std::cin >> x >> y)
	{
		Point p;
		p.x = x;
		p.y = y;
		vec.push_back(p);
	}

	std::sort(vec.begin(), vec.end());

	for (auto iter = vec.begin(); iter != vec.end(); ++iter)
	{
		std::cout << iter->x << " " << iter->y << std::endl;
	}

	return 0;
}