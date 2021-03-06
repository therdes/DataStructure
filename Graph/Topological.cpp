/*
 * Topological.cpp
 *
 *  Created on: 2014年12月18日
 *      Author: therdes
 */

#include "Topological.h"

using namespace std;

Topological::Topological(Digraph& dg) {
	order = new vector<int>();
	marked = new bool[dg.n()];
	for (int i = 0; i < dg.n(); i++)
		marked[i] = false;

	DirectedCycle* dcycle = new DirectedCycle(dg);
	if (!dcycle->hasCycle()) {
		queue<int>* q = new queue<int>();

		Degrees* dgdgree = new Degrees(dg);
		int* indegree = new int[dg.n()];
		for (int i = 0; i < dg.n(); i++)
			indegree[i] = dgdgree->indegree(i);
		delete dgdgree;

		for (int v = 0; v < dg.n(); v++)
			if (indegree[v] == 0 && !marked[v]) {
				q->push(v);
				marked[v] = true;
			}
		while (!q->empty()) {
			int v = q->front();
			q->pop();

			order->push_back(v);

			for (int w = dg.first(v); w < dg.n(); w = dg.next(v, w)) {
				indegree[w]--;
			}
			for (int w = 0; w < dg.n(); w++)
				if (indegree[w] == 0 && !marked[w]) {
					q->push(w);
					marked[w] = true;
				}
		}
	}
}

Topological::~Topological() {
	delete order;
	delete marked;
}

vector<int>* Topological::topoOrder() {
	vector<int>* temp = new vector<int>(*(this->order));
	return temp;
}
