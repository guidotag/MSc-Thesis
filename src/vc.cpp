#include "vc.h"
#include "network.h"

using std::pair;

umvi generate_ids(umvv &adj_list) {
	umvi ids;
	int id = 0;
	for (auto &kv : adj_list) {
		vertex u = kv.first;
		ids[u] = id;
		++id;
	}
	return ids;
}

int vc(umvv &adj_list, umvi &partition) {
	umvi ids = generate_ids(adj_list);
	int n = ids.size();
	int source = n;
	int sink = n + 1;
	network net(n + 2, source, sink);
	for (auto &kv : partition) {
		vertex u = kv.first;
		int p = kv.second;
		if (p == 0) {
			for (vertex v : adj_list[u]) {
				net.add_edge(ids[u], ids[v], 1);
			}
		}
	}

	for (auto &kv : partition) {
		vertex u = kv.first;
		int p = kv.second;
		if (p == 0) {
			net.add_edge(source, ids[u], 1);
		} else {
			net.add_edge(ids[u], sink, 1);
		}
	}

	return net.max_flow();
}