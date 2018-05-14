#include <iostream>
#include <set>
#include <chrono>
#include "defines.h"
#include "dp.h"
#include "backtracking.h"

using std::set;
using std::vector;
using std::cout;
using std::endl;
using std::cin;
using std::ratio;
using namespace std::chrono;

void read_input(int &n, int &m, set<edge> &clients) {
	int k;
	cin >> n >> m >> k;
	for (int i = 0; i < k; ++i) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		clients.insert(edge(vertex(x1, y1), vertex(x2, y2)));
	}
}

int main() {
	int n, m;
	set<edge> clients;
	read_input(n, m, clients);

	vector<vertex> path;
	high_resolution_clock::time_point start, end;
	duration<long int, ratio<1, 1000000000>> span;

	// cout << "backtracking with bounds" << endl;
	// backtracking solver1(n, m, clients, true);
	// start = high_resolution_clock::now();
	// path = solver1.solve();
	// end = high_resolution_clock::now();
	// span = duration_cast<nanoseconds>(end - start);
	// cout << "dist: " << length(path) << endl;
	// cout << refine(path);
	// cout << "exec time: " << span.count() << endl;

	cout << "backtracking without bounds" << endl;
	backtracking solver1(n, m, clients, false);
	start = high_resolution_clock::now();
	path = solver1.solve();
	end = high_resolution_clock::now();
	span = duration_cast<nanoseconds>(end - start);
	cout << "dist: " << length(path) << endl;
	cout << refine(path);
	cout << "exec time: " << span.count() << endl;

	// cout << "dp with bounds" << endl;
	// dp solver3(n, m, clients, true);
	// start = high_resolution_clock::now();
	// path = solver3.solve();
	// end = high_resolution_clock::now();
	// span = duration_cast<nanoseconds>(end - start);
	// cout << "dist: " << length(path) << endl;
	// cout << refine(path);
	// cout << "exec time: " << span.count() << endl;

// 	cout << "dp without bounds" << endl;
// 	dp solver3(clients, false);
// start = high_resolution_clock::now();
// 	path = solver3.solve();
// end = high_resolution_clock::now();
// 	cout << "dist: " << length(path) << endl;
// 	cout << path;
// 	cout << "exec time: " << (end - start).count() << endl;

	return 0;
}