#include "solution.hpp"

solution::solution(BTSolver& bt) : status("error"), solved(false), nodes(0), deadends(0){
	chron::mark_acp_start();
	chron::mark_acp_stop();
	chron::mark_start();
	if(tokenReader::mrv) {
		key = bt.get_mrv_solution();
	}
	else if(tokenReader::dh) {
		key = bt.get_dh_solution();
	}
	else {
		key = bt.get_solution();
	}
	chron::mark_stop();
	std::cout << std::setprecision(4) << std::fixed << chron::get_total_start() << " " << chron::get_time() << '\n';
	if(!bt.has_solution()) {
		status = "error";
	}
	else if(bt.get_timeout()) {
		status = "timeout";
	}
	else {
		status = "success";
		solved=true;
	}
	nodes = bt.get_nodes();
	deadends = bt.get_deadends();
}
solution::~solution() {
}
std::string solution::get_status() {
	return status;
}
int solution::get_nodes() {
	return nodes;
}
int solution::get_deadends() {
	return deadends;
}
std::string solution::get_solution() {
	std::string temp = "(";
	for(int i : key) {
		temp+=(odo::itoo(i));
		temp.push_back(',');
	}
	temp.push_back(')');
	return temp;
}
std::stack<int> solution::get_path() {
	return path;
}
bool solution::has_solution() {
	return solved;
}
