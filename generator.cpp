#include "generator.hpp"

sudoku generator::generate_puzzle( int m, int n, int p, int q) {
	sudoku gen(n,p,q);
	if(!(n == (p*q))) {
		std::cout << "Invalid parameters: " << n << ", " << p << ", " << " or " << q << std::endl;
		sudoku s;
		return s;
	}
	chron::set_timeout(300);
	std::vector<int> domain;
	int temp, r_num;
	std::random_device rd;
	int max = n*n;
	tokenReader::mrv=true;
	while(true) {

		sudoku gen(n,p,q);
		constraint cpt(gen);
		int i=0;
		while(i < m) {
			temp = (rd()%max);
			if(cpt.is_empty(temp)) {
				r_num = (rd()%n);
				domain = cpt.get_constraint(temp);
				for(int j : domain) {
					if(j == r_num) {
						cpt.set_index(temp, r_num);
						cpt.update_insert();
						++i;
					}
				}
			}
		}
		domain = cpt.get_solution();
		gen.set_board(domain);
		BTSolver solver(gen);
		solution ff(solver);
		if(ff.has_solution()) {
			domain = cpt.get_solution();
			gen.printBoard();
			std::cout << "\n" << m << "\n";
			return gen;
		}
	}
}
