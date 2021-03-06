/*
 * DirectedDFS.h
 *
 *  Created on: 2014年12月17日
 *      Author: therdes
 */

#ifndef DIRECTEDDFS_H_
#define DIRECTEDDFS_H_

#include <iostream>
#include "Digraph.h"

class DirectedDFS {
private:
	bool* marked;
	int source;
	const Digraph* dg;

	void dfs(Digraph& G, int v);
	inline bool getMark(int v);

public:
	DirectedDFS(Digraph& dg, int source);
//	DirectedDFS(Digraph& dg, int* sources, int length);
	virtual ~DirectedDFS();

	void reachable();
};

#endif /* DIRECTEDDFS_H_ */
