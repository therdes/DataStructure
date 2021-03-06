/*
 * Graphm.h
 *
 *  Created on: 2014年12月5日
 *      Author: therdes
 */

#ifndef GRAPHM_H_
#define GRAPHM_H_

#include "Graph.h"
#include <stack>
#include <string>
#include <queue>

#include <iostream>
#include <fstream>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class Graphm: public Graph {
private:
	int numVertex, numEdge;
	int **matrix;
	int *mark;

	void DFS(int vertex);
	int minVertex(int *D);

	void DFSofFindPath(int v, int* edgeTo);
	void DFSofCycle(int v, int u, int* edgeTo, std::stack<int> *& cycle);

public:
	Graphm();
	Graphm(std::string* file);
	Graphm(const Graphm& G);
	virtual ~Graphm();

	inline int n() const;
	inline int e() const;

//	void CreatGraph();
	void CreatGraph(std::string* file);
	void PrintAdjMatrix() const;

	int first(int v) const;
	int next(int v, int w) const;

	void addEdge(int v, int w, double wt = 1);
	inline int weight(int v1, int v2) const;
	inline bool contains(int v, int w) const;

	inline int getMark(int v) const;
	inline void setMark(int v, int val);

	int DFSTraverse();
	int BFSTraverse();

	int ShortestPaths(int *D, int start);

	int ShortestPathsWithHeap(int *D, int start);

	void findPaths(int v, int w);
	void Cycle(std::stack<int> *& cycle);

	Graphm& operator=(const Graphm& G);
	friend std::ostream& operator<<(std::ostream& output, const Graphm& G);

	Graphm* reverse();
};

#endif /* GRAPHM_H_ */
