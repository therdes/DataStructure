/*
 * DepthFirstDirectedPaths.cpp
 *
 *  Created on: 2014年12月17日
 *      Author: therdes
 */

#include "DepthFirstDirectedPaths.h"
using namespace std;

DepthFirstDirectedPaths::DepthFirstDirectedPaths(Digraph& dg, int source) :
		source(source) {
	marked = new bool[dg.n()];
	for (int i = 0; i < dg.n(); i++)
		marked[i] = false;
	edgeTo = new int[dg.n()];
	edgeTo[source] = source;

	dfs(dg, source);
}

DepthFirstDirectedPaths::~DepthFirstDirectedPaths() {
	delete[] marked;
	delete[] edgeTo;
}

void DepthFirstDirectedPaths::dfs(Digraph& dg, int v) {
	marked[v] = true;
	for (int w = dg.first(v); w < dg.n(); w = dg.next(v, w))
		if (!marked[w]) {
			edgeTo[w] = v;
			dfs(dg, w);
		}
}

bool DepthFirstDirectedPaths::hasPathTo(int v) {
	return marked[v];
}

void DepthFirstDirectedPaths::pathTo(int v) {
	if (hasPathTo(v)) {
		cout << "The path from " << source << " to " << v << " is:" << endl;
		if (source == v) {
			cout << "itself."<<endl;
			return;
		}

		stack<int>* s = new stack<int>();
		for (int x = v; x != source; x = edgeTo[x])
			s->push(x);
		s->push(source);

		cout << s->top();
		s->pop();
		while (!s->empty()) {
			cout << " - " << s->top();
			s->pop();
		}
		cout << endl;
		delete s;
	} else {
		cout << "Can't find the path." << endl;
	}
}
