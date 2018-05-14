#ifndef __BACKTRACKING_H__
#define __BACKTRACKING_H__

#include <vector>
#include <set>
#include <cmath>
#include <algorithm>
#include "defines.h"	
#include "bounds.h"
#include "utils.h"
#include "approximation.h"

using std::vector;
using std::set;

class backtracking {
public:
	backtracking(int n, int m, set<edge> &clients, bool bounds);
	vector<vertex> solve();

private:
	void sr(vector<edge> &permut, set<edge> &rem, int l0, int l1);
	vector<vertex> build_path();
	int minimum_length(const vector<edge> &permut);
	bool prune(vertex cur, set<edge> &rem, int len);
	void approximate();

	bool _bounds;
	int _n, _m;
	set<edge> _clients;
	int _opt_length;
	vector<edge> _opt_permut;
};

#endif