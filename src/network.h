#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <vector>
#include <queue>
#include <cassert>

#define INF 1e9
#define NIL -1

using namespace std;

typedef vector<vector<int> > flow;	// matrix defining the flow for each (u, v) pair (not necessarily an edge)
typedef vector<int> path;

class network {
private:
	vector<vector<int> > adj_list;
	vector<vector<int> > adj_matrix;
	vector<vector<int> > cap;		// capacities matrix
	int s, t;
	int n;

	void build_path(vector<int> &pred, int current, int first, path &p) {
		if (current == first) {
			p.push_back(current);
			return;
		}
		build_path(pred, pred[current], first, p);
		p.push_back(current);
	}

	path augmenting_path(flow &f) {
		vector<bool> discovered(n, false);
		vector<int> pred(n, NIL);
		queue<int> q;
		q.push(s);
		discovered[s] = true;

		while(not q.empty()) {
			int u = q.front();
			q.pop();
			for (int v : adj_list[u]) {
				if (f[u][v] < cap[u][v] && not discovered[v]) {
					discovered[v] = true;
					pred[v] = u;
					q.push(v);
				}
			}
		}

		path p;
		if (not discovered[t]) {
			return p;
		}

		build_path(pred, t, s, p);

		return p;
	}

	int slack(path &p, flow &f) {
		int delta = INF;
		for (int i = 1; i < (int)p.size(); ++i) {
			int u = p[i - 1], v = p[i];
			delta = min(delta, cap[u][v] - f[u][v]);
		}
		return delta;
	}

	int value(flow &f) {
		int val = 0;
		for (int u = 0; u < n; ++u) {
			if (f[s][u] > 0) {
				val += f[s][u];
			} else {
				val -= f[u][s];
			}
		}
		return val;
	}

public:
	int max_flow() {
		path p;
		flow f(n, vector<int>(n, 0));

		while (true) {
			p = augmenting_path(f);
			if (p.empty()) {
				break;
			}
			int delta = slack(p, f);
			for (int i = 1; i < (int)p.size(); ++i) {
				int u = p[i - 1], v = p[i];
				f[u][v] += delta;
				f[v][u] -= delta;
			}
		}

		return value(f);
	}

	void add_edge(int u, int v, int c) {
		assert(0 <= u and u < n);
		assert(0 <= v and v < n);
		assert(0 <= c);

		if (adj_matrix[u][v] == 0) {
			adj_list[u].push_back(v);
			adj_list[v].push_back(u);
		}

		adj_matrix[u][v] = adj_matrix[v][u] = 1;
		cap[u][v] = c;
	}

	network(int size, int source, int sink) 
		: n(size), s(source), t(sink), adj_list(size), adj_matrix(size, vector<int>(size, 0)), cap(size, vector<int>(size, 0)) {
		assert(0 <= s and s < n);
		assert(0 <= t and t < n);
	}
};
#endif
