#include "constraint.hpp"

constraint::constraint() {
}
constraint::constraint(sudoku& puzzle) : n(puzzle.getN()), p(puzzle.getP()), q(puzzle.getQ())
{
	rows_init(puzzle);
	setColumns();
	setBlocks();
	domain_init();
	if(tokenReader::lcv) {
		lcv_init();
	}
	if(tokenReader::dh) {
		dh_init();
	}
	if(tokenReader::mrv) {
		mrv_init();	
	}
	solution_init();
}
constraint::~constraint() {
}
// printing/debugging functions--------------------------------------------------------------------
void constraint::printRow(int r) { printer::print(rows[r]); }
void constraint::printCol(int c) { printer::print(columns[c]); }
void constraint::printBlock(int b) { printer::print(blocks[b]); }
void constraint::printRows() { printer::print(rows); }
void constraint::printColumns() { printer::print(columns); }
void constraint::printBlocks() { printer::print(blocks); }
void constraint::print_constraint_map() { printer::print(constraint_map); }
void constraint::print_constraints() {
	for(unsigned int i=0;i<domainMap.size(); ++i) {
		std::cout << i << ": ";
		for(int j : domainMap[i]) {
			std::cout  << (j) << " | ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
void constraint::printSolution() {
	int row = 0;
	for(int i : solution) {
		std::cout << i << " ";
		if(row == n-1) {
			std::cout << '\n';
			row = -1;
		}
		++row;
	}
	std::cout << '\n';
}
void constraint::print_mrv() {
	int k = 0;
	for(int i : mrv_map) {
		std::cout << "(" << k << ", " << i << ")";
		++k;
	}
}
void constraint::print_dh() {
	for(auto i : dh_map) {
		for(int j : i) {
			std::cout << j << " ";
		}
		std::cout << std::endl;
	}
}
// -------------------------------------------------------------------------------------------- 
void constraint::update_insert() {
	top_rank=n;
	refreshDomainMap();
}
void constraint::update_constraint_map(int i, int val) {
	constraint_map[i].push_back(val);
}
void constraint::set_index(int i, int val) {
	insert(i/n, i%n, val);
	solution[i] = val;
}
void constraint::t_fix(int i) {
	reset_constraint_map(i);
}
void constraint::bt_fix(int i) {
	std::vector<int> fm = constraint_map[i];
	int size = n*n;
	for(int k = 0;k<size;++k) {
		constraint_map[k].clear();
	}
	refreshDomainMap();
	constraint_map[i] = fm;
	fm.clear();
	std::set_difference(
			domainMap[i].begin(), domainMap[i].end(),
			constraint_map[i].begin(), constraint_map[i].end(),
			std::back_inserter(fm));
	domainMap[i]=fm;
}
void constraint::backtrack(int i, int val) {
	refreshDomainMap();
	constraint_map[i].push_back(val);
	std::sort(constraint_map[i].begin(), constraint_map[i].end());
	std::vector<int> temp;
	std::set_difference(
			domainMap[i].begin(), domainMap[i].end(),
			constraint_map[i].begin(), constraint_map[i].end(),
			std::back_inserter(temp));
	domainMap[i]=temp;
}
void constraint::dh_backtrack(int i, int val, std::stack<int> path) {
	refreshDomainMap();
	constraint_map[i].push_back(val);
	std::sort(constraint_map[i].begin(), constraint_map[i].end());
	std::vector<int> temp;
	apply_constraints(path);	
}
void constraint::apply_constraints(std::stack<int> path) {
	std::vector<int> temp;
	int i;
	while(!path.empty()) {
		i = path.top();
		temp.clear();
		std::set_difference(domainMap[i].begin(), domainMap[i].end(),
							constraint_map[i].begin(), constraint_map[i].end(),
							std::back_inserter(temp));
		domainMap[i] = temp;
		path.pop();
	}
}
// getter methods ---------------------------------------------------------------------------------
int constraint::get_n() {	return n;	}
int constraint::get_p() {	return p;	}
int constraint::get_q() {	return q;	}
int constraint::get_nns() {	 return nns;	}
int constraint::get_domain(int i) {
	return domainMap[i].front();	
}
std::vector<std::vector<int>> constraint::get_domain_map() {
	return domainMap;
}
int constraint::get_index(int i) {
	return solution[i];	
}
std::vector<int> constraint::get_constraint(int i) {
	return domainMap[i];
}
std::vector<int> constraint::get_solution() {
	return solution;
}
std::vector<int> constraint::get_constraints(int row, int col) {
	if(solution[((row*n)+col)] != 0) {
		return std::vector<int>();
	}
	std::set<int> temp; 
	for(int i : rows[row]) {
		if(i!=0)
			temp.insert(i);
	}
	for(int i : columns[col]) {
		if(i!=0)
			temp.insert(i);
	}
	for(int i : blocks[ ((row/p)*p) + (col/q)  ]) {
		if(i!=0)
			temp.insert(i);
	}
	std::vector<int> make;
	std::set_symmetric_difference(
			temp.begin(), temp.end(),
			domain.begin(), domain.end(),
			std::back_inserter(make) 
	);
	return make;
}
bool constraint::has_domain(int i) {
	return (!domainMap[i].empty());
}
bool constraint::is_empty(int i) {
	return (solution[i]==0);
}
// heuristic functions----------------------------------------------------------------------------
int constraint::get_mrv() {
	int max = n*n;
	top_rank = n;
	for(int i=0;i<max;++i) {
		if( (mrv_map[i] <= top_rank) && (solution[i] == 0) ) {
			if(tokenReader::dh && mrv_map[i] == top_rank) {
				if(dh_map[i/n][i%n] > dh_map[top_index/n][top_index%n]) {
					top_index = i;
					top_rank = mrv_map[i];
				}
				continue;
			}
			top_index = i;
			top_rank = mrv_map[i];
		}
	}
	return top_index;
}
int constraint::get_dh() {
	int dh_index=0, top_dh=0;
	for(int i=0;i<n;++i) {
		for(int j=0;j<n;++j) {
			if((dh_map[i][j] > top_dh) && (solution[((i*n)+j)] == 0) ) {
					top_dh = dh_map[i][j];
					dh_index = i*n+j;
			}
		}
	}
	return dh_index;
}
std::vector<int> constraint::get_dh_constraints(int row, int col) {
	int degree, min, max, tk;
	degree = 0;
	std::set<int> temp; 
	for(int i : blocks[ ((row/p)*p) + (col/q)  ]) {
		if(i!=0) 
			temp.insert(i);
		else
			++degree;
	}
	min = (col/q)*q;
	max = min+q-1;
	tk = 0;
	for(int i : rows[row]) {
		if(i!=0) 
			temp.insert(i);
		else{ 
			if(tk < min || tk > max)
				++degree;
		}
		++tk;
	}
	min = (row/p)*p;
	max = min+p-1;
	tk = 0;
	for(int i : columns[col]) {
		if(i!=0) 
			temp.insert(i);
		else {
			if(tk < min || tk > max)
				++degree;
		}
		++tk;
	}
	dh_map[row][col] = degree;
	std::vector<int> make;
	std::set_symmetric_difference(
			temp.begin(), temp.end(),
			domain.begin(), domain.end(),
			std::back_inserter(make) 
	);
	return make;
}
int constraint::get_lcv(int i) {
	if(domainMap[i].size()==1) {
		return domainMap[i].front();
	}
	lcv_rank = lcv_mask;
	std::vector<int> temp = domainMap[i];
	int col = i%n;
	int row = i/n;
	int block = ((((i/n)/p)*p)*n) + (((i%n)/q)*q);
	for(int i=0;i<n;++i)
		for(int j : domainMap[row+i])
			++lcv_rank[j-1];
	for(int i=0;i<n;++i) 
		for(int j : domainMap[col+(i*n)])
			++lcv_rank[j-1];
	for(int i=0;i<p;++i) 
		for(int j=0;j<q;++j)
			for(int k : domainMap[block+(i*n)+j])
				++lcv_rank[k-1];
	int lcv = temp.front();
	for(int i : temp) 
		if(lcv_rank[i-1] < lcv_rank[lcv-1])
			lcv = i;

	return lcv;
}
// private helper functions------------------------------------------------------------------------
void constraint::insert(int row, int col, int x) {
	rows[row][col] = x;
	columns[col][row] = x;
	blocks[(((row/p)*p)+(col/q))][(((row%p)*p)+ (col%q))] = x;
}
void constraint::rows_init(sudoku& puzzle) {
	rows = puzzle.getBoard();
}
void constraint::setColumns() {
	board col = board(n, std::vector<int>(n,0));
	for(int i=0;i<n;++i) {
		for(int j=0;j<n;++j) {
			col[i][j] = rows[j][i];
		}
	}
	columns = col;
}
void constraint::setBlocks() {
	int rs,cs,c_bl;
	if(p!=q)
		c_bl = p;
	else
		c_bl = q;
	rs=0;
	cs=0;
	for(int i=0;i<n;++i) {
		blocks.push_back(std::vector<int>());
		rs = ((i/p)*p);
		cs = ((i%c_bl)*q);
		for(int row=0;row<p;++row){
			for(int col=0;col<q;++col) {
				blocks[i].push_back( rows[rs+row][cs+col] );
			}
		}
	}
}
void constraint::refreshDomainMap() {
	int t=0;
	for(int i=0;i<n;++i) {
		for(int j=0;j<n;++j) {
			if(solution[t] == 0) {
				if(tokenReader::dh)
					domainMap[t] = get_dh_constraints(i,j);
				else
					domainMap[t] = get_constraints(i,j);
				if(tokenReader::mrv) {
					mrv_map[t] = domainMap[t].size();
				}
			}
			++t;
		}
	}
}
void constraint::solution_init() {
	constraint_map = std::vector<std::vector<int>>((n*n), std::vector<int>());
	nns =0;
	int t=0;
	for(int i=0;i<n;++i) {
		for(int j=0;j<n;++j) {
			solution.push_back( rows[i][j] );
			if(tokenReader::dh) 
				domainMap.push_back(get_dh_constraints(i,j));
			else
				domainMap.push_back(get_constraints(i,j));
			if(tokenReader::mrv)
				mrv_map[t] = domainMap.back().size();
			if(solution[t] != 0) {
				++nns;
				domainMap[t].clear();
				if(tokenReader::dh)
					dh_map[i][j] = 0;
			}
			++t;
		}
	}
}

void constraint::domain_init() {
	for(int i=1;i<=n;++i) {
		domain.push_back(i);
	}
}
void constraint::reset_constraint_map(int i) {
	constraint_map[i].clear();	
}
// private heuristic functions-----------------------------------------------------------------
void constraint::mrv_init() {
	mrv_map = std::vector<int>(n*n, 0);
}
void constraint::dh_init() {
	dh_map = std::vector<std::vector<int>>(n, std::vector<int>(n,0));
}
void constraint::lcv_init() {
	lcv_mask = std::vector<int>(n,0);
	lcv_rank = std::vector<int>(n,0);
}

