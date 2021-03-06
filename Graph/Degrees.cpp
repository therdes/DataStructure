/*
 * Degrees.cpp
 *
 *  Created on: 2014年12月18日
 *      Author: therdes
 */

#include "Degrees.h"

using namespace std;

void Degrees::init(int numVertex) {
	this->numVertex = numVertex;
	indegreeArray = new int[numVertex];
	outdegreeArray = new int[numVertex];
	for (int i = 0; i < numVertex; i++)
		indegreeArray[i] = outdegreeArray[i] = 0;
}

Degrees::Degrees(Graph& g) {
	init(g.n());
	Graph* gr = g.reverse();

	for (int v = 0; v < g.n(); v++)
		for (int w = g.first(v); w < g.n(); w = g.next(v, w))
			indegreeArray[w]++;
	for (int v = 0; v < gr->n(); v++)
		for (int w = gr->first(v); w < gr->n(); w = gr->next(v, w))
			outdegreeArray[w]++;
}

Degrees::~Degrees() {
	delete[] indegreeArray;
	delete[] outdegreeArray;
}

int Degrees::indegree(int v) {
	return indegreeArray[v];
}

int Degrees::outdegree(int v) {
	return outdegreeArray[v];
}

vector<int>* Degrees::sink() {
	vector<int>* temp = new vector<int>();
	for (int v = 0; v < numVertex; v++)
		if (outdegree(v) == 0)
			temp->push_back(v);
	return temp;
}

vector<int>* Degrees::sources() {
	vector<int>* temp = new vector<int>();
	for (int v = 0; v < numVertex; v++)
		if (outdegree(v) == 0)
			temp->push_back(v);
	return temp;
}

bool Degrees::isMap() {
	int v;
	for (v = 0; v < numVertex; v++)
		if (outdegree(v) != 1)
			break;

	return v == numVertex;
}
