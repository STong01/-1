#include <iostream>
#include <time.h>
#include <math.h>
#include <fstream>
#include "RSA.h"

//构造函数
RSA::RSA()
{
	getKeys();
}

//加密文件
void RSA::ecrept(const char* filename, const char* fileout)
{
	std::ifstream fin(filename, std::ifstream::binary);//构建输入文件对象
	//binary文件打开方式，此处为二进制
	std::ofstream fout(fileout, std::ifstream::binary);//构建输出文件对象
	if (!fin.is_open())//判断是否成功打开文件
	{
		perror("input file open failed!");
		return;
	}

	char* buffer = new char[NUMBER];
	DataType* bufferOut = new DataType[NUMBER];
	while (!fin.eof())
	{
		fin.read(buffer, NUMBER);//每次读取文件，以及读取的文件大小
		int curNum = fin.gcount();//最近一次读取的字节数
		for (int i = 0; i < curNum; i++)
		{
			//对每个字节进行加密操作
			bufferOut[i] = ecrept((DataType)buffer[i], _key._ekey, _key._pkey);
		}
		fout.write((char*)bufferOut, curNum*sizeof(DataType));//文件写操作
	}
	delete[] bufferOut;
	delete[] buffer;
	fin.close();
	fout.close();
}

//解密文件
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
			//对每个字节进行解密操作
			bufferOut[i] = decrept(buffer[i], _key._dkey, _key._pkey);
		}
		fout.write(bufferOut, num);
	}
	delete[] bufferOut;
	delete[] buffer;
	fout.close();
	fin.close();
}

//产生所有所需key值
void RSA::getKeys()
{
	DataType prime1 = getPrime();//产生两个所需素数
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

//加密
DataType RSA::ecrept(DataType data, DataType ekey, DataType pkey)
{
	//i : 0....最后一位
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

//解密
DataType RSA::decrept(DataType data, DataType dkey, DataType pkey)
{
	return ecrept(data, dkey, pkey);
}

//产生素数
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

//判断是不是素数
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

//产生公钥 n = 素数 * 素数
DataType RSA::getPkey(DataType prime1, DataType prime2)
{
	return prime1 * prime2;
}

//产生欧拉函数 f(n) = (素数p - 1) * (素数q - 1)
DataType RSA::getOrla(DataType prime1, DataType prime2)
{
	return (prime1 - 1)*(prime2 - 1);
}

//产生加密密钥e: 1 < e < f(n)
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

//产生解密密钥d: e * d % f(n) = 1
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

//求解最大公约数(辗转相除法)
DataType RSA::getGcd(DataType data1, DataType data2)
{
	DataType residual;//余数
	while (residual = data1 % data2)
	{
		data1 = data2;
		data2 = residual;
	}
	return data2;
}
