#ifndef ODO_HPP
#define ODO_HPP

#include <cctype>
#include <vector>
#include <string>
// static functions to convert string to int and int to string
// functions accout for alpha numerics
// each one is O(1) time since the conversion is arithmetic instead of searching a string. ideally, this is faster.

class odo {
public:
	static int otoi(std::string value) {
		char c = value.at(0);
		if(std::isdigit(c))
			return (int)c - 48;
		return (int)c - 55;
	}
	static std::string itoo(int num) {
		std::string s;
		if(num<=9)
			return s = std::to_string(num);
		else {
			char c = num+55;
			return s = c;
		}
		return s;
	}
	static int ctoi(char value) {
		if(std::isdigit(value))
			return (int)value - 48;
		return (int)value - 55;
	}
	static char itoc(int num) {
		if(num<=9)
			return (char)(num+48);
		else
			return (char)(num+55);
	}
};
#endif
