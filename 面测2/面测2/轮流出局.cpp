#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int num;
	while (cin >> num)
	{
		vector<int> A(num + 1, 0);
		for (int i = 1; i < num + 1; i++)
		{
			cin >> A[i];
		}

		vector<int> B(num, NULL);
		for (int i = num; i > 0; i--)
		{
			int sum = 0;
			int cur = num - i + 1;
			int j = 0;
			while (sum != A[cur])
			{
				if (B[j] == NULL)
				{
					sum++;
				}
				if (j == num - 1)
				{
					j = 0;
					break;
				}
				j++;
			}
			B[j] = i;
		}

		for (int i = 0; i < num; i++)
		{
			cout << B[i] << endl;
		}
	}

	return 0;
}