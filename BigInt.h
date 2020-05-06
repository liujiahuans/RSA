#pragma once

#include<iostream>
#include<string>
#include<utility>
#include<boost/multiprecision/cpp_int.hpp>
#include<boost/multiprecision/random.hpp>

class BigInt {
public:
	BigInt();
	BigInt(const std::string & num);
	//BigInt(const int num);
	BigInt operator+(BigInt bi);
	BigInt operator-(BigInt bi);
	BigInt operator*(BigInt bi);
	BigInt operator/(BigInt bi);
	BigInt operator%(BigInt bi);
	friend std::ostream& operator<<(std::ostream & _cout, BigInt &bi);

private:
	std::string Add(std::string str1, std::string str2);
	std::string Sub(std::string str1, std::string str2);
	std::string Mul(std::string str1, std::string str2);
	std::pair<std::string, std::string> Dev(std::string str1, std::string str2);
	bool less(std::string str1, std::string str2);
	//产生大数随机数算法
	//素性检测算法

	std::string m_number;
};