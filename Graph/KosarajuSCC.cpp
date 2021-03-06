/*
 * KosarajuSCC.cpp
 *
 *  Created on: 2014年12月18日
 *      Author: therdes
 */

#include "KosarajuSCC.h"

using namespace std;

KosarajuSCC::KosarajuSCC(Digraph& dg) {
	marked = new bool[dg.n()];
	for (int i = 0; i < dg.n(); i++)
		marked[i] = false;
	id = new int[dg.n()];
	count = 0;

	Digraph* dgR = dg.reverse();
	DepthFirstOrder* dforder = new DepthFirstOrder(*dgR);
	stack<int>& reverseOrder = dforder->reversePostOrder();
	delete dgR;

	while (!reverseOrder.empty()) {
		int v = reverseOrder.top();
		reverseOrder.pop();
		if (!marked[v]) {
			dfs(dg, v);
			count++;
		}
	}
	delete dforder;
}

KosarajuSCC::~KosarajuSCC() {
	delete[] marked;
	delete[] id;
}

void KosarajuSCC::dfs(Digraph& dg, int v) {
	marked[v] = true;
	id[v] = count;

	for (int w = dg.first(v); w < dg.n(); w = dg.next(v, w)) {
		if (!marked[w])
			dfs(dg, w);
	}
}

bool KosarajuSCC::stronglyConnected(int v, int w) const {
	return id[v] == id[w];
}

int KosarajuSCC::sccID(int v) {
	return id[v];
}

int KosarajuSCC::sccCount() {
	return count;
}
