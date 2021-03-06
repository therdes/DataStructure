/*
 * DepthFirstDirectedPaths.h
 *
 *  Created on: 2014年12月17日
 *      Author: therdes
 */

#ifndef DEPTHFIRSTDIRECTEDPATHS_H_
#define DEPTHFIRSTDIRECTEDPATHS_H_

#include "Digraph.h"
#include <stack>

class DepthFirstDirectedPaths {
private:
	bool* marked;
	int* edgeTo;
	const int source;

	void dfs(Digraph& dg, int v);

public:
	DepthFirstDirectedPaths(Digraph& dg, int source);
	~DepthFirstDirectedPaths();

	bool hasPathTo(int v);
	void pathTo(int v);
};

#endif /* DEPTHFIRSTDIRECTEDPATHS_H_ */
