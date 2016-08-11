#ifndef TOKENREADER_HPP
#define TOKENREADER_HPP

#include <iostream>
#include <vector>
#include <cstring>

class tokenReader {
public:
	static void getTokens(int& argc, char**& argv);
	static void print_tokens();
	static bool bt;
	static bool fc;
	static bool acp;
	static bool mrv;
	static bool dh;
	static bool lcv;
	static bool gen;
};
#endif
