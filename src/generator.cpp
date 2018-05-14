#include <iostream>
#include <random>
#include <set>
#include "defines.h"

using std::cout;
using std::cin;
using std::endl;
using std::set;
using std::default_random_engine;
using std::uniform_int_distribution;

int main() {
	int seed;
	cin >> seed;
	int n, m;
	cin >> n >> m;
	int p;
	cin >> p;
	int k = (n * (m - 1) + m * (n - 1)) * (p / 100.0);
	cout << n << " " << m << " " << k << endl;

	default_random_engine engine(seed);

	uniform_int_distribution<int> xs(0, m - 1);
	uniform_int_distribution<int> ys(0, n - 1);
	uniform_int_distribution<int> unit(-1, 1);

	set<edge> clients;
	for (int i = 0; i < k; ++i) {
		edge e;
		while (true) {
			int x1 = xs(engine);
			int y1 = ys(engine);
			int dx = unit(engine);
			int dy = unit(engine);
			int x2 = x1 + dx;
			int y2 = y1 + dy;
			e = edge(vertex(x1, y1), vertex(x2, y2));
			if ((dx == 0 or dy == 0) 
				and (dx != 0 or dy != 0)
				and (x2 < m and x2 >= 0 and y2 < n and y2 >= 0)
				and clients.count(e) == 0) {
				cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
				break;
			}
		}
		clients.insert(e); 
	}

	return 0;
}