#include<iostream>
#include<fstream>
#include "rsa.h"
#include"BigInt.h"
#include<type_traits>
//#include<boost/multiprecision/cpp_int.hpp>
#include<boost/multiprecision/random.hpp>



using std::cout;
using std::cin;
using std::endl;

void test() {
	RSA rsa;
	//RSA();
	//rsa.getPrime();
	//rsa.getKeys();
	Key key = rsa.getallKey();

	DataType original = 2;
	DataType ecrept = rsa.ecrypt(key.m_ekey, key.m_pkey, original);
	DataType decrept = rsa.decrypt(key.m_dkey, key.m_pkey, ecrept);

	rsa.ecrypt("test.txt", "test.ecrypt.txt");
	rsa.decrypt("test.ecrypt.txt", "test.decrypt.txt");

	cout << "original : " << original << endl;
	cout << "ecrept : " << ecrept << endl;
	cout << "decrept : " << decrept << endl;

}

//struct A {
//	char a;
//	int b;
//	float f;
//};
void testFile() {

	/*std::ifstream fin("test.txt");
	char c;
	int a;
	double d;

	fin >> c;
	fin >> a;
	fin >> d;

	cout << "a : " << a << " c :" << c << " d :" << d << endl;*/

	/*std::ifstream fin("test.txt", std::ifstream::binary);
	char buffer[100] = { 0 };
	fin.read(buffer, 100);
	cout << fin.gcount() << endl;
	cout << buffer << endl;*/

	/*A a;
	a.a = 's';
	a.b = 233;
	a.f = 12.322;	*/
	/*字符流操作*/
	/*std::ofstream fout("testout.txt");
	fout << a.a << endl;
	fout << a.b << ' ' << a.f << endl;*/

	/*字节流操作*/
	/*std::ofstream fout("testout.txt", std::ofstream::binary);
	fout.write((char*)&a, sizeof(A));
	fout.close();*/
	/*std::ifstream fin("testout.txt", std::ifstream::binary);
	A b;
	fin.read((char*)&b, sizeof(A));
	cout << b.a << ' ' << b.b << ' ' << b.f << endl;*/

	RSA rsa;
	rsa.ecrypt("test.txt", "test.ecrypt.txt");
	rsa.decrypt("test.ecrypt.txt", "test.decrypt.txt");
}

void testBigInt() {
	BigInt bi;
	//bi.Dev("198765342", "934");

	BigInt a("7564");
	BigInt b("7654");
	int aa = 7564;
	int bb = 7654;
	cout << a << endl;
	cout << b << endl;
	cout << aa * bb << endl;
	BigInt c = a * b;
	cout << c << endl;
 }

void testRandom() {
	//生成随机数
	/*boost::random::mt19937 gen(time(NULL));
	boost::random::uniform_int_distribution<DataType> dist(0, DataType(1) << 1023);
	for (int i = 0; i < 100; ++i) {
		DataType num = dist(gen);
		cout << num << endl;
	}*/
	/*boost::multiprecision::cpp_int cppInt(DataType(1) << 1023);
	cout << cppInt << endl;
	cout << cppInt + 1 << endl;

	boost::multiprecision::int1024_t cpp1024(DataType(1) << 1023);
	cout << cpp1024 << endl;
	cout << cpp1024 + 1 << endl;

	boost::multiprecision::int1024_t cpp1024_2 = boost::multiprecision::int1024_t(1) << 1023;
	cout << "cpp1024 << 1023 :" << endl;
	cout << cpp1024_2 << endl;*/
}

int main() {
	test();
	//testFile();
	//testBigInt();
	//testRandom();
	return 0;
}