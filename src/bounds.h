#ifndef __BOUNDS_H__
#define __BOUNDS_H__

#include <set>
#include "defines.h"

using std::set;

int bound_zero();

int bound_dist_x2(vertex cur, set<edge> &rem);

int bound_dist_x3(vertex cur, set<edge> &rem);

int bound_clients_count(set<edge> &rem);

int bound_mst(set<edge> &rem);

int bound_vc(set<edge> &rem);

int bound_vc_mst(set<edge> &rem);

#endif