#include "approximation.h"
#include "defines.h"
#include "utils.h"
#include <random>
#include <vector>
#include <set>
#include <cmath>

#define INF 1e9

using std::set;
using std::vector;
using std::default_random_engine;
using std::uniform_int_distribution;

void swap(edge &e, edge &f) {
	edge g = e;
	e = f;
	f = g;
}

void shuffle(vector<edge> &permut) {
	default_random_engine engine(1234567);

	int n = permut.size();
	for (int i = 0; i < n; ++i) {
		uniform_int_distribution<int> index(i, n - 1);
		int j = index(engine);
		swap(permut[i], permut[j]);
	}
}

vector<edge> random_permutation(const set<edge> &clients) {
	vector<edge> permut;
	for (const edge &e : clients) {
		permut.push_back(e);
	}
	shuffle(permut);
	return permut;
}

vector<edge> snake_permutation(const set<edge> &clients) {
	int min_x, min_y, max_x, max_y;
	min_x = INF;
	max_x = -INF;
	min_y = INF;
	max_y = -INF;
	for (const edge &e : clients) {
		for (int i = 0; i < 2; ++i) {
			min_x = fmin(min_x, e[i].x);
			max_x = fmax(max_x, e[i].x);
			min_y = fmin(min_y, e[i].y);
			max_y = fmax(max_y, e[i].y);
		}
	}

	vector<vertex> path;
	for (int y = min_y; y <= max_y; ++y) {
		if (y % 2 == min_y % 2) {
			for (int x = min_x; x <= max_x; ++x) {
				path.push_back(vertex(x, y));
			}
		} else {
			for (int x = max_x; x >= min_x; --x) {
				path.push_back(vertex(x, y));
			}
		}
	}

	set<edge> rem(clients);
	vector<edge> permut;
	for (vertex &u : path) {
		for (const edge &e : clients) {
			if (rem.count(e) > 0 and covers(u, e)) {
				rem.erase(e);
				permut.push_back(e);
			}
		}
	}

	return permut;
}