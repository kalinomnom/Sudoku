#ifndef BTSOLVER_HPP
#define BTSOLVER_HPP

#include <algorithm>
#include <set>
#include <map>
#include <stack>
#include <utility>
#include <iostream>
#include <vector>
#include "sudoku.hpp"
#include "constraint.hpp"
#include "chron.hpp"
#include "tokenReader.hpp"
#include "printer.hpp"

class BTSolver {
public:
	BTSolver();
	BTSolver(sudoku& board);

	std::vector<int> get_solution();
	std::vector<int> get_mrv_solution();
	std::vector<int> get_dh_solution();
	int get_nodes();
	int get_deadends();
	std::stack<int> get_path();
	bool has_solution();
	bool get_timeout();
private:
	constraint constraints;
	std::stack<int> path;
	std::stack<int> bt;
	std::vector<int> bt_rank;
	std::set<int> aem;
	bool solved=false;
	bool timeout=false;
	int nodes;
	int deadends;
	void initDomain();
};
#endif
