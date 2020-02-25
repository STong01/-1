#include <iostream>
#include <string>
using namespace std;

class Solution
{
public:
	long StrToInt(string str)
	{
		if (str.empty())
		{
			return 0;
		}

		//��¼�ַ����Ķ�Ӧ����
		int symbol = 1;
		if (str[0] == '-')
		{
			symbol = -1;
			str[0] = '0';
		}
		else if (str[0] == '+')
		{
			symbol = 1;
			str[0] = '0';
		}

		//�ַ���ת������sum��¼ת���������
		long sum = 0;
		for (int i = 0; i < str.size(); i++)
		{
			if (str[i] < '0' || str[i] > '9')
			{
				sum = 0;
				break;
			}

			sum = sum * 10 + str[i] - '0';
		}
		return symbol * sum;
	}
};

int main()
{
	Solution str;
	string A = "-2147483649";
	long B = str.StrToInt(A);
	cout << B << endl;

	system("pause");
	return 0;
}