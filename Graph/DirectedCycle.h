/*
 * DirectedCycle.h
 *
 *  Created on: 2014年12月17日
 *      Author: therdes
 */

#ifndef DIRECTEDCYCLE_H_
#define DIRECTEDCYCLE_H_

#include <stack>
#include "Digraph.h"

class DirectedCycle {
private:
	bool* marked;
	bool* onStack;
	int* edgeTo;
	const int source;
	bool acyclic;
	int cycleBegin;

	void dfs(Digraph& dg, int v);

public:
	DirectedCycle(Digraph& dg, int source = 0);
	~DirectedCycle();

	bool hasCycle(bool showCycle = false);
};

#endif /* DIRECTEDCYCLE_H_ */
