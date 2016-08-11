#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <thread>
#include <vector>
#include <set>
#include <stack>
#include <string>

#include "BTSolver.hpp"
#include "chron.hpp"
#include "odo.hpp"
class solution {
private:
	std::string status;
	int nodes;
	int deadends;
	std::stack<int> path;
	std::vector<int> key;
	bool solved;
public:
	solution();
	solution(BTSolver& bt);	
	~solution();
	std::string get_status();
	int get_nodes();
	int get_deadends();
	std::string get_solution(); 
	std::stack<int> get_path();
	bool has_solution();
};

#endif
