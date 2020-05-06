#include <iostream>
#include<time.h>
#include<math.h>
#include<fstream>
#include<boost/multiprecision/cpp_int.hpp>
#include<boost/multiprecision/random.hpp>
#include<boost/multiprecision/miller_rabin.hpp>
#include "rsa.h"
#include "BigInt.h"

#define NUMBER 256

DataType RSA :: getPrime() {//得到一个随机数并验证是否为素数
	std::cout << "getPrime()" << std::endl;

	boost::random::mt19937 gen(time(NULL));
	boost::random::uniform_int_distribution<DataType> dist(3, DataType(1) << 256);

	DataType prime;
	while (true) {
		prime = dist(gen);
		if (isBigPrime(prime)) {
			break;
		}
	}
	return prime;
}

//bool RSA::isPrime(DataType data) {//判断是否是素数
//	if (data < 0)
//		return false;
//	for (int i = 2; i <= sqrt(data); ++i) {
//		if (data % i == 0) {
//			return false;
//		}
//	}
//	return true;
//}

bool RSA::isBigPrime(DataType data) {
	boost::random::mt19937 gen2(time(nullptr));
	if (miller_rabin_test(data, 25, gen2)) {
		if (miller_rabin_test((data - 1) / 2, 25, gen2)) {
			return true;
		}
	}
	return false;
}

DataType RSA::getPkey(DataType data1, DataType data2) {//求n
	return data1 * data2;
}

DataType RSA::getOrla(DataType data1, DataType data2) {//求f(n)
	return ((data1 - 1) * (data2 - 1));
}

DataType RSA::getEkey(DataType orla) {//求e
	boost::random::mt19937 gen(time(nullptr));
	boost::random::uniform_int_distribution<DataType> dist(2, orla);
	DataType prime, x = 0, y = 0;
	while (true) {
		prime = dist(gen);
		if (getGcd(prime, orla, x, y) == 1) {
			return prime;
		}
	}
}
 
DataType RSA::getDkey(DataType ekey, DataType orla) {//求d
	/*DataType dkey = orla / ekey;
	while (true) {
		if ((dkey * ekey) % orla == 1) {
			return dkey;
		}
		++dkey;
	}*/
	DataType x = 0, y = 0;
	getGcd(ekey, orla, x, y);
	return (x % orla + orla) % orla;
}

//DataType RSA::getGcd(DataType data1, DataType data2) {//求最大公约数，判断e和f(n)是否互质
//	/*DataType tmp;
//	if (tmp = data1 % data2) {
//		data1 = data2;
//		data2 = tmp;
//	}
//	return data2;*/
//	if (data2 == 0) {
//		return data1;
//	}
//	return getGcd(data2, data1 % data2);
//}

DataType RSA::getGcd(DataType a, DataType b, DataType& x, DataType & y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	DataType gcd = getGcd(b, a % b, x, y);
	DataType x1 = x, y1 = y;
	x = y1;
	y = x1 - a / b * y1;
	return gcd;
}

DataType RSA :: ecrypt(DataType ekey, DataType pkey, DataType data) {// 加密
	//a(n) = (a(n-1) * a(n-1)) % c
	DataType i = data;
	DataType res = 1;

	while (ekey) {
		if (ekey & 1)
			res = (res * i) % pkey;
		ekey >>= 1;
		i = (i * i) % pkey;
	}
	return res;
}
DataType RSA :: decrypt(DataType dkey, DataType pkey, DataType data) {//解密
	//return (DataType)pow(data, dkey) % pkey;
	return ecrypt(dkey, pkey, data);
} 

void RSA::getKeys() {//实现转换
	DataType prime1 = getPrime();
	std::cout << "prime1 : " << prime1 << std::endl;
	DataType prime2 = getPrime();
	std::cout << "prime2 : " << prime2 << std::endl;
	while (prime1 == prime2) {
		prime2 = getPrime();
	}
	
	DataType orla = getOrla(prime1, prime2);
	std::cout << "orla :" << orla << std::endl;
	m_key.m_pkey = getPkey(prime1, prime2);
	std::cout << "p : " << m_key.m_pkey << std::endl;
	m_key.m_ekey = getEkey(orla);
	std::cout << "e : " << m_key.m_ekey << std::endl;
	m_key.m_dkey = getDkey(m_key.m_ekey, orla);
	std::cout << "d : " << m_key.m_dkey << std::endl;
}

RSA::RSA()
{
	getKeys();
}

void RSA ::ecrypt(const char * filename, const char * fileout) {//加密接口
	std::ifstream fin(filename, std::ifstream::binary);
	std::ofstream fout(fileout, std::ifstream::binary);

	if (!fin.is_open()) {
		perror("input file open failed!");
		return;
	}
	char* buffer = new char[NUMBER];
	DataType* bufferout = new DataType[NUMBER];
	while (!fin.eof()) {
		fin.read(buffer, NUMBER);
		int curnum = fin.gcount();//最近一次读取的字节数
		for (int i = 0; i < curnum; ++i) {
			bufferout[i] = ecrypt(m_key.m_ekey, m_key.m_pkey, (DataType)buffer[i]);
		}
		fout.write((char*)bufferout, curnum * sizeof(DataType));
	}
	fout.close();
	fin.close();
}
void RSA ::decrypt(const char * filename, const char * fileout) {//解密接口
	std::ifstream fin(filename, std::ifstream::binary);
	std::ofstream fout(fileout, std::ofstream::binary);

	if (!fin.is_open()) {
		perror("input file open is failed!");
		return;
	}

	DataType * buffer = new DataType[NUMBER];
	char * bufferout = new char[NUMBER];
	while (!fin.eof()) {
		fin.read((char*)buffer, NUMBER * sizeof(DataType));
		int curnum = fin.gcount();
		curnum /= sizeof(DataType);
		for (int i = 0; i < curnum; ++i) {
			bufferout[i] = (char)decrypt(m_key.m_dkey, m_key.m_pkey, buffer[i]);
		}
		fout.write(bufferout, curnum);
	}
	fout.close();
	fin.close();
}

Key RSA :: getallKey() {
	return m_key;
}
