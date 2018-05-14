#include "backtracking.h"
#include "dp.h"
#include "defines.h"
#include <iostream>
#include <getopt.h>
#include <chrono>
#include <set>

#define timeit(start_var, end_var, function_call) 		\
				start = high_resolution_clock::now();	\
				function_call;							\
				end = high_resolution_clock::now();

using std::cout;
using std::endl;
using std::cin;
using std::cerr;
using std::string;
using std::ratio;
using std::set;
using namespace std::chrono;

void read_input(set<edge> &clients, int &n, int &m) {
	int k;
	cin >> n >> m >> k;
	for (int i = 0; i < k; ++i) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		clients.insert(edge(vertex(x1, y1), vertex(x2, y2)));
	}
}

void print(high_resolution_clock::time_point &start, high_resolution_clock::time_point &end, bool human, string name) {
	duration<long int, ratio<1, 1000000>> span = duration_cast<microseconds>(end - start);
	double exec_time = span.count() / 1000000.0;	// seconds

	if (human) {
		cout << name << ": " << exec_time << endl;
	} else {
		cout << exec_time;
	}
}

int main(int argc, char *argv[]) {
	set<edge> clients;
	int n, m;
	read_input(clients, n, m);

	set<string> args;

	const char *optstring = "ha";
	struct option options[] {
		{"bt_wb", no_argument, 0, 0},
		{"bt_wob", no_argument, 0, 0},
		{"dp_wb", no_argument, 0, 0},
		{"dp_wob", no_argument, 0, 0},
		{0, 0, 0, 0}
	};
	bool human = false;

	while (true) {
		int index = 0;
		int c = getopt_long(argc, argv, optstring, options, &index);
		if (c == -1) {
			break;
		}
		switch(c) {
			case 0:
				args.insert(string(options[index].name));
				break;
			case 'h':
				human = true;
				break;
			case 'a':
				args.insert("bt_wb");
				args.insert("bt_wob");
				args.insert("dp_wb");
				args.insert("dp_wob");	
				break;
			default:
				cerr << "Invalid arguments!" << endl;
				exit(1);
		}
	}

	if (human) {
		cout << "solver: time(secs)" << endl;
	}

	for (const string &f : args) {
		high_resolution_clock::time_point start, end;

		if (f == "bt_wob") {
			backtracking solver(n, m, clients, false);
			timeit(start, end, solver.solve());
		} else if (f == "bt_wb") {
			backtracking solver(n, m, clients, true);
			timeit(start, end, solver.solve());
		} else if (f == "dp_wob") {
			dp solver(n, m, clients, false);
			timeit(start, end, solver.solve());
		} else if (f == "dp_wb") {
			dp solver(n, m, clients, true);
			timeit(start, end, solver.solve());
		}

		print(start, end, human, f);
	}

	return 0;
}