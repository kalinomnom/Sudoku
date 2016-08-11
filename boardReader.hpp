#ifndef BOARDREADER_HPP
#define BOARDREADER_HPP

#include <locale>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cctype>
#include <list>
#include <algorithm>
#include <vector>
#include "sudoku.hpp"
#include "odo.hpp"
class boardReader {
public:
	boardReader(char* file);
	~boardReader();
	std::vector<int> getParam();
	board getPuzzle();
private:
	std::ifstream file;
	board puzzle;
	std::vector<int> parameters;
};

#endif
