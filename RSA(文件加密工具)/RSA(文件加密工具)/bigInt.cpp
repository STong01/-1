#include "bigInt.h"

BigInt::BigInt(const std::string& num)
	:_number(num)
{}

//�������������
BigInt BigInt::operator+(BigInt& bi)
{
	std::string ret = add(_number, bi._number);
	return BigInt(ret);
}

BigInt BigInt::operator- (BigInt& bi)
{
	std::string ret = sub(_number, bi._number);
	return BigInt(ret);
}

BigInt BigInt::operator*(BigInt& bi)
{
	std::string ret = mul(_number, bi._number);
	return BigInt(ret);
}

BigInt BigInt::operator/ (BigInt& bi)
{
	std::pair<std::string, std::string> ret = dev(_number, bi._number);
	return BigInt(ret.first);
}

BigInt BigInt::operator% (BigInt& bi)
{
	std::pair<std::string, std::string> ret = dev(_number, bi._number);
	return BigInt(ret.second);
}

//ģ��ӷ�������
//�������
std::string BigInt::add(std::string num1, std::string num2)
{
	//λ������
	int len1 = num1.size();
	int len2 = num2.size();
	int diffNum = abs(len1 - len2);
	int longSize = len1 > len2 ? len1 : len2;
	//��λ����
	if (len1 < len2)
	{
		num1.insert(0, diffNum, '0');
	}
	else if (len2 < len1)
	{
		num2.insert(0, diffNum, '0');
	}
	std::string ret;
	ret.resize(longSize);
	//��λ���
	int step = 0;
	for (int i = longSize - 1; i >= 0; i--)
	{
		ret[i] = (num1[i] - '0') + (num2[i] - '0') + step;
		ret[i] += '0';
		//����
		if (ret[i] > '9')
		{
			ret[i] = ret[i] - 10;
			step = 1;
		}
		else
		{
			step = 0;
		}
	}
	if (step == 1)
	{
		ret.insert(0, 1, '1');
	}
	return ret;
}

//ģ�����������
//�������
std::string BigInt::sub(std::string num1, std::string num2)
{
	int len1 = num1.size();
	int len2 = num2.size();
	int diffNum = abs(len1 - len2);
	int longSize = len1 > len2 ? len1 : len2;
	//��λ����
	if (len1 < len2)
	{
		num1.insert(0, diffNum, '0');
	}
	else if (len2 < len1)
	{
		num2.insert(0, diffNum, '0');
	}
	std::string ret;
	ret.resize(longSize);
	//��������
	for (int i = longSize - 1; i >= 0; i--)
	{
		//�ж��Ƿ���Ҫ��λ
		if (num1[i] < num2[i])
		{
			num1[i] += 10;
			//���¸�λ
			num1[i - 1]--;
		}
		//�����֮�����ַ�
		ret[i] = (num1[i] - '0') - (num2[i] - '0') + '0';
	}
	//ɾ��ǰ��0
	while (ret.size() > 1 && ret[0] == '0')
	{
		ret.erase(0, 1);
	}
	return ret;
}

//ģ��˷�������
//�������
std::string BigInt::mul(std::string num1, std::string num2)
{
	/*
	1���ӵ�λ��ʼ���
	2��ÿһλģ��˷��Ĳ�������Ӧ��Ӧ�˷� + ��λ
	3�����£���Ӧλ�ͽ�λ
	4���������λ�Ƿ���Ҫ��λ
	5���ۼӣ���֮ǰ�Ľ�����ۼ�����һ�εĳ˷����(�������)
	*/

	//�򻯳˷��Ĺ��̣��Ƚ�С���� * �Ƚϴ����  num1 * num2
	if (num2.size() > num1.size())
	{
		swap(num2, num1);
	}
	std::string ret = "0";
	for (int i = num2.size() - 1; i >= 0; i--)
	{
		//��ȡ��ǰ������Ӧλ��ֵ
		int curDigit = num2[i] - '0';
		int step = 0;

		//��ǰλ�˻��Ľ��
		std::string temp = num1;
		for (int j = temp.size() - 1; j >= 0; j--)
		{
			//��λ���
			temp[j] = (temp[j] - '0') * curDigit + step;
			//���½�λֵ
			if (temp[j] > 9)
			{
				step = temp[j] / 10;
				temp[j] = temp[j] - step * 10;
			}
			else
			{
				step = 0;
			}
			//��ԭΪ�ַ�
			temp[j] += '0';
		}
		//����ж��Ƿ���Ҫ��λ
		if (step > 0)
		{
			temp.insert(0, 1, step + '0');
		}
		//����
		temp.append(num2.size() - 1 - i, '0');
		//�ۼ�һ�γ˷��Ľ��
		ret = add(ret, temp);
	}
	return ret;
}

//�������
//��������ʵ��
std::pair<std::string, std::string> BigInt::dev(std::string num1, std::string num2)
{
	std::string ret;//��
	std::string rem = num1;//����
	//���������зŴ󣬰���10�ı����Ŵ�
	int diffNum = num1.size() - num2.size();
	//�������
	num2.append(diffNum, '0');
	for (int i = 0; i <= diffNum; i++)
	{
		//��¼����ִ�еĴ���
		char count = '0';
		while (true)
		{
			//�������м�ȥ����
			if (less(rem, num2))
			{
				break;
			}
			//��Сһ�θ���һ������
			rem = sub(rem, num2);
			count++;
		}
		ret += count;
		//������Сʮ����
		num2.pop_back();
	}
	//ɾ��ǰ��0
	while (ret.size() > 1 && ret[0] == '0')
	{
		//ɾ���̵�ǰ��0
		ret.erase(0, 1);
	}
	//����<�̣�����>
	return make_pair(ret, rem);
}

//С���ж�
bool BigInt::less(std::string& num1, std::string& num2)
{
	if (num1.size() < num2.size())
	{
		return true;
	}

	if (num1.size() > num2.size())
	{
		return false;
	}

	//������ͬ��ʱ��
	return num1 < num2;
}

//<<����
std::ostream& operator<<(std::ostream&_cout, BigInt& bi)
{
	_cout << bi._number << std::endl;
	return _cout;
}

