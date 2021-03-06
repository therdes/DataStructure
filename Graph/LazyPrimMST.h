/*
 * LazyPrimMST.h
 *
 *  Created on: 2014年12月30日
 *      Author: therdes
 */

#ifndef LAZYPRIMMST_H_
#define LAZYPRIMMST_H_

#include "WeightedEdge.h"
#include "EdgeWeightedGraph.h"
#include <queue>
#include <algorithm>
using namespace std;

class LazyPrimMST {
private:
	bool* marked;
	queue<WeightedEdge*>* mst;
	typedef priority_queue<WeightedEdge*, vector<WeightedEdge*>,
			WeightedEdgeCompare> MinPQ;
	MinPQ* pq;

	void visit(EdgeWeightedGraph& G, int v);

public:
	LazyPrimMST(EdgeWeightedGraph& G);
	~LazyPrimMST();

	const queue<WeightedEdge*>& edges() const;
	double weight() const;
};

#endif /* LAZYPRIMMST_H_ */
