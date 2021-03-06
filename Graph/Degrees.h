/*
 * Degrees.h
 *
 *  Created on: 2014年12月18日
 *      Author: therdes
 */

#ifndef DEGREES_H_
#define DEGREES_H_

#include <vector>
#include "Digraph.h"
#include "Graphm.h"

class Degrees {
private:
	int* indegreeArray;
	int* outdegreeArray;
	int numVertex;

	void init(int numVertex);

public:
	Degrees(Graph& g);
	~Degrees();

	int indegree(int v);
	int outdegree(int v);

	std::vector<int>* sources();
	std::vector<int>* sink();

	bool isMap();
};

#endif /* DEGREES_H_ */
