#include <iostream>
#include <exception>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <unistd.h>
#include <stdio.h>
#include "odo.hpp"
#include "mtos.hpp"
#include "printer.hpp"
#include "boardReader.hpp"
#include "boardWriter.hpp"
#include "constraint.hpp"
#include "BTSolver.hpp"
#include "sudoku.hpp"
#include "solution.hpp"
#include "chron.hpp"
#include "tokenReader.hpp"
#include "generator.hpp"
int main(int argc, char* argv[]) {

	chron::mark_total_start();
	if(argc < 3){ 
		std::cout << "Incorrect program command parameters.";
		return 0;
	}
	tokenReader::getTokens(argc, argv);
	sudoku puzzle0;
	boardReader board(argv[1]);

	puzzle0.setParam(board.getParam());
	puzzle0.setBoard(board.getPuzzle());

	boardWriter writeFile(argv[2]);
	chron::set_timeout( std::atoi(argv[3]) );
	BTSolver solver(puzzle0);
	solution sol(solver);
	writeFile.writeSolution(sol);
/*
	int m, n, p, q;
	m = std::atoi(argv[2]);
	n = std::atoi(argv[3]);
	p = std::atoi(argv[4]);
	q = std::atoi(argv[5]);
	boardWriter writeFile(argv[1]);
	sudoku gen(n,p,q);
	gen = generator::generate_puzzle(m,n,p,q);
	writeFile.write_puzzle(gen);
*/	
	return 0;
}
