/*
 * Digraph.h
 *
 *  Created on: 2014年12月17日
 *      Author: therdes
 */

#ifndef DIGRAPH_H_
#define DIGRAPH_H_

#include "Graph.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>

class Digraph: public Graph {
private:
	int numVertex;
	int numEdge;
	std::vector<int>** adj;

public:
	Digraph(std::string& file);
	Digraph(int v, int e);
	virtual ~Digraph();

	void CreatDigraph(std::string& file);

	int n() const {
		return numVertex;
	}
	int e() const {
		return numEdge;
	}

	void addEdge(int v, int w, double wt = 1);
	inline int getWeight(int v, int w) const;
	bool contains(int v, int w) const;

	int first(int v) const;
	int next(int v, int w) const;

	friend std::ostream& operator<<(std::ostream& output, Digraph& G);

	Digraph* reverse();
};

#endif /* DIGRAPH_H_ */
