#include <iostream>
#include <vector>
using namespace std;

int main2()
{
	long n;
	while (cin >> n)
	{
		vector<long> a;
		a.resize(n);
		for (long i = 0; i < n; i++)
		{
			cin >> a[i];
		}

		for (long i = 0; i < n; i++)
		{
			for (long j = 0; j < n; j++)
			{
				if ((a[i] & a[j]) == 0)
				{
					cout << "1" << " ";
					break;
				}
				if (j == n - 1)
				{
					cout << "-1" << " ";
				}
			}
		}
		cout << endl; 
	}

	return 0;
}