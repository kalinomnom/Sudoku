#ifndef BOARDWRITER_HPP
#define BOARDWRITER_HPP

#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <stack>
#include <chrono>
#include <ctime>

#include "BTSolver.hpp"
#include "sudoku.hpp"
#include "solution.hpp"
#include "tokenReader.hpp"
#include "chron.hpp"

class boardWriter {
public:
	boardWriter(char* path);
	~boardWriter();
	void write_puzzle( sudoku& p);
	void writeSolution(solution sol);
private:
	std::ofstream file;
};
#endif
