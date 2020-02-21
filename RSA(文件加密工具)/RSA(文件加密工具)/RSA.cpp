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
			bufferOut[i] = decrept(buffer[i], _key._dkey, _key._pkey);
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
	_key._pkey = getPkey(prime1, prime2);
	_key._ekey = getEkey(orla);
	_key._dkey = getDkey(_key._ekey, orla);
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
		ekey >>= 1;
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
	srand(time(NULL));
	DataType prime;
	while (true)
	{
		prime = rand() % 100 + 2;//(2 - 102)
		if (isPrime(prime))
		{
			break;
		}
	}
	return prime;
}

//�ж��ǲ�������
bool RSA::isPrime(DataType data)
{
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
	return true;
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
	srand(time(NULL));
	DataType ekey;
	while (true)
	{
		ekey = rand() % orla;
		if (ekey > 1 && getGcd(ekey, orla) == 1)
		{
			return ekey;
		}
	}
}

//����������Կd: e * d % f(n) = 1
DataType RSA::getDkey(DataType ekey, DataType orla)
{
	DataType dkey = orla / ekey;
	while (true)
	{
		if ((dkey *ekey) % orla == 1)
		{
			return dkey;
		}
		dkey++;
	}
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
