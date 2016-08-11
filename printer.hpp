#ifndef PRINTER_HPP
#define PRINTER_HPP

#include <vector>

class printer {
public:
	static void print(std::vector<int>& n) {
		std::cout << "(";
		for(int i : n ) {
			std::cout << i << ",";
		}
		std::cout << ")\n";
	}
	static void print(std::set<int>& n) {
		std::cout << "(";
		for(int i : n ) {
			std::cout << i << ",";
		}
		std::cout << ")\n";
	}
	static void print(std::vector<std::vector<int>>& n) {
		for( auto i : n ) {
			for( int j : i ) {
				std::cout << j << ", ";
			}
			std::cout << std::endl;
		}
		std::cout << "\n";
	}

};

#endif
