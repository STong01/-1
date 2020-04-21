#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int num;
	while (cin >> num)
	{
		vector<int> tmp;
		tmp.resize(num);
		for (int i = 0; i < num; i++)
		{
			cin >> tmp[i];
		}

		vector<vector<int>> mp = (num, vector<int>(num, 0));

		for (int i = 0; i <= num; i++)
		{
			int n, m;
			cin >> n >> m;
			mp[n][m] = 1;
			mp[m][n] = 1;
		}

		int len = 0;

		for (int i = 0; i < num; i++)
		{
			for (int j = 0; i < num; i++)
			{
				if (i != j)
				{
					if (tmp[i] == tmp[j])
					{
						int sos = i;
						for (int p = 0; p < num; p++)
						{
							if (p == sos)
							{
								for (int k = 0; k < num; k++)
								{
									if (mp[sos][k] == 1)
									{
										sos = k;
										len += 1;
										if (k == j)
										{
											cout << len << endl;
										}
										break;
									}
								}
							}
						}
					}
				}
			}
		}

	}
	return 0;
}