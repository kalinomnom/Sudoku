#include "chron.hpp"

// static variable initialization
std::clock_t chron::t_total_start;
std::clock_t chron::t_start;
std::clock_t chron::t_stop;
std::clock_t chron::t_acp_start;
std::clock_t chron::t_acp_stop;
double chron::time=0;
double chron::total_start=0;
double chron::start=0;
double chron::stop=0;
double chron::acp_start=0;
double chron::acp_stop=0;
double chron::timeout=0;

// marker methods
void chron::mark_total_start() {
		t_total_start = std::clock();
		total_start = (std::clock() - t_total_start)/(double)CLOCKS_PER_SEC;
}
void  chron::mark_start() {
		t_start = std::clock();
		start = (t_start - t_total_start)/(double)CLOCKS_PER_SEC;
}
void chron::mark_stop() {
		t_stop = std::clock();
		stop = (t_stop - t_start)/(double)CLOCKS_PER_SEC;
}
bool chron::mark_check() {
		std::clock_t temp = std::clock();
		double check = (temp - t_start)/(double)CLOCKS_PER_SEC;
		return(check > timeout);
}
void chron::mark_acp_start() {
		t_acp_start = std::clock();
		acp_start = (t_acp_start - t_total_start)/(double)CLOCKS_PER_SEC;
}
void chron::mark_acp_stop() {
		t_acp_stop = std::clock();
		acp_stop = (t_acp_stop - t_total_start)/(double)CLOCKS_PER_SEC;
}
// getter static methods
double chron::get_time() {
		time = ((t_acp_stop - t_acp_start) + (t_stop - t_start))/(double)CLOCKS_PER_SEC;
		return time;
}
double chron::get_total_start() {
		return total_start;
}
double chron::get_start() {
		return start;
}
double chron::get_stop() {
		return stop;
}
double chron::get_acp_start() {
		return acp_start;
}
double chron::get_acp_stop() {
		return acp_stop;
}
// timeout calls
void chron::set_timeout(double t) {
	timeout = t;
}
double chron::get_timeout() {
		return timeout;
}
