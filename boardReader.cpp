#include "boardReader.hpp"

boardReader::boardReader(char* file_) {
	file.open(file_, std::ios_base::in);
	if(!file.is_open()) {
		//file.close();
		std::cout << "Could not open file " << file_ << std::endl;
	}
	std::string line, token;
	board temp;
	int row=0;
	std::getline(file, line);
	

	std::istringstream istream(line.c_str());
	for(;;) {
		if(!(istream>>token))
			break;
		parameters.push_back(std::stoi(token));
	}

	/*
	line.erase(std::remove_if(line.begin(), line.end(), [](char c) { return std::isspace(c); } ), line.end());
	for(char i : line) {
		parameters.push_back(odo::ctoi(i));
	}
	*/

	while(std::getline(file, line)) {
		temp.push_back(std::vector<int>());
		line.erase(std::remove_if(line.begin(), line.end(), [](char c) { return std::isspace(c); } ), line.end());
		for(char i : line) {
			temp[row].push_back(odo::ctoi(i));
		}
		line.clear();
		++row;
	}
	puzzle = temp;
}
boardReader::~boardReader() {
	if(file.is_open()) {
		file.close();
	}
}
std::vector<int> boardReader::getParam() {	// n, p, q
	return parameters;
}
board boardReader::getPuzzle() {	// reads and assigns board row by row
	return puzzle;
}
