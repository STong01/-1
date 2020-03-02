#include <iostream>
#include <time.h>
#include <math.h>
#include <fstream>
#include "RSA.h"

//���캯��
RSA::RSA()
{
	getKeys();
}

//�����ļ�
void RSA::ecrept(const char* filename, const char* fileout)
{
	std::ifstream fin(filename, std::ifstream::binary);//���������ļ�����
	//binary�ļ��򿪷�ʽ���˴�Ϊ������
	std::ofstream fout(fileout, std::ifstream::binary);//��������ļ�����
	if (!fin.is_open())//�ж��Ƿ�ɹ����ļ�
	{
		perror("input file open failed!");
		return;
	}

	char* buffer = new char[NUMBER];
	DataType* bufferOut = new DataType[NUMBER];
	while (!fin.eof())
	{
		fin.read(buffer, NUMBER);//ÿ�ζ�ȡ�ļ����Լ���ȡ���ļ���С
		int curNum = fin.gcount();//���һ�ζ�ȡ���ֽ���
		for (int i = 0; i < curNum; i++)
		{
			//��ÿ���ֽڽ��м��ܲ���
			bufferOut[i] = ecrept((DataType)buffer[i], _key._ekey, _key._pkey);
		}
		fout.write((char*)bufferOut, curNum*sizeof(DataType));//�ļ�д����
	}
	delete[] bufferOut;
	delete[] buffer;
	fin.close();
	fout.close();
}

//�����ļ�
void RSA::decrept(const char* filename, const char* fileout)
{
	std::ifstream fin(filename, std::ifstream::binary);
	std::ofstream fout(fileout, std::ifstream::binary);
	if (!fin.is_open())
	{
		perror("file open failed!");
		return;
	}
	DataType* buffer = new DataType[NUMBER];

	char* bufferOut = new char[NUMBER];
	while (!fin.eof())
	{
		fin.read((char*)buffer, NUMBER * sizeof(DataType));
		int num = fin.gcount();
		num /= sizeof(DataType);
		for (int i = 0; i < num; i++)
		{
			//��ÿ���ֽڽ��н��ܲ���
			bufferOut[i] = (char) decrept(buffer[i], _key._dkey, _key._pkey);
		}
		fout.write(bufferOut, num);
	}
	delete[] bufferOut;
	delete[] buffer;
	fout.close();
	fin.close();
}

//������������keyֵ
void RSA::getKeys()
{
	DataType prime1 = getPrime();//����������������
	DataType prime2 = getPrime();
	while (prime1 == prime2)
	{
		prime2 = getPrime();
	}
	
	DataType orla = getOrla(prime1, prime2);
	std::cout << "orla finish" << std::endl;
	_key._pkey = getPkey(prime1, prime2);
	std::cout << "n finish" << std::endl;
	_key._ekey = getEkey(orla);
	std::cout << "e finish" << std::endl;
	_key._dkey = getDkey(_key._ekey, orla);
	std::cout << "d finish" << std::endl;
}

Key RSA::getallKey()
{
	return _key;
}

//����
DataType RSA::ecrept(DataType data, DataType ekey, DataType pkey)
{
	//i : 0....���һλ
	DataType Ai = data;
	DataType msgE = 1;
	//data^ekey % pkey
	while (ekey)
	{
		if (ekey & 1)
		{
			msgE = (msgE * Ai) % pkey;
		}
		ekey >>= 1;// ekey /= 2;
		Ai = (Ai * Ai) % pkey;
	}
	return msgE;
}

//����
DataType RSA::decrept(DataType data, DataType dkey, DataType pkey)
{
	return ecrept(data, dkey, pkey);
}

//��������
DataType RSA::getPrime()
{
	std::cout << "getPrime()" << std::endl;
	//srand(time(NULL));
	brdm::mt19937 gen(time(NULL));
	brdm::uniform_int_distribution<DataType> dist(0, DataType(1) << 256);

	DataType prime;
	while (true)
	{
		//prime = rand() % 100 + 2;//(2 - 102)
		prime = dist(gen);
		//std::cout << "BigInt Random: " << prime << std::endl;
		if (isPrimeBigInt(prime))
		{
			break;
		}
	}
	std::cout << "getPrime() finish" << std::endl;
	return prime;
}

//�ж��ǲ�������
bool RSA::isPrime(DataType data)
{
	std::cout << "isPrime()" << std::endl;
	if (data <= 0)
	{
		return false;
	}

	for (int i = 2; i < sqrt(data); i++)
	{
		if (data%i == 0)
		{
			return false;
		}
	}
	std::cout << "isPrime() finish" << std::endl;
	return true;
}

//�����ж��Ƿ�Ϊ����
bool RSA::isPrimeBigInt(DataType data)
{
	brdm::mt11213b gen(time(nullptr));
	//25Ϊ0.25���ݴ���
	if (miller_rabin_test(data, 25, gen))
	{
		if (miller_rabin_test((data - 1) / 2, 25, gen))
		{
			return true;
		}
	}
	return false;
}

//������Կ n = ���� * ����
DataType RSA::getPkey(DataType prime1, DataType prime2)
{
	return prime1 * prime2;
}

//����ŷ������ f(n) = (����p - 1) * (����q - 1)
DataType RSA::getOrla(DataType prime1, DataType prime2)
{
	return (prime1 - 1)*(prime2 - 1);
}

//����������Կe: 1 < e < f(n)
DataType RSA::getEkey(DataType orla)
{
	//srand(time(NULL));
	brdm::mt19937 gen(time(NULL));
	brdm::uniform_int_distribution<DataType> dist(2, orla);
	DataType ekey;
	while (true)
	{
		//ekey = rand() % orla;
		ekey = dist(gen);
		if (ekey > 1 && getGcd(ekey, orla) == 1)
		{
			return ekey;
		}
	}
}

//����������Կd: e * d % f(n) = 1
DataType RSA::getDkey(DataType ekey, DataType orla)
{
	DataType x = 0, y = 0;
	exGcd(ekey, orla, x, y);
	//�任���ý�����Կ��һ���Ƚ�С����ֵ
	return (x % orla + orla) % orla;
	//DataType dkey = orla / ekey;
	//while (true)
	//{
	//	if ((dkey *ekey) % orla == 1)
	//	{
	//		return dkey;
	//	}
	//	dkey++;
	//}
}

//������Լ��(շת�����)
DataType RSA::getGcd(DataType data1, DataType data2)
{
	DataType residual;//����
	while (residual = data1 % data2)
	{
		data1 = data2;
		data2 = residual;
	}
	return data2;
}

//��ģ��Ԫ�أ���������Կ
//ŷ������㷨
DataType RSA::exGcd(DataType a, DataType b, DataType& x, DataType& y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	DataType gcd = exGcd(b, a % b, x, y);
	DataType x1 = x, y1 = y;
	x = y1;
	y = x1 - a / b * y1;
	return gcd;
}