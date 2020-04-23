#include <iostream>
#include <vector>
using namespace std;

int main3()
{
	int num;
	while (cin >> num)
	{
		vector<vector<int>> a(2001, vector<int>(2001, 0));
		for (int i = 0; i < num; i++)
		{
			int n, m;
			cin >> n >> m;
			a[n + 1000][m + 1000] = 1;
		}
		
		int count = 0;

		for (int i = 0; i < 2001; i++)
		{
			for (int j = 0; j < 2001; j++)
			{
				if (a[i][j] == 1)
				{
					int n = i;
					int m = j;
					int down = 0;
					int up = 0;
					int left = 0;
					int right = 0;
					while (i > 0)
					{
						i--;
						if (a[i][j] == 1)
						{
							up = 1;
							break;
						}
					}
					i = n;
					j = m;
					while (i < 2001)
					{
						i++;
						if (a[i][j] == 1)
						{
							down = 1;
							break;
						}
					}	
					i = n;
					j = m;
					while (j > 0)
					{
						j--;
						if (a[i][j] == 1)
						{
							left = 1;
							break;
						}
					}
					i = n;
					j = m;
					while (j < 2001)
					{
						j++;
						if (a[i][j] == 1)
						{
							right = 1;
							break;
						}
					}

					while (up == 1 && down == 1 && left == 1 && right == 1)
					{
						count++;
					}
				}
			}
		}
		cout << count << endl;
	}

	return 0;
}