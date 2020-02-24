#include <iostream>
#include <vector>
using namespace std;

//不要二
int main()
{
	//定义宽，高，计数放蛋糕位置
	int w, h, res = 0;
	cin >> w >> h;
	vector<vector<int>> a;
	a.resize(w);
	for (auto&e : a)
	{
		e.resize(h, 1);
	}

	//遍历所有的点，不满足的放置0；
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			if (a[i][j] == 1)
			{
				res++;
				if ((i+2)<w)
				{
					a[i + 2][j] = 0;
				}

				if ((j + 2) < h)
				{
					a[i][j + 2] = 0;
				}
			}
		}
	}
	cout << res << endl;
	system("pause");
	return 0;
}