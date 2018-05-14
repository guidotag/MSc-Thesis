#include "mst.h"
#include <vector>
#include <cmath>

#define INF 1e9

using std::vector;

int min(const vector<int> &q, const vector<bool> &visited) {
	int res = -1;
	for (int i = 0; i < q.size(); ++i) {
		if ((res == -1 or q[i] < q[res]) and (not visited[i])) {
			res = i;
		}
	}
	return res;
}

int mst(const vector<vector<int>> &adj_matrix) {
	int n = adj_matrix.size();
	vector<int> q(n, INF);
	vector<bool> visited(n, false);
	q[0] = 0;

	int mst = 0;
	for (int i = 0; i < n; ++i) {
		int u = min(q, visited);
		mst += q[u];
		visited[u] = true;
		for (int v = 0; v < n; ++v) {
			if (not visited[v]) {
				q[v] = fmin(q[v], adj_matrix[u][v]);
			}
		}
	}

	return mst;
}