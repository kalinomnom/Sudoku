#include "tokenReader.hpp"

bool tokenReader::bt=false;
bool tokenReader::fc=false;
bool tokenReader::acp=false;
bool tokenReader::mrv=false;
bool tokenReader::dh=false;
bool tokenReader::lcv=false;
bool tokenReader::gen=false;
void tokenReader::getTokens(int& argc, char**& argv) {
	char* temp;
	for(int i=4; i < argc; ++i) {
		temp = argv[i];
		if(!std::strcmp(temp, "BT")) {
			tokenReader::bt=true;
		}
		else if(!std::strcmp(temp, "FC")) {
			tokenReader::fc=true;
		}
		else if(!std::strcmp(temp, "ACP")) {
			tokenReader::acp=true;
		}
		else if(!std::strcmp(temp, "MRV")) {
			tokenReader::mrv=true;
		}
		else if(!std::strcmp(temp, "DH")) {
			tokenReader::dh=true;
		}
		else if(!std::strcmp(temp, "LCV")) {
			tokenReader::lcv=true;
		}
		else if(!std::strcmp(temp, "GEN")) {
			tokenReader::gen=true;
		}
	}
}
