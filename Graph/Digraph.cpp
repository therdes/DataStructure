/*
 * Digraph.cpp
 *
 *  Created on: 2014年12月17日
 *      Author: therdes
 */

#include "Digraph.h"
using namespace std;

Digraph::Digraph(string& file) {
	CreatDigraph(file);
}

Digraph::Digraph(int v, int e) {
	numVertex = v;
	numEdge = e;
	adj = (vector<int>**) new vector<int>*[n()];
	for (int i = 0; i < n(); i++)
		adj[i] = new vector<int>();
}

void Digraph::CreatDigraph(string& file) {
	ifstream in;
	in.open(file.c_str(), ios::in);

	in >> numVertex >> numEdge;

	adj = (vector<int>**) new vector<int>*[n()];
	for (int i = 0; i < n(); i++)
		adj[i] = new vector<int>();

	int vStart, vEnd;
	for (int i = 0; i < e(); i++) {
		in >> vStart >> vEnd;
		if (vStart == vEnd) {
			printf("Invalid Input (%d - %d):  ", vStart, vEnd);
			puts("Self-loops is NOT allow. This input will be ignored.");
			numEdge--;
			i--;
			continue;
		}
		addEdge(vStart, vEnd);
	}
	in.close();
}

Digraph::~Digraph() {
	for (int i = 0; i < n(); i++)
		delete adj[i];
	delete[] adj;
}

void Digraph::addEdge(int v, int w, double wt) {
	if (v > n() || w > n()) {
		printf("Invalid input (%d -> %d):  ", v, w);
		puts("the vertexes are not in the graph.");
		exit(0);
	}
	adj[v]->push_back(w);
}

int Digraph::getWeight(int v, int w) const {
	return 1;
}

bool Digraph::contains(int v, int w) const {
	vector<int>::const_iterator iter;
	for (iter = adj[v]->begin(); iter != adj[v]->end(); iter++)
		if (*iter == w)
			return true;
	return false;
}

int Digraph::first(int v) const {
	if (adj[v]->empty())
		return n();
	return adj[v]->front();
}

int Digraph::next(int v, int w) const {
	vector<int>::const_iterator iter;
	for (iter = adj[v]->begin(); iter != adj[v]->end(); iter++)
		if (*iter == w)
			break;
	if (*iter == w && ++iter != adj[v]->end())
		return *iter;
	return n();
}

ostream& operator<<(ostream& output, Digraph& G) {
	output << G.n() << " Vertexes and " << G.e() << " Edges" << endl;
	for (int v = 0; v < G.n(); v++) {
		output << v << ": ";
		for (int w = G.first(v); w < G.n(); w = G.next(v, w))
			output << w << " ";
		output << endl;
	}
	return output;
}

Digraph* Digraph::reverse() {
	Digraph* dg = new Digraph(n(), e());
	for (int v = 0; v < n(); v++)
		for (int w = first(v); w < n(); w = next(v, w))
			dg->addEdge(w, v, getWeight(v, w));
	return dg;
}
