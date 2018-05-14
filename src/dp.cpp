#include "dp.h"
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include "defines.h"
#include "utils.h"
#include "bounds.h"

using std::pair;
using std::set;
using std::map;
using std::vector;

dp::dp(int n, int m, set<edge> &clients, bool bounds) : 
		_n(n), _m(m), _clients(clients), _opt_length(INF), _bounds(bounds) {}

vector<vertex> dp::solve() {
	set<edge> rem(_clients);

	for (edge e : _clients) {
		rem.erase(e);
		int l0 = sr(e[0], rem, 0);
		int l1 = sr(e[1], rem, 0);
		rem.insert(e);
		if (fmin(l0, l1) < _opt_length) {
			_opt_length = fmin(l0, l1);
			if (l0 <= l1) {
				_opt_start = mp(e, 0);
			} else {
				_opt_start = mp(e, 1);
			}
		}
	}

	return build_path();
}

int dp::sr(vertex cur, set<edge> &rem, int len) {
	dp_state st(cur, rem);
	if (_opt.count(st) > 0) {
		return _opt[st];
	}
	if (rem.size() == 0) {
		_opt[st] = 0;
		return 0;
	}
	
	if (_bounds and prune(cur, rem, len)){
		return INF;
	}

	for (edge e : _clients) {
		if (rem.count(e) > 0) {
			rem.erase(e);
			int l0 = dist(cur, e[0]) + sr(e[0], rem, len + dist(cur, e[0]));
			int l1 = dist(cur, e[1]) + sr(e[1], rem, len + dist(cur, e[1]));
			rem.insert(e);
			if (_opt.count(st) == 0 or fmin(l0, l1) < _opt[st]) {
				_opt[st] = fmin(l0, l1);
				if (l0 <= l1) {
					_suc[st] = mp(e, 0);
				} else {
					_suc[st] = mp(e, 1);
				}
			}
		}
	}
	
	return _opt[st];
}

vector<vertex> dp::build_path() {
	pair<edge, int> next = _opt_start;
	set<edge> rem(_clients);
	vector<vertex> path;

	for (int i = 0; i < _clients.size(); ++i) {
		edge e = next.first;
		int endpt = next.second;
		path.push_back(e[endpt]);
		rem.erase(e);
		next = _suc[dp_state(e[endpt], rem)];
	}

	return path;
}

bool dp::prune(vertex &cur, set<edge> &rem, int len) {
	assert(rem.size() > 0);

	int edges_count = _n * (_m - 1) + _m * (_n - 1);
	float p = rem.size() / (float) edges_count;
	if (edges_count < 80) {
		if (rem.size() >= 2 and len + bound_dist_x2(cur, rem) >= _opt_length) {
			return true;
		}
	} else {
		if (0.3 <= p and 
			(len + bound_clients_count(rem) >= _opt_length or
			len + bound_vc(rem) >= _opt_length)) {
			return true;
		} else if (p < 0.3 and 
			(len + bound_clients_count(rem) >= _opt_length or
			len + bound_mst(rem) >= _opt_length) or
			(rem.size() >= 2 and len + bound_dist_x2(cur, rem) >= _opt_length)) {
			return true;
		}
	}
	return false;
}