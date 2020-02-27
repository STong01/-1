#pragma once
#include <string>
#include <utility>
#include <iostream>

class BigInt
{
public:
	BigInt(){}
	BigInt(const std::string& num);
	BigInt(const int num);
	BigInt operator+(BigInt& bi);
	BigInt operator-(BigInt& bi);
	BigInt operator*(BigInt& bi);
	BigInt operator/(BigInt& bi);
	BigInt operator%(BigInt& bi);
	friend std::ostream& operator<<(std::ostream&_cout, BigInt& bi);

	BigInt& operator+=(BigInt& bi);
	BigInt& operator-=(BigInt& bi);
	BigInt& operator*=(BigInt& bi);
	BigInt& operator/=(BigInt& bi);
	BigInt& operator%=(BigInt& bi);

	// ���������
#if 0
	//++a
	BigInt& operator++();
	//a++
	BigInt operator++(int);

	//--a
	BigInt& operator--();
	//a--
	BigInt operator--(int);

#endif

private:
	std::string add(std::string num1, std::string num2);//�������
	std::string sub(std::string num1, std::string num2);//�������
	std::string mul(std::string num1, std::string num2);//�������
	std::pair<std::string, std::string> dev(std::string num1, std::string num2);//�������
	bool less(std::string& num1, std::string& num2);//С���ж�

	//ͨ���ַ�����ʾ
	std::string _number;
};