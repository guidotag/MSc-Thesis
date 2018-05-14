#include "bounds.h"
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

void print(int value, high_resolution_clock::time_point &start, high_resolution_clock::time_point &end, bool human, string name) {
	duration<long int, ratio<1, 1000000000>> span = duration_cast<nanoseconds>(end - start);
	double exec_time = span.count() / 1000000.0;	// millisecs

	if (human) {
		cout << name << ": " << value << " - " << exec_time << endl;
	} else {
		cout << value << " " << exec_time;
	}
}

int main(int argc, char *argv[]) {
	set<edge> clients;
	int n, m;
	read_input(clients, n, m);
	vertex start_point = vertex(m / 2, n / 2);

	set<string> args;

	const char *optstring = "ha";
	struct option options[] {
		{"clients_count", no_argument, 0, 0},
		{"dist_x2", no_argument, 0, 0},
		{"dist_x3", no_argument, 0, 0},
		{"mst", no_argument, 0, 0},
		{"vc", no_argument, 0, 0},
		{"vc_mst", no_argument, 0, 0},
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
				args.insert("dist_x2");
				args.insert("dist_x3");
				args.insert("clients_count");
				args.insert("mst");
				args.insert("vc");
				args.insert("vc_mst");	
				break;
			default:
				cerr << "Invalid arguments!" << endl;
				exit(1);
		}
	}

	if (human) {
		cout << "bound: value - time(millisecs)" << endl;
	}

	for (const string &f : args) {
		int value;
		high_resolution_clock::time_point start, end;

		if (f == "dist_x2") {
			timeit(start, end, value = bound_dist_x2(start_point, clients));
		} else if (f == "dist_x3") {
			timeit(start, end, value = bound_dist_x3(start_point, clients));
		} else if (f == "clients_count") {
			timeit(start, end, value = bound_clients_count(clients));
		} else if (f == "mst") {
			timeit(start, end, value = bound_mst(clients));
		} else if (f == "vc") {
			timeit(start, end, value = bound_vc(clients));
		} else if (f == "vc_mst") {
			timeit(start, end, value = bound_vc_mst(clients));
		}

		print(value, start, end, human, f);
	}

	return 0;
}