#ifndef __UTILS_H__
#define __UTILS_H__

#include <vector>
#include "defines.h"

using std::vector;

int dist(vertex u, vertex v);

int dist(vertex u, edge e);

int dist(edge e, edge f);

vertex dist_endpt(vertex u, edge e);

int length(vector<vertex> &path);

vector<vertex> refine(vector<vertex> &path);

bool covers(vertex u, edge e);

#endif