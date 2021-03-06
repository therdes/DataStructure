/*
 * Graph.h
 *
 *  Created on: 2014年12月5日
 *      Author: therdes
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>

const int UNVISITED = 0;
const int VISITED = 1;

//const int INFINITY = 65536;

class Graph {
public:
	Graph() {
	}
	virtual ~Graph() {
	}

	virtual int n() const =0;
	virtual int e() const =0;

	virtual int first(int v) const =0;
	virtual int next(int v, int w) const =0;

	virtual void addEdge(int v, int w, double wt = 1) =0;
	virtual bool contains(int v, int w) const =0;

	virtual Graph* reverse() =0;
};

#endif /* GRAPH_H_ */
