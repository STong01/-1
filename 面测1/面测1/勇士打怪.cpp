#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main1()
{
	int cur, sum;
	while (cin >> cur >> sum)
	{
		vector<int> tmp;
		tmp.resize(sum);
		for (int i = 0; i < sum; i++)
		{
			cin >> tmp[i];
		}

		int money = 0;
		int max_money = 0;

		sort(tmp.begin(), tmp.end());

		for (int i = 0; i < sum; i++)
		{
			if (cur >= tmp[i])
			{
				money = money + 1;
				max_money = max(max_money, money);
			}
			else
			{
				if ((cur + money) >= tmp[i])
				{
					money = money - (tmp[i] - cur);
					cur = cur + (tmp[i] - cur);
					money = money + 1;
					max_money = max(max_money, money);
				}
				else
				{
					break;
				}
			}
		}
		cout << max_money << endl;

	}
	return 0;
}