#pragma once
#include <string>
#include <utility>

class BigInt
{
public:
	BigInt(){}
	BigInt(const std::string& num);
	BigInt(const int num);
//private:
	std::string add(std::string num1, std::string num2);//大数相加
	std::string sub(std::string num1, std::string num2);//大数相减
	std::string mul(std::string num1, std::string num2);//大数相乘
	std::pair<std::string, std::string> dev(std::string num1, std::string num2);//大数相除


	//通过字符串表示
	std::string _number;
};