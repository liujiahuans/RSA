#pragma once
#include<boost/multiprecision/cpp_int.hpp>
#include<boost/multiprecision/random.hpp>
typedef boost::multiprecision::int1024_t DataType;

struct Key {
	DataType m_ekey;//˽Կ
	DataType m_dkey;//��Կ
	DataType m_pkey;//����
};

/*
1���õ�����p��q
2����n = pq
3��ŷ������f(n)
4����e 1 < e < f(n) e��f(n)����
5����d de mod f(n) = 1
6����Կ(e, n) ˽Կ(d, n)
*/
class RSA {
public:
	RSA();
	DataType getPrime();//�õ�һ������
	//bool isPrime(DataType data);//�ж��Ƿ�������
	bool isBigPrime(DataType data);//����Ƿ�Ϊ��������
	DataType getPkey(DataType data1, DataType data2);//��n
	DataType getOrla(DataType data1, DataType data2);//��f(n)
	DataType getEkey(DataType orla);//��e
	DataType getDkey(DataType ekey, DataType orla);//��d
	//DataType getGcd(DataType data1, DataType data2);//�ж�e��f(n)�Ƿ���
	DataType getGcd(DataType a, DataType b, DataType& x, DataType & y);
	DataType ecrypt(DataType ekey, DataType pkey, DataType data);//����
	DataType decrypt(DataType dkey, DataType pkey, DataType data);//����
	void ecrypt(const char * filename, const char * fileout);//���ܽӿ�
	void decrypt(const char * filename, const char * fileout);//���ܽӿ�
	void getKeys();//ʵ��ת��
	Key getallKey();
private:
	Key m_key;
};
