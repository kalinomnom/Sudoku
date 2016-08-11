#include "BTSolver.hpp"

BTSolver::BTSolver() {
}
BTSolver::BTSolver(sudoku& board_) : constraints(board_) {
	nodes = 0;
	deadends = 0;
	int n = constraints.get_n();
	bt_rank = std::vector<int>(n*n, 0);
}
std::vector<int> BTSolver::get_solution() {
	int n = constraints.get_n();
	int i=0;
	int a =0;
	int max = n*n;
	while(i < max) {
		if(chron::mark_check()) {
			timeout = true;
			std::cout << "Timeout\n";
			return constraints.get_solution();
		}
		if(constraints.get_index(i) == 0) {
			if( constraints.has_domain(i) ) {
				path.push(i);
				if(tokenReader::lcv) 
					a = constraints.get_lcv(i);
				else 
					a = constraints.get_domain(i);
				bt.push(a);
				constraints.set_index(i, a);
				constraints.update_insert();
				++i;
				++nodes;
				continue;
			}
			else {
				if( path.empty() ) {
					return constraints.get_solution();	
				}
				else {
					constraints.t_fix(i);
					i = path.top();
					constraints.set_index(i, 0);
					constraints.backtrack(i, bt.top());
					bt.pop();
					path.pop();
					if(path.empty())
						i=0;
					else
						i = path.top();
					++deadends;
					continue;
				}
			}
		}
		else {
			++i;
		}
	}
	solved=true;
	return constraints.get_solution();
}
std::vector<int> BTSolver::get_mrv_solution() {
	int n = constraints.get_n();
	int i=0;
	int max = n*n;
	int a, sol;
	sol = constraints.get_nns();
	while(sol < max) {
		if(chron::mark_check()) {
			timeout = true;
			std::cout << "Timeout\n";
			return constraints.get_solution();
		}
		i = constraints.get_mrv();
		if( constraints.has_domain(i) ) {
			path.push(i);
			if(tokenReader::lcv) 
				a = constraints.get_lcv(i);
			else 
				a = constraints.get_domain(i);
			bt.push(a);
			constraints.set_index(i, a);
			constraints.update_insert();
			++nodes;
			++sol;
			continue;
		}
		else {
			if( path.empty() ) {
				return constraints.get_solution();	
			}
			else {
				constraints.t_fix(i);
				i = path.top();
				constraints.set_index(i, 0);
				constraints.backtrack(i, bt.top());
				bt.pop();
				path.pop();
				++deadends;
				--sol;
				continue;
			}
		}
	}
	solved=true;
	std::cout << "\n";
	constraints.printSolution();
	return constraints.get_solution();
}
std::vector<int> BTSolver::get_dh_solution() {
	int n = constraints.get_n();
	int i=0;
	int max = n*n;
	int a, sol;
	sol = constraints.get_nns();
	while(sol < max) {
		if(chron::mark_check()) {
			timeout = true;
			std::cout << "Timeout\n";
			return constraints.get_solution();
		}
		i = constraints.get_dh();
		if( constraints.has_domain(i) ) {
			path.push(i);
			if(tokenReader::lcv) 
				a = constraints.get_lcv(i);
			else 
				a = constraints.get_domain(i);
			bt.push(a);
			constraints.set_index(i, a);
			constraints.update_insert();
			++nodes;
			++sol;
			continue;
		}
		else {
			if( path.empty() ) {
				return constraints.get_solution();	
			}
			else {
				constraints.t_fix(i);
				i = path.top();
				constraints.set_index(i, 0);
				constraints.backtrack(i, bt.top());
				bt.pop();
				path.pop();
				if(path.size() ==0) {
					constraints.bt_fix(constraints.get_dh());
				}
				++deadends;
				--sol;
				continue;
			}
		}
	}
	solved=true;
	std::cout << "\n";
	constraints.printSolution();
	return constraints.get_solution();
}
bool BTSolver::has_solution() {
	return solved;
}
bool BTSolver::get_timeout() {
	return timeout;
}
int BTSolver::get_nodes() {
	return nodes;
}
int BTSolver::get_deadends() {
	return deadends;
}
std::stack<int> BTSolver::get_path() {
	return path;
}
