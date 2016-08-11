#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <iostream>
#include <random>
#include "sudoku.hpp"
#include "constraint.hpp"
#include "BTSolver.hpp"
#include "tokenReader.hpp"
#include "solution.hpp"
#include "chron.hpp"
class generator {
public:
	static sudoku generate_puzzle(int m, int n, int p, int q);
private:

};
#endif
