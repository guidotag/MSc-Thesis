#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <iostream>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <boost/functional/hash.hpp>

using std::ostream;
using std::endl;
using std::pair;
using std::make_pair;
using std::vector;
using std::unordered_map;
using std::size_t;

#define mp(x, y) make_pair(x, y)

#define INF 1e9

struct vertex {
	vertex() {}
	vertex(int a, int b) : x(a), y(b) {}

	void operator=(const vertex &other) {
		x = other.x;
		y = other.y;
	}

    bool operator==(const vertex &other) const {
    	return x == other.x and y == other.y;
    }

    bool operator!=(const vertex &other) const {
    	return not (*this == other);
    }

    bool operator<(const vertex &other) const {
    	return x < other.x or (x == other.x and y < other.y);
    }

	int x;
	int y;
};

struct vertex_hasher {
	size_t operator()(const vertex &u) const {
		size_t seed = 0;
        boost::hash_combine(seed, u.x);
        boost::hash_combine(seed, u.y);
        return seed;
	}
};

struct edge {
public:
	edge() {}
	edge(vertex u, vertex v) : first(u), second(v) {}

	vertex operator[](int i) const {
		assert(i == 0 or i == 1);
		if (i == 0) return first;
		return second;
	}

	void operator=(const edge &other) {
		first = other.first;
		second = other.second;
	}

	bool operator<(const edge &other) const {
		return (first < other.first) or (first == other.first and second < other.second);
	}

	bool operator!=(const edge &other) const {
		return first != other.first or second != other.second;
	}

	vertex first;
	vertex second;
};

typedef unordered_map<vertex, int, vertex_hasher> umvi;
typedef unordered_map<vertex, vector<vertex>, vertex_hasher> umvv;

inline ostream &operator<<(ostream &out, const vertex &u) {
	out << "(" << u.x << "," << u.y << ")";
	return out;
}

inline ostream &operator<<(ostream &out, const vector<vertex> &path) {
	for (vertex u : path) {
		out << u << endl;
	}
	return out;
}

#endif