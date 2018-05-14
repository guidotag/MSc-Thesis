#include "utils.h"
#include <cmath>

using std::vector;

int dist(vertex u, vertex v) {
	return abs(u.x - v.x) + abs(u.y - v.y);
}
 
int dist(vertex u, edge e) {
	return fmin(dist(u, e.first), dist(u, e.second));
}

int dist(edge e, edge f) {
	return fmin(dist(e.first, f.first), 
		fmin(dist(e.first, f.second),
		fmin(dist(e.second, f.first), dist(e.second, f.second))));
}

vertex dist_endpt(vertex u, edge e) {
	int d = dist(u, e);
	if (d == dist(u, e.first)) {
		return e.first;
	}
	return e.second;
}

int length(vector<vertex> &path) {
	int res = 0;
	for (int i = 1; i < path.size(); ++i) {
		res += dist(path[i - 1], path[i]);
	}
	return res;
}

vector<vertex> refine(vector<vertex> &path) {
	vector<vertex> refined;
	refined.push_back(path[0]);
	for (int i = 1; i < path.size(); ++i) {
		if (path[i] != path[i - 1]) {
			refined.push_back(path[i]);
		}
	}
	return refined;
}

bool covers(vertex u, edge e) {
	if (e.first == u or e.second == u) {
		return true;
	}
	return false;
}