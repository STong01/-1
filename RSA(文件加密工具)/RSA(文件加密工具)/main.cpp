//#define  _SCL_SECURE_NO_WARNINGS  添加至预处理器
#include <iostream>
#include <fstream>
#include <boost/multiprecision/cpp_int.hpp>
#include "bigInt.h"
#include "RSA.h"
using namespace std;

void test()
{
	RSA rsa;
	rsa.getKeys();
	Key key = rsa.getallKey();
	cout << "keys:" << endl;
	cout << key._ekey << " " << key._dkey << " " << key._pkey << endl;

	DataType original = 2;
	DataType decout = rsa.ecrept(original, key._ekey, key._dkey);
	cout << "original : " << original << endl;
	cout << "ecrept:" << decout << endl;
	cout << "decrpet:" << rsa.decrept(decout, key._dkey, key._pkey) << endl;
}

struct A
{
	int a;
	char c;
	float f;
};

void testFile()
{
	//std::ifstream fin("test.txt");
	////文本形式打开，按照空格或者换行进行数据读取
	//char c;
	//int a;
	//double d;
	//fin >> c;
	//cout << fin.gcount() << endl;
	//fin >> a;
	//cout << fin.gcount() << endl;
	//fin >> d;
	//cout << fin.gcount() << endl;
	//cout << "a: " << a << " c: " << c << " d: " << d << endl;

	//二进制形式打开
	//std::ifstream fin("test.txt", std::ifstream::binary);
	//char buffer[100] = { 0 };
	//fin.read(buffer, 100);
	//cout << fin.gcount() << endl;
	//cout << buffer << endl;

	A a;
	a.a = 1;
	a.c = 'a';
	a.f = 2.2;

	//字符流
	/*std::ofstream fout("testout.txt");
	fout << a.a << endl;
	fout << a.c << " " << a.f << endl;*/
	
	//字节流
	std::ofstream fout("textout2.txt", std::ofstream::binary);
	fout.write((char*)&a, sizeof(A));
	fout.close();
	std::ifstream fin("testout2.txt", std::ifstream::binary);
	A b;
	fin.read((char*)&b, sizeof(A));
	cout << b.a << " " << b.c << " " << b.f << endl;

}

void testRSA()
{
	RSA rsa;
	Key key = rsa.getallKey();
	cout << "(e,n)" << key._ekey << "," << key._pkey << endl;
	cout << "(d,n)" << key._dkey << "," << key._pkey << endl;
	rsa.ecrept("test.txt", "test.ecrpet.txt");
	rsa.decrept("test.ecrpet.txt", "test.decrpet.txt");
}

//验证加法
void testBigIntAdd()
{
	BigInt bi;
	int a = 198765342;
	int b = 93476581;

	cout << a + b << endl;
	//cout << bi.add("198765342", "93476581") << endl;
	BigInt aa = "198765342";
	BigInt bb = "93476581";
	cout << aa + bb << endl;
}

//验证减法
void testBigIntSub()
{
	BigInt bi;
	int a = 198765342;
	int b = 93476581;

	cout << a - b << endl;
	//cout << bi.sub("198765342", "93476581") << endl;
	BigInt aa = "198765342";
	BigInt bb = "93476581";
	cout << aa - bb << endl;
}

//验证乘法
void testBigIntMul()
{
	BigInt bi;
	int a = 1234;
	int b = 3421;

	cout << a * b << endl;
	//cout << bi.mul("1234", "3421") << endl;
	BigInt aa = "1234";
	BigInt bb = "3421";
	cout << aa * bb << endl;
}

//验证除法
void testBigIntDev()
{
	BigInt bi;
	int a = 3421;
	int b = 1234;

	cout << a / b << endl;
	cout << a % b << endl;
	//cout << bi.dev("3421", "1234").first << endl;
	//cout << bi.dev("3421", "1234").second << endl;
	BigInt aa = "3421";
	BigInt bb = "1234";
	cout << aa / bb << endl;
	cout << aa % bb << endl;

}

//大数操作，大数文件boost
void testBoostBigInt()
{
	boost::multiprecision::cpp_int ci;
	ci = 1024;
	cout << ci << endl;
	//常量太大
	//ci = 1234567765234568765434567874345678874345687643456;
	std::string num = "1234567765234568765434567874345678874345687643456";
	
	//拷贝构造
	boost::multiprecision::cpp_int cppInt(num);
	cout << cppInt << endl;
	cout << cppInt + 1 << endl;

	//后面数字表示最大多少位
	boost::multiprecision::int1024_t cpp1024(num);
	cout << cpp1024 << endl;
	cout << cpp1024 + 1<< endl;

	boost::multiprecision::int1024_t cpp1024_2 = boost::multiprecision::int1024_t(1) << 1023;
	cout << cpp1024_2 << endl;

}

void testBoostRandom()
{
	//大数随机数产生
	boost::random::mt19937 gen(time(NULL));
	//随机数范围限定在(0, 100)
	//boost::random::uniform_int_distribution<DataType> dist(0, 100);
	boost::random::uniform_int_distribution<DataType> dist(0, DataType(1) << 1023);
	for (int i = 0; i < 100; i++)
	{
		DataType num = dist(gen);
		cout << num << endl;
	}
}

int main()
{
	//test();
	//testFile();
	testRSA();
	//testBoostBigInt();
	//testBoostRandom();
	system("pause");
	return 0;
}