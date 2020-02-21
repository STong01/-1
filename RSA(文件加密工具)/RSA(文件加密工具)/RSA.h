#pragma once

#define NUMBER 256

typedef long DataType;

struct Key
{
	//(e, n), (d, n)
	DataType _ekey;//加密密钥
	DataType _dkey;//解密密钥
	DataType _pkey;//公钥
};

/*
1、产生素数
2、求n
3、求f(n)
4、求e   1 < e < f(n),e和f(n)构成互质，随机选择
5、求d  e * d % f(n) = 1
*/

/*
p = 5, q = 3
n = 3 * 5 = 15
f(n) = f(15) = f(5) * f(3) = 4 * 2 = 8
求加密密钥e: 1 < e < 8,e和8构成互质关系: 3
求解密密钥d: e * d % f(n) == 1
d = 3

加密(3, 15) 解密(3, 15)
加密: 明文: 2---> 2 ^ 3 % 15 = 密文: 8
解密: 密文: 8---> 8 ^ 3 % 15 = 明文: 2
*/

class RSA
{
public:
	RSA();
	void ecrept(const char* filename, const char* fileout);//加密文件
	void decrept(const char* filename, const char* fileout);//解密文件
	
	DataType ecrept(DataType data, DataType ekey, DataType pkey);//加密
	DataType decrept(DataType data, DataType dkey, DataType pkey);//解密
	DataType getPrime();//产生素数
	bool isPrime(DataType data);//判断是不是素数
	DataType getPkey(DataType prime1, DataType prime2);//产生公钥
	DataType getOrla(DataType prime1, DataType prime2);//产生欧拉函数
	DataType getEkey(DataType orla);//产生加密密钥
	DataType getDkey(DataType ekey, DataType orla);//产生解密密钥
	DataType getGcd(DataType data1, DataType data2);//求解最大公约数
	void getKeys();//产生所有key值
	Key getallKey();

private:
	Key _key;
};