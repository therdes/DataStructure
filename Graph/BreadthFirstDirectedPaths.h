/*
 * BreadthFirstDirectedPaths.h
 *
 *  Created on: 2014年12月17日
 *      Author: therdes
 */

#ifndef BREADTHFIRSTDIRECTEDPATHS_H_
#define BREADTHFIRSTDIRECTEDPATHS_H_

#include "Digraph.h"
#include <queue>
#include <stack>

class BreadthFirstDirectedPaths {
private:
	bool* marked;
	int* edgeTo;
	int* distanceTo;
	const int source;

	void bfs(Digraph& dg);

public:
	BreadthFirstDirectedPaths(Digraph& dg, int source);
	~BreadthFirstDirectedPaths();

	bool hasPathTo(int v);
	void pathTo(int v);
	int distTo(int v);
};

#endif /* BREADTHFIRSTDIRECTEDPATHS_H_ */
