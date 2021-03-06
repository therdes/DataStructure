/*
 * DirectedCycle.cpp
 *
 *  Created on: 2014年12月17日
 *      Author: therdes
 */

#include "DirectedCycle.h"

using namespace std;

DirectedCycle::DirectedCycle(Digraph& dg, int source) :
		source(source) {
	cycleBegin = dg.n();
	acyclic = true;
	marked = new bool[dg.n()];
	onStack = new bool[dg.n()];
	edgeTo = new int[dg.n()];
	for (int i = 0; i < dg.n(); i++)
		marked[i] = false;
	edgeTo[this->source] = this->source;

	dfs(dg, this->source);
}

DirectedCycle::~DirectedCycle() {
	delete[] marked;
	delete[] edgeTo;
	delete[] onStack;
}

void DirectedCycle::dfs(Digraph& dg, int v) {
	marked[v] = true;
	onStack[v] = true;
	for (int w = dg.first(v); w < dg.n(); w = dg.next(v, w)) {
		if (!acyclic)
			return;
		if (!marked[w]) {
			edgeTo[w] = v;
			dfs(dg, w);
		} else if (onStack[w]) {
			edgeTo[w] = v;
			cycleBegin = w;
			acyclic = false;
		}
	}
	onStack[v] = false;
}

bool DirectedCycle::hasCycle(bool showCycle) {
	if (showCycle) {
		if (!acyclic) {
			stack<int>* s = new stack<int>();
			s->push(cycleBegin);
			for (int x = edgeTo[cycleBegin]; x != cycleBegin; x = edgeTo[x])
				s->push(x);

			cout << "One of the cycle in Directed graph is:" << endl;
			cout << cycleBegin;
			while (!s->empty()) {
				cout << " - " << s->top();
				s->pop();
			}
			cout << endl;
			delete s;
		} else {
			cout << "No cycle in the Directed Graph." << endl;
		}
	}

	return !acyclic;
}
