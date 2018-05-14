#include "bounds.h"
#include <cmath>
#include <queue>
#include "utils.h"
#include "mst.h"
#include "vc.h"
#include "defines.h"

using std::queue;

int bound_zero() {
	return 0;
}

int bound_dist_x2(vertex cur, set<edge> &rem) {
	int res = 0;
	for (edge e1 : rem) {
		for (edge e2 : rem) {
			res = fmax(res, fmin(dist(cur, e1), dist(cur, e2)) + dist(e1, e2));
		}
	}
	return res;
}

int bound_dist_x3(vertex cur, set<edge> &rem) {
	assert(rem.size() >= 3);

	int res = 0;
	for (edge e1 : rem) {
		for (edge e2 : rem) {
			if (e1 != e2) {
				for (edge e3 : rem) {
					if (e3 != e2 and e3 != e1) {
						res = fmax(res, 
									fmin(dist(cur, e1) + dist(e1, e2) + dist(e2, e3), 
										fmin(dist(cur, e1) + dist(e1, e3) + dist(e3, e2),
											fmin(dist(cur, e2) + dist(e2, e1) + dist(e1, e3), 
												fmin(dist(cur, e2) + dist(e2, e3) + dist(e3, e1),
													fmin(dist(cur, e3) + dist(e3, e1) + dist(e1, e2), 
														dist(cur, e3) + dist(e3, e2) + dist(e2, e1)
														)
													)
												)
											)
										)
									);
					}
				}
			}
		}
	}
	return res;
}

int bound_clients_count(set<edge> &rem) {
	assert(rem.size() > 0);

	return rem.size() / 3 - 1;
}

int bound_mst(set<edge> &rem) {
	assert(rem.size() > 0);

	int n = rem.size();
	vector<vector<int>> adj_matrix(n, vector<int>(n));
	
	int i, j;
	i = 0;
	for (edge e : rem) {
		j = 0;
		for (edge f : rem) {
			adj_matrix[i][j] = dist(e, f);
			++j;
		}
		++i;
	}

	return mst(adj_matrix);
}

void bfs_partition(vertex s, 
					umvv &adj_list,
					umvi &partition,
					umvi &component,
					int count) {
	queue<vertex> q;
	q.push(s);
	partition[s] = 0;
	int color = 0;
	while (not q.empty()) {
		vertex u = q.front();
		q.pop();
		component[u] = count;
		for (vertex v : adj_list[u]) {
			if (partition.count(v) == 0) {
				partition[v] = color;
				q.push(v);
			}
		}
		color = (color + 1) % 2;
	}
}

umvv build_adj_list(set<edge> &rem) {
	umvv adj_list;
	vector<vertex> vertices;
	for (edge e : rem) {
		adj_list[e[0]].push_back(e[1]);
		adj_list[e[1]].push_back(e[0]);
	}

	return adj_list;
}

// Construye las listas de adyacencias, las componentes conexas, y una biparticion.
void build(set<edge> &rem, umvv &adj_list, umvi &component, umvi &partition, int &ccs) {
	adj_list = build_adj_list(rem);

	ccs = 0;
	for (auto &kv : adj_list) {
		vertex u = kv.first;
		if (component.count(u) == 0) {
			bfs_partition(u, adj_list, partition, component, ccs);
			++ccs;
		}
	}
}

int bound_vc(set<edge> &rem) {
	assert(rem.size() > 0);

	umvi component;	// no se usa
	umvi partition;
	umvv adj_list;
	int ccs;	// no se usa
	build(rem, adj_list, component, partition, ccs);
	int tau = vc(adj_list, partition); 
	return tau - 1;
}

int bound_vc_mst(set<edge> &rem) {
	assert(rem.size() > 0);

	umvi component;
	umvi partition;
	umvv adj_list;
	int ccs;

	build(rem, adj_list, component, partition, ccs);
	int tau = vc(adj_list, partition);

	vector<vector<int>> ccs_adj_matrix(ccs, vector<int>(ccs, INF));
	for (auto &kv1 : adj_list) {
		vertex u = kv1.first;
		int cu = component[u];
		for (auto &kv2 : adj_list) {
			vertex v = kv2.first;
			int cv = component[v];
			ccs_adj_matrix[cu][cv] = fmin(ccs_adj_matrix[cu][cv], dist(u, v));
		}
	}

	return tau - 1 + mst(ccs_adj_matrix) - (ccs - 1);
}