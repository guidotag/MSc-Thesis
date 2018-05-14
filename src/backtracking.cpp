#include "backtracking.h"
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
using std::reverse;

backtracking::backtracking(int n, int m, set<edge> &clients, bool bounds) : 
		_n(n), _m(m), _clients(clients), _opt_length(INF), _bounds(bounds) {}

vector<vertex> backtracking::solve() {
	// approximate();
	vector<edge> permut;
	set<edge> rem(_clients);
	for (edge e : _clients) {
		rem.erase(e);
		permut.push_back(e);
		sr(permut, rem, 0, 0);
		rem.insert(e);
		permut.pop_back();
	}
	return build_path();
}

void backtracking::sr(vector<edge> &permut, set<edge> &rem, int l0, int l1) {
	if (rem.size() == 0) {
		if (fmin(l0, l1) < _opt_length) {
			_opt_length = fmin(l0, l1);
			_opt_permut = permut;
		}
		return;
	}

	edge e = permut.back();

	if (_bounds and prune(e[0], rem, l0) and prune(e[1], rem, l1)) {
		return;
	}

	for (edge f : _clients) {
		if (rem.count(f) > 0) {
			int ll0 = fmin(l0 + dist(e[0], f[0]), l1 + dist(e[1], f[0]));
			int ll1 = fmin(l0 + dist(e[0], f[1]), l1 + dist(e[1], f[1]));
			permut.push_back(f);
			rem.erase(f);
			sr(permut, rem, ll0, ll1);
			permut.pop_back();
			rem.insert(f);
		}
	}
}

vector<vertex> backtracking::build_path() {
	int k = _clients.size();
	vector<vector<int>> pred(2, vector<int>(k));
	int l0 = 0;
	int l1 = 0;
	for (int i = 1; i < k; ++i) {
		edge e = _opt_permut[i - 1];
		edge f = _opt_permut[i];
		int ll0 = fmin(l0 + dist(e[0], f[0]), l1 + dist(e[1], f[0]));
		int ll1 = fmin(l0 + dist(e[0], f[1]), l1 + dist(e[1], f[1]));
		for (int j = 0; j < 2; ++j) {
			if (l0 + dist(e[0], f[j]) <= l1 + dist(e[1], f[j])) {
				pred[j][i] = 0;
			} else {
				pred[j][i] = 1;
			}
		}
		l0 = ll0;
		l1 = ll1;
	}

	int endpt;
	if (l0 <= l1) {
		endpt = 0;
	} else {
		endpt = 1;
	}

	vector<vertex> path;
	for (int i = k - 1; i >= 0; --i) {
		edge e = _opt_permut[i];
		path.push_back(e[endpt]);
		endpt = pred[endpt][i];
	}
	reverse(path.begin(), path.end());

	return path;
}

int backtracking::minimum_length(const vector<edge> &permut) {
	int l0 = 0;
	int l1 = 0;
	for (int i = 1; i < permut.size(); ++i) {
		edge e = permut[i - 1];
		edge f = permut[i];
		int ll0 = fmin(l0 + dist(e[0], f[0]), l1 + dist(e[1], f[0]));
		int ll1 = fmin(l0 + dist(e[0], f[1]), l1 + dist(e[1], f[1]));
		l0 = ll0;
		l1 = ll1;
	}
	return fmin(l0, l1);
}

bool backtracking::prune(vertex cur, set<edge> &rem, int len) {
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

void backtracking::approximate() {
	vector<edge> permut1 = random_permutation(_clients);
	int length1 = minimum_length(permut1);
	vector<edge> permut2 = snake_permutation(_clients);
	int length2 = minimum_length(permut2);
	if (length1 < length2) {
		_opt_permut = permut1;
		_opt_length = length1;
	} else {
		_opt_permut = permut2;
		_opt_length = length2;
	}
}