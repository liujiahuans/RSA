#include<iostream>
#include"BigInt.h"
#include<boost/multiprecision/cpp_int.hpp>
#include<boost/multiprecision/random.hpp>


BigInt::BigInt(const std::string & num)
	:m_number(num) { }
//BigInt::BigInt(const int num) {
//
//}

BigInt BigInt :: operator+(BigInt bi) {
	std::string ret = Add(m_number, bi.m_number);
	return BigInt(ret);
}
BigInt BigInt :: operator-(BigInt bi) {
	std::string ret = Sub(m_number, bi.m_number);
	return BigInt(ret);
}
BigInt BigInt :: operator*(BigInt bi) {
	std::string ret = Mul(m_number, bi.m_number);
	return BigInt(ret);
}
BigInt BigInt :: operator/(BigInt bi) {
	std::pair<std::string, std::string> ret = Dev(m_number, bi.m_number);
	return BigInt(ret.first);
}
BigInt BigInt :: operator%(BigInt bi) {
	std::pair<std::string, std::string> ret = Dev(m_number, bi.m_number);
	return BigInt(ret.second);
}

BigInt:: BigInt() {}
std::string BigInt :: Add(std::string str1, std::string str2) {
	while (str1.size() < str2.size()) {
		str1 = '0' + str1;
	}
	while (str1.size() > str2.size()) {
		str2 = '0' + str2;
	}
	int longsize = str1.size() > str2.size() ? str1.size() : str2.size();

	int step = 0;
	std::string res;
	res.resize(longsize);
	for (int i = str1.size() - 1; i > -1; --i) {
		res[i] = (str1[i] - '0') + (str2[i] - '0') + step + '0';
		if (res[i] > '9') {
			res[i] -= 10;
			step = 1;
		}
		else {
			step = 0;
		}
	}
	if (step == 1) {
		res = '1' + res;
	}
	return res;
}
std::string BigInt::Sub(std::string str1, std::string str2) {
	while (str1.size() < str2.size()) {
		str1 = '0' + str1;
	}
	while (str1.size() > str2.size()) {
		str2 = '0' + str2;
	}
	int longsize = str1.size() > str2.size() ? str1.size() : str2.size();

	int step = 0;
	std::string res;
	res.resize(longsize);
	for (int i = longsize - 1; i > -1; --i) {
		if (str1[i] < str2[i]) {
			str1[i] += 10;
			str1[i - 1]--;
		}
		res[i] = (str1[i] - '0') - ( str2[i] - '0') + '0';
	}
	while (res.size() > 1 && res[0] == '0') {
		res.erase(0, 1);
	}
	 
	return res;
}
std::string BigInt::Mul(std::string str1, std::string str2) {
	if (str1.size() < str2.size()) {
		swap(str2, str1);
	}
	std::string res("0");

	for (int i = str2.size() - 1; i >= 0; --i) {
		int cur = str2[i] - '0';
		int step = 0;

		std::string tmp = str1;
		for (int j = tmp.size() - 1; j >= 0; --j) {
			tmp[j] = (tmp[j] - '0') * cur + step;
			if (tmp[j] > 9) {
				step = tmp[j] / 10;
				tmp[j] = tmp[j] - step * 10;
			}
			tmp[j] += '0';
		}
		if (step > 0) {
			tmp.insert(0, 1, step + '0');
		}
		tmp.append(str2.size() - 1 - i, '0');
		res = Add(res, tmp);
	}

	return res;
}

std ::pair<std::string, std::string> BigInt :: Dev(std::string str1, std::string str2) {
	std::string res;
	std::string rem = str1;

	int difNum = str1.size() - str2.size();
	str2.append(difNum, '0');
	for (int i = 0; i <= difNum; ++i) {
		char count = '0';
		while (true) {
			if (less(rem, str2))
				break;
			rem = Sub(rem, str2);
			++count;
		}
		res += count;
		str2.pop_back();
	}

	while (res.size() > 1 && res[0] == '0') {
		res.erase(0, 1);
	}

	return make_pair(res, rem);
}
bool BigInt :: less(std ::string str1, std ::string str2) {
	if (str1.size() < str2.size())
		return true;
	if (str2.size() < str1.size())
		return false;
	return str1 < str2;
}

std::ostream& operator<<(std::ostream & _cout, BigInt &bi) {
	_cout << bi.m_number << std::endl;
	return _cout;
}