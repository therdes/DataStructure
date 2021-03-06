/*
 * BreadthFirstDirectedPaths.cpp
 *
 *  Created on: 2014年12月17日
 *      Author: therdes
 */

#include "BreadthFirstDirectedPaths.h"

using namespace std;

BreadthFirstDirectedPaths::BreadthFirstDirectedPaths(Digraph& dg, int source) :
		source(source) {
	marked = new bool[dg.n()];
	edgeTo = new int[dg.n()];
	distanceTo = new int[dg.n()];
	for (int i = 0; i < dg.n(); i++) {
		marked[i] = false;
		distanceTo[i] = INT_MAX;
	}
	edgeTo[source] = source;
	distanceTo[source] = 0;

	bfs(dg);
}

BreadthFirstDirectedPaths::~BreadthFirstDirectedPaths() {
	delete[] marked;
	delete[] edgeTo;
	delete[] distanceTo;
}

void BreadthFirstDirectedPaths::bfs(Digraph& dg) {
	queue<int>* q = new queue<int>();

	q->push(source);
	marked[source] = true;
	while (!q->empty()) {
		int v = q->front();
		q->pop();
		for (int w = dg.first(v); w < dg.n(); w = dg.next(v, w)) {
			if (!marked[w]) {
				q->push(w);
				edgeTo[w] = v;
				distanceTo[w]++;
				marked[w] = true;
			}
		}
	}
	delete q;
}

bool BreadthFirstDirectedPaths::hasPathTo(int v) {
	return marked[v];
}

int BreadthFirstDirectedPaths::distTo(int v) {
	return distanceTo[v];
}

void BreadthFirstDirectedPaths::pathTo(int v) {
	if (hasPathTo(v)) {
		cout << "The path from " << source << " to " << v << " is:" << endl;
		if (source == v) {
			cout << "itself." << endl;
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
