#include "bigInt.h"

BigInt::BigInt(const std::string& num)
	:_number(num)
{}

//大数运算符重载
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

//模拟加法的运算
//大数相加
std::string BigInt::add(std::string num1, std::string num2)
{
	//位数补齐
	int len1 = num1.size();
	int len2 = num2.size();
	int diffNum = abs(len1 - len2);
	int longSize = len1 > len2 ? len1 : len2;
	//补位操作
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
	//逐位相加
	int step = 0;
	for (int i = longSize - 1; i >= 0; i--)
	{
		ret[i] = (num1[i] - '0') + (num2[i] - '0') + step;
		ret[i] += '0';
		//更新
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

//模拟减法的运算
//大数相减
std::string BigInt::sub(std::string num1, std::string num2)
{
	int len1 = num1.size();
	int len2 = num2.size();
	int diffNum = abs(len1 - len2);
	int longSize = len1 > len2 ? len1 : len2;
	//补位操作
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
	//减法操作
	for (int i = longSize - 1; i >= 0; i--)
	{
		//判断是否需要借位
		if (num1[i] < num2[i])
		{
			num1[i] += 10;
			//更新高位
			num1[i - 1]--;
		}
		//相减完之后变回字符
		ret[i] = (num1[i] - '0') - (num2[i] - '0') + '0';
	}
	//删除前置0
	while (ret.size() > 1 && ret[0] == '0')
	{
		ret.erase(0, 1);
	}
	return ret;
}

//模拟乘法的运算
//大数相乘
std::string BigInt::mul(std::string num1, std::string num2)
{
	/*
	1、从低位开始相乘
	2、每一位模拟乘法的操作：对应相应乘法 + 进位
	3、更新：对应位和进位
	4、考虑最高位是否需要进位
	5、累加，在之前的结果上累加最新一次的乘法结果(补零操作)
	*/

	//简化乘法的过程，比较小的数 * 比较大的数  num1 * num2
	if (num2.size() > num1.size())
	{
		swap(num2, num1);
	}
	std::string ret = "0";
	for (int i = num2.size() - 1; i >= 0; i--)
	{
		//获取当前乘数对应位的值
		int curDigit = num2[i] - '0';
		int step = 0;

		//当前位乘积的结果
		std::string temp = num1;
		for (int j = temp.size() - 1; j >= 0; j--)
		{
			//逐位相乘
			temp[j] = (temp[j] - '0') * curDigit + step;
			//更新进位值
			if (temp[j] > 9)
			{
				step = temp[j] / 10;
				temp[j] = temp[j] - step * 10;
			}
			else
			{
				step = 0;
			}
			//还原为字符
			temp[j] += '0';
		}
		//最后判断是否需要进位
		if (step > 0)
		{
			temp.insert(0, 1, step + '0');
		}
		//补零
		temp.append(num2.size() - 1 - i, '0');
		//累加一次乘法的结果
		ret = add(ret, temp);
	}
	return ret;
}

//大数相除
//借助减法实现
std::pair<std::string, std::string> BigInt::dev(std::string num1, std::string num2)
{
	std::string ret;//商
	std::string rem = num1;//余数
	//给除数进行放大，按照10的倍数放大
	int diffNum = num1.size() - num2.size();
	//补零操作
	num2.append(diffNum, '0');
	for (int i = 0; i <= diffNum; i++)
	{
		//记录减法执行的次数
		char count = '0';
		while (true)
		{
			//在余数中减去除数
			if (less(rem, num2))
			{
				break;
			}
			//减小一次更新一次余数
			rem = sub(rem, num2);
			count++;
		}
		ret += count;
		//除数减小十倍；
		num2.pop_back();
	}
	//删除前置0
	while (ret.size() > 1 && ret[0] == '0')
	{
		//删除商的前面0
		ret.erase(0, 1);
	}
	//返回<商，余数>
	return make_pair(ret, rem);
}

//小于判断
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

	//长度相同的时候
	return num1 < num2;
}

//<<重载
std::ostream& operator<<(std::ostream&_cout, BigInt& bi)
{
	_cout << bi._number << std::endl;
	return _cout;
}

