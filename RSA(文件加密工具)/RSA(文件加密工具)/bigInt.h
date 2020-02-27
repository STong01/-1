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

	// 运算符重载
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
	std::string add(std::string num1, std::string num2);//大数相加
	std::string sub(std::string num1, std::string num2);//大数相减
	std::string mul(std::string num1, std::string num2);//大数相乘
	std::pair<std::string, std::string> dev(std::string num1, std::string num2);//大数相除
	bool less(std::string& num1, std::string& num2);//小于判断

	//通过字符串表示
	std::string _number;
};