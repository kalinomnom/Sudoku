#include "boardWriter.hpp"

boardWriter::boardWriter(char* path) : file(path) {
	if(!file.is_open()) {
		std::cout << "File " << path << " could not be opened."<< std::endl;
		exit(0);
	}
}
boardWriter::~boardWriter() {
	if(file.is_open()) {
		file.close();
	}
}
void boardWriter::writeSolution(solution sol) {
	file << "TOTAL_START=" << chron::get_total_start() << '\n';

	file << "PREPROCESSING_START=" << chron::get_acp_start() << '\n';

	file << "PREPROCESSING_DONE=" << chron::get_acp_stop() << '\n';

	file << "SEARCH_START=" << chron::get_start() << '\n';

	file << "SEARCH_DONE=" << chron::get_stop() << '\n';

	file << "SOLUTION_TIME=" << chron::get_time() << '\n';

	file << "STATUS=" << sol.get_status() << '\n';

	file << "SOLUTION=" << sol.get_solution() << '\n';

	file << "COUNT_NODES=" << sol.get_nodes() << '\n';

	file << "COUNT_DEADENDS " << sol.get_deadends() << '\n';
}
void boardWriter::write_puzzle(sudoku& puzzle) {
	std::vector<int> temp;
	temp = puzzle.getParams();
	std::cout << "gen";
	for(int i : temp) {
		file << i << " ";
	}
	int line = puzzle.getN();
	file << "\n";
	for(int i=0;i<line;++i) {
		temp = puzzle.get_row(i);
		for(int j : temp) {
			file << j << " ";
		}
		file << "\n";
	}
	std::cout << "file written";
}
