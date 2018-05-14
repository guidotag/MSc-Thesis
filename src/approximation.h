#ifndef __APPROXIMATION_H__
#define __APPROXIMATION_H__

#include <set>
#include <vector>
#include "defines.h"

using std::vector;
using std::set;

vector<edge> random_permutation(const set<edge> &clients);

vector<edge> snake_permutation(const set<edge> &clients);

#endif