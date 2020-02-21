#pragma once

#define NUMBER 256

typedef long DataType;

struct Key
{
	//(e, n), (d, n)
	DataType _ekey;//������Կ
	DataType _dkey;//������Կ
	DataType _pkey;//��Կ
};

/*
1����������
2����n
3����f(n)
4����e   1 < e < f(n),e��f(n)���ɻ��ʣ����ѡ��
5����d  e * d % f(n) = 1
*/

/*
p = 5, q = 3
n = 3 * 5 = 15
f(n) = f(15) = f(5) * f(3) = 4 * 2 = 8
�������Կe: 1 < e < 8,e��8���ɻ��ʹ�ϵ: 3
�������Կd: e * d % f(n) == 1
d = 3

����(3, 15) ����(3, 15)
����: ����: 2---> 2 ^ 3 % 15 = ����: 8
����: ����: 8---> 8 ^ 3 % 15 = ����: 2
*/

class RSA
{
public:
	RSA();
	void ecrept(const char* filename, const char* fileout);//�����ļ�
	void decrept(const char* filename, const char* fileout);//�����ļ�
	
	DataType ecrept(DataType data, DataType ekey, DataType pkey);//����
	DataType decrept(DataType data, DataType dkey, DataType pkey);//����
	DataType getPrime();//��������
	bool isPrime(DataType data);//�ж��ǲ�������
	DataType getPkey(DataType prime1, DataType prime2);//������Կ
	DataType getOrla(DataType prime1, DataType prime2);//����ŷ������
	DataType getEkey(DataType orla);//����������Կ
	DataType getDkey(DataType ekey, DataType orla);//����������Կ
	DataType getGcd(DataType data1, DataType data2);//������Լ��
	void getKeys();//��������keyֵ
	Key getallKey();

private:
	Key _key;
};