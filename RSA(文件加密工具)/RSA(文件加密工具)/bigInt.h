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
	std::string add(std::string num1, std::string num2);//�������
	std::string sub(std::string num1, std::string num2);//�������
	std::string mul(std::string num1, std::string num2);//�������
	std::pair<std::string, std::string> dev(std::string num1, std::string num2);//�������


	//ͨ���ַ�����ʾ
	std::string _number;
};