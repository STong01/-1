#include <iostream>
#include <fstream>
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
	////�ı���ʽ�򿪣����տո���߻��н������ݶ�ȡ
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

	//��������ʽ��
	//std::ifstream fin("test.txt", std::ifstream::binary);
	//char buffer[100] = { 0 };
	//fin.read(buffer, 100);
	//cout << fin.gcount() << endl;
	//cout << buffer << endl;

	A a;
	a.a = 1;
	a.c = 'a';
	a.f = 2.2;

	//�ַ���
	/*std::ofstream fout("testout.txt");
	fout << a.a << endl;
	fout << a.c << " " << a.f << endl;*/
	
	//�ֽ���
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

	rsa.ecrept("test.txt", "test.ecrpet.txt");
	rsa.decrept("test.ecrpet.txt", "test.decrpet.txt");
}

int main()
{
	//test();
	testFile();
	system("pause");
	return 0;
}