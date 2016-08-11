#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <vector>
#include <string>
#include "odo.hpp"

using board=std::vector<std::vector<int>>;
class sudoku {
	
public:
	sudoku();
	sudoku(int n, int p, int q);
	sudoku(sudoku& other);
	sudoku& operator=(const sudoku& rhs);
	~sudoku();

	int getP();
	int getQ();
	int getN();
	std::vector<int> getIndex(int i);

	std::vector<int> getParams();
	board getBoard();
	int getIndex(int row, int col);
	std::vector<int> get_row(int i);
	void setP(int p);
	void setQ(int q);
	void setN(int n);
	void setParam(std::vector<int> param);
	void setBoard(board b_);
	void setBoard(int n);
	void set_board(std::vector<int> rmo);
	void setIndex(int row, int col, int val);

	std::string toString();
	void printBoard();
	void printParam();
	
private:
	int n,p,q;
	board b;
	// int* b;	<= single array to store board. could be more efficient.
};

#endif
