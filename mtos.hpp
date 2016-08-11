#ifndef MTOS_HPP
#define MTOS_HPP

#include <vector>
#include <utility>

// static class that gets the row/col/block of an index
// also converts sudoku row/col index to row-major order index and
// vice-versa

class mtos {
public:
	// getter functions
	static int get_col(int i, int n) {
		return (i%n);
	}
	static int get_row(int i, int n) {
		return (i/n);
	}
	static int get_block(int i, int n, int p, int q) {
		return ( (((i/n)/p)*p) + ((i%n)/q)  );
	}
	static int get_block(int row, int col, int n, int p, int q) {
		int temp = ptoi(row, col, n);
		 return get_block(temp, n, p, q);
	}
	// converter functions
	// int to row/column pair
	static std::pair<int,int> itop(int i, int n) {
		int row = ( (i/n) );
		int col = ( (i%n) );
		return std::pair<int,int>(row,col);
	}
	// row, column to RMO index
	static int ptoi(int row, int col, int n) {
		return ( (row*n) + col );	
	}
};
#endif
