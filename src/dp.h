#ifndef __DP_H__
#define __DP_H__

#include <vector>
#include <map>
#include <set>
#include "defines.h"
#include "utils.h"
#include "bounds.h"

using std::pair;
using std::set;
using std::map;
using std::vector;

struct dp_state {
	vertex cur;
	set<edge> rem;

	dp_state(vertex c, set<edge> &r) : cur(c), rem(r) {}
};

struct dp_state_comparer {
	bool operator()(const dp_state &s1, const dp_state &s2) const {
		if (s1.cur < s2.cur or (s1.cur == s2.cur and s1.rem < s2.rem)) {
			return true;
		}
		return false;
	}
};

class dp {
public:
	dp(int n, int m, set<edge> &clients, bool bounds);
	vector<vertex> solve();

private:
	int sr(vertex cur, set<edge> &rem, int len);
	vector<vertex> build_path();
	bool prune(vertex &cur, set<edge> &rem, int len);

	bool _bounds;
	int _n, _m;
	set<edge> _clients;
	map<dp_state, int, dp_state_comparer> _opt;
	map<dp_state, pair<edge, int>, dp_state_comparer> _suc;
	pair<edge, int> _opt_start;
	int _opt_length;
};

#endif