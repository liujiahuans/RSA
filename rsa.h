#pragma once
#include<boost/multiprecision/cpp_int.hpp>
#include<boost/multiprecision/random.hpp>
typedef boost::multiprecision::int1024_t DataType;

struct Key {
	DataType m_ekey;//私钥
	DataType m_dkey;//公钥
	DataType m_pkey;//明文
};

/*
1、得到素数p、q
2、求n = pq
3、欧拉函数f(n)
4、求e 1 < e < f(n) e与f(n)互质
5、求d de mod f(n) = 1
6、公钥(e, n) 私钥(d, n)
*/
class RSA {
public:
	RSA();
	DataType getPrime();//得到一个素数
	//bool isPrime(DataType data);//判断是否是素数
	bool isBigPrime(DataType data);//检测是否为大数素数
	DataType getPkey(DataType data1, DataType data2);//求n
	DataType getOrla(DataType data1, DataType data2);//求f(n)
	DataType getEkey(DataType orla);//求e
	DataType getDkey(DataType ekey, DataType orla);//求d
	//DataType getGcd(DataType data1, DataType data2);//判断e和f(n)是否互质
	DataType getGcd(DataType a, DataType b, DataType& x, DataType & y);
	DataType ecrypt(DataType ekey, DataType pkey, DataType data);//加密
	DataType decrypt(DataType dkey, DataType pkey, DataType data);//解密
	void ecrypt(const char * filename, const char * fileout);//加密接口
	void decrypt(const char * filename, const char * fileout);//解密接口
	void getKeys();//实现转换
	Key getallKey();
private:
	Key m_key;
};
