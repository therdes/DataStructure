/*
 * EdgeWeightedGraph.h
 *
 *  Created on: 2014年12月26日
 *      Author: therdes
 */

#ifndef EDGEWEIGHTEDGRAPH_H_
#define EDGEWEIGHTEDGRAPH_H_

#include "Graph.h"
#include "WeightedEdge.h"
#include <list>

class EdgeWeightedGraph: Graph {
private:
	int numVertex;
	int numEdge;
	std::list<WeightedEdge*>** adj;

	void removeEdge_help(int v, int w);

public:
	EdgeWeightedGraph(int n, int e);
	~EdgeWeightedGraph();

	void creatGraph();

	void addEdge(int v, int w, double wt);
	void removeEdge(int v, int w);
	bool contains(int v, int w) const;

	double getEdgeWeight(int v, int w) const;

	int n() const {
		return numVertex;
	}
	int e() const {
		return numEdge;
	}

	int first(int v) const;
	int next(int v, int w) const;

	WeightedEdge* firstEdge(int v) const;
	WeightedEdge* nextEdge(int v, int w) const;

	friend std::ostream& operator<<(std::ostream& output, EdgeWeightedGraph& G);

	Graph* reverse();
};

#endif /* EDGEWEIGHTEDGRAPH_H_ */
