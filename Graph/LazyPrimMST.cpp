/*
 * LazyPrimMST.cpp
 *
 *  Created on: 2014年12月30日
 *      Author: therdes
 */

#include "LazyPrimMST.h"
using namespace std;

LazyPrimMST::LazyPrimMST(EdgeWeightedGraph& G) {
	marked = new bool[G.n()];
	for (int i = 0; i < G.n(); i++)
		marked[i] = false;
	mst = new queue<WeightedEdge*>();
	pq = new MinPQ();

	visit(G, 0);
	while (!pq->empty()) {
		WeightedEdge* edge = pq->top();
		pq->pop();

		int v = edge->either();
		int w = edge->other(v);
		if (marked[v] && marked[w])
			continue;
		mst->push(edge);
		if (!marked[v])
			visit(G, v);
		if (!marked[w])
			visit(G, w);
	}
}

LazyPrimMST::~LazyPrimMST() {
	delete[] marked;
	delete mst;
	delete pq;
}

void LazyPrimMST::visit(EdgeWeightedGraph& G, int v) {
	marked[v] = true;
	WeightedEdge* edge = G.firstEdge(v);
	while (edge != NULL) {
		if (!marked[edge->other(v)])
			pq->push(edge);
		edge = G.nextEdge(v, edge->other(v));
	}
}

const queue<WeightedEdge*>& LazyPrimMST::edges() const {
	return *mst;
}
