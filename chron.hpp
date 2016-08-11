#ifndef CHRON_HPP
#define CHRON_HPP

#include <iostream>
#include <chrono>
#include <string>

class chron {
private:
	static std::clock_t t_total_start;
	static std::clock_t t_start;
	static std::clock_t t_stop;
	static std::clock_t t_acp_start;
	static std::clock_t t_acp_stop;
	static double time;
	static double total_start;
	static double start;
	static double stop;
	static double acp_start;
	static double acp_stop;
	static double timeout;
public:
	static void mark_total_start(); 
	static void mark_start(); 
	static void mark_stop(); 
	static bool mark_check();
	static void mark_acp_start();
	static void mark_acp_stop(); 
	static double get_time(); 
	static double get_total_start(); 
	static double get_start(); 
	static double get_stop(); 
	static double get_acp_start();
	static double get_acp_stop(); 

	static void set_timeout(double t);
	static double get_timeout();
};
#endif
