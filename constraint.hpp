#ifndef CONSTRAINT_HPP 
#define CONSTRAINT_HPP

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <set>
#include <algorithm>
#include <utility>
#include <vector>
#include <list>
#include <stack>
#include "sudoku.hpp"
#include "tokenReader.hpp"
#include "printer.hpp"
#include "mtos.hpp"

class constraint {
public:
	constraint();
	constraint( sudoku& puzzle);
	~constraint();
	void printRow(int r);
	void printCol(int c);
	void printBlock(int b);
	void printRows();
	void printColumns();
	void printBlocks();
	void print_constraints();
	void printSolution();
	void print_constraint_map();
	void print_mrv();
	void print_dh();
	
	void update_insert();
	void update_constraint_map(int i, int val);
	void t_fix(int i);
	void bt_fix(int i);
	void set_index(int i, int val);
	void backtrack(int i, int val);
	void dh_backtrack(int i, int val, std::stack<int> path);
	void apply_constraints(std::stack<int> path);

	int get_n();
	int get_p();
	int get_q();
	int get_nns();
	int get_domain(int i);
	std::vector<std::vector<int>> get_domain_map();
	int get_mrv(int i);
	int get_index(int i);
	std::vector<int> get_constraint(int i);
	std::vector<int> get_solution();
	std::vector<int> get_constraints(int row, int col);
	bool has_domain(int i);
	bool is_empty(int i);
	// heuristic functions
	int get_mrv();
	int get_dh();
	int get_lcv(int i);
	std::vector<int> get_dh_constraints(int row, int col);
private:
	std::vector<std::vector<int>> rows;
	std::vector<std::vector<int>> blocks;
	std::vector<std::vector<int>> columns;
	int n, p, q, nns;
	std::vector<std::vector<int> > domainMap;
	std::vector<std::vector<int> > constraint_map;
	std::vector<int> solution;
	std::vector<int> domain;
	// heuristic variables
	std::vector<int> mrv_map;
	int top_index;
	int top_rank;
	std::vector<std::vector<int>> dh_map;
	std::vector<int> lcv_mask;
	std::vector<int> lcv_rank;

	void insert(int row, int col, int x);
	void rows_init(sudoku& puzzle);
	void setColumns();
	void setBlocks();

	void refreshDomainMap();
	void solution_init();
	void domain_init();
	void reset_constraint_map(int i);
	// heuristic private func
	void mrv_init();
	void dh_init();
	void lcv_init();
};
#endif
