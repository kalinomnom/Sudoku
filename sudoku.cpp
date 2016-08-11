#include <iostream>
#include <vector>

#include "sudoku.hpp"
sudoku::sudoku() {
}
sudoku::sudoku(sudoku& other)  {
	n = other.getN();
	p = other.getP();
	q = other.getQ();
	b = other.getBoard();
}

sudoku::sudoku(int n_, int p_, int q_)
{
	if(n_ != p_*q_ || n_<1) {
		setP(3);
		setQ(3);
		setN(9);
		setBoard(9);
	}
	else {
		setP(p_);
		setQ(q_);
		setN(n_);
		setBoard(n);
	}
}
sudoku& sudoku::operator=(const sudoku& rhs) {
	if(this == &rhs)
		return *this;
	n = rhs.n;
	p = rhs.p;
	q = rhs.q;
	b = rhs.b;
	return *this;
}
sudoku::~sudoku(void) {
}
int sudoku::getP()  {
	return p;
}
int sudoku::getQ() {
	return q;
}
int sudoku::getN()  {
	return n;
}
std::vector<int> sudoku::getIndex(int i) {
	return b[i];
}
void sudoku::setP(int p_) {
	p = p_;
}
void sudoku::setQ(int q_) {
	q = q_;
}
void sudoku::setN(int n_) {
	n = n_;
}
std::vector<int> sudoku::get_row(int i) {
	return b[i];
}
std::vector<int> sudoku::getParams()  {
	std::vector<int> temp = {n, p, q};
	return temp;
}
board sudoku::getBoard()  {
	return b;
}
void sudoku::setParam(std::vector<int> param) {
	n = param[0];
	p = param[1];
	q = param[2];
}
void sudoku::setBoard(board b_) {
	b = b_;
}
void sudoku::setBoard(int n) {		// nxn with all 0's
	b = board(n, std::vector<int>(n, 0));
}
void sudoku::set_board(std::vector<int> rmo) {
	int max = n*n;
	for(int i=0;i<max;++i ) {
		b[i/n][i%n] = rmo[i];
	}
}
void sudoku::setIndex (int row, int col, int val){
	b[row][col] = val;
}
std::string sudoku::toString() {
	std::string s = "wabadubadub";
	return s;
}
int sudoku::getIndex(int row, int col) {
	return b[row][col];
}
void sudoku::printBoard() {
	for(int i=0; i<n; ++i) {
		std::cout << " | ";
		for(int j=0; j<n; ++j) {
			std::cout << odo::itoo(b[i][j]) << " | ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
void sudoku::printParam() {
	std::cout << "N: " << n << " p: " << p << " q: " << q << std::endl;
}
