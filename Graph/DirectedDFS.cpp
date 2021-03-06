/*
 * DirectedDFS.cpp
 *
 *  Created on: 2014年12月17日
 *      Author: therdes
 */

#include "DirectedDFS.h"

DirectedDFS::DirectedDFS(Digraph& dg, int source) {
	marked = new bool[dg.n()];
	for (int i = 0; i < dg.n(); i++)
		marked[i] = false;

	this->source = source;
	this->dg = &dg;
	dfs(dg, source);
}
/*
 * ToDo
 */
/*DirectedDFS::DirectedDFS(Digraph& dg, int* sources, int length)
 {
 marked = new bool[dg.n()];
 for(int i = 0; i < dg.n(); i++)
 marked[i] = false;
 }*/

DirectedDFS::~DirectedDFS() {
	delete[] marked;
}

void DirectedDFS::dfs(Digraph& dg, int v) {
	marked[v] = true;
	for (int w = dg.first(v); w < dg.n(); w = dg.next(v, w))
		if (!getMark(w))
			dfs(dg, w);
}

bool DirectedDFS::getMark(int v) {
	return marked[v];
}

void DirectedDFS::reachable() {
	std::cout << source << " can reach to ";
	for (int i = 0; i < dg->n(); i++)
		if (getMark(i))
			std::cout << i << " ";
	std::cout << std::endl;
}
