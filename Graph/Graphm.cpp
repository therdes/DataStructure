/*
 * Graphm.cpp
 *
 *  Created on: 2014年12月5日
 *      Author: therdes
 */

#include "Graphm.h"

using namespace std;

Graphm::Graphm() {
	numVertex = 0;
	numEdge = 0;
	matrix = NULL;
	mark = NULL;
}

Graphm::Graphm(string* file) {
	CreatGraph(file);
}

Graphm::Graphm(const Graphm& G) {
	cout << "Using copy constructor." << endl;
	this->numVertex = G.n();
	this->numEdge = G.e();

	this->mark = new int[this->n()];
	this->matrix = (int**) new int*[this->n()];
	for (int i = 0; i < this->n(); i++)
		this->matrix[i] = new int[this->n()];

	for (int i = 0; i < this->n(); i++)
		for (int j = 0; j < this->n(); j++)
			this->addEdge(i, j, G.weight(i, j));
}

Graphm::~Graphm() {
	delete[] mark;
	for (int i = 0; i < numVertex; i++)
		delete[] matrix[i];
	delete[] matrix;
}

Graphm& Graphm::operator =(const Graphm& G) {
	cout << "Using overload assign operator." << endl;
	this->numVertex = G.n();
	this->numEdge = G.e();

	this->mark = new int[this->n()];
	this->matrix = (int**) new int*[this->n()];
	for (int i = 0; i < this->n(); i++)
		this->matrix[i] = new int[this->n()];

	for (int v = 0; v < this->n(); v++)
		for (int w = 0; w < this->n(); w++)
			this->addEdge(v, w, G.weight(v, w));
	return *this;
}

ostream& operator <<(ostream& output, const Graphm& G) {
	output << G.n() << " Vertexes and " << G.e() << " Edges." << endl;
	for (int v = 0; v < G.n(); v++) {
		output << v << ": ";
		for (int w = G.first(v); w < G.n(); w = G.next(v, w))
			output << w << " ";
		output << endl;
	}
	return output;
}

void Graphm::CreatGraph(string* file) {
	ifstream in;
	in.open(file->c_str(), ios::in);
	in >> numVertex >> numEdge;

	mark = new int[n()];
	matrix = (int**) new int*[n()];
	for (int i = 0; i < n(); i++)
		matrix[i] = new int[n()];
	for (int i = 0; i < n(); i++)
		for (int j = 0; j < n(); j++)
			addEdge(i, j, 0);

	int vStart, vEnd, wt = 1;
	for (int i = 0; i < e(); i++) {
		in >> vStart >> vEnd;
		if (vStart == vEnd) {
			printf("Invalid Input (%d - %d):  ", vStart, vEnd);
			puts("Self-loops is NOT allow. This input will be ignored.");
			numEdge--;
			i--;
			continue;
		}
		addEdge(vStart, vEnd, wt);
//		addEdge(vEnd, vStart, wt);
	}
	in.close();
}

void Graphm::PrintAdjMatrix() const {
	int i, j;

	printf("%2c", ' ');
	for (i = 0; i < n(); i++)
		printf("%6d ", i);
	printf("\n");

	for (i = 0; i < n(); i++) {
		printf("%2d", i);
		for (j = 0; j < n(); j++) {
			if (weight(i, j) == 0)
				printf("%6c ", '_');
			else
				printf("%6d ", weight(i, j));
		}
		printf("\n");
	}
}

int Graphm::n() const {
	return numVertex;
}

int Graphm::e() const {
	return numEdge;
}

int Graphm::first(int v) const {
	for (int i = 0; i < n(); i++)
		if (weight(v, i) != 0)
			return i;
	return n();
}

int Graphm::next(int v, int w) const {
	for (int i = w + 1; i < n(); i++)
		if (weight(v, i) != 0)
			return i;
	return n();
}

void Graphm::addEdge(int v1, int v2, double wt) {
	matrix[v1][v2] = wt;
}

inline int Graphm::weight(int v1, int v2) const {
	return matrix[v1][v2];
}

inline bool Graphm::contains(int v, int w) const {
	return weight(v, w) != 0;
}

inline int Graphm::getMark(int v) const {
	return mark[v];
}

inline void Graphm::setMark(int v, int val) {
	mark[v] = val;
}

int Graphm::DFSTraverse() {
	cout << "Start DFS Traverse." << endl;
	for (int i = 0; i < n(); i++)
		setMark(i, UNVISITED);
	for (int i = 0; i < n(); i++)
		if (getMark(i) == UNVISITED)
			DFS(i);
	return 0;
}

void Graphm::DFS(int vertex) {
	setMark(vertex, VISITED);
	for (int i = 0; i < n(); i++) {
		if ((weight(vertex, i) != 0) && (getMark(i) == UNVISITED)) {
			printf("%d to %d\n", vertex, i);
			DFS(i);
		}
	}
}

int Graphm::BFSTraverse() {
	cout << "Start BFS Traverse." << endl;

	queue<int>* q = new queue<int>();

	for (int i = 0; i < n(); i++)
		setMark(i, UNVISITED);

	q->push(0);
	setMark(0, VISITED);
	cout << "Start at 0." << endl;
	for (int i = 1; i < n(); i++) {
		int v = q->front();
		q->pop();
		for (int i = 0; i < n(); i++) {
			if ((weight(v, i) != 0) && (getMark(i) == UNVISITED)) {
				q->push(i);
				setMark(i, VISITED);
				cout << "To " << i << endl;
			}
		}
	}
	delete q;

	return 0;
}

int Graphm::ShortestPaths(int *D, int start) {
	for (int i = 0; i < n(); i++)
		D[i] = INT_MAX;
	D[start] = 0;
	for (int i = 0; i < n(); i++)
		setMark(i, UNVISITED);

	int v;
	for (int i = 0; i < n(); i++) {
		v = minVertex(D);
		if (D[v] == INT_MAX)
			return 1;
		setMark(v, VISITED);
		for (int w = first(v); w < n(); w = next(v, w))
			if (D[w] > D[v] + weight(v, w))
				D[w] = D[v] + weight(v, w);
	}
	return 0;
}

int Graphm::minVertex(int *D) {
	int v = -1, i;
	for (i = 0; i < n(); i++)
		if (getMark(i) == UNVISITED) {
			v = i;
			break;
		}
	for (i++; i < n(); i++)
		if ((getMark(i) == UNVISITED) && (D[i] < D[v]))
			v = i;

	return v;
}

int Graphm::ShortestPathsWithHeap(int *D, int start) {

	return 0;
}

void Graphm::findPaths(int v, int w) {
	for (int i = 0; i < n(); i++)
		setMark(i, UNVISITED);
	int* edgeTo = new int[n()];

	DFSofFindPath(v, edgeTo);
	stack<int>* s = new stack<int>();
	for (int x = w; x != v; x = edgeTo[x])
		s->push(x);
	s->push(v);
	while (!s->empty()) {
		printf("%d - ", s->top());
		s->pop();
	}
	putchar('\n');

	delete[] edgeTo;
}

void Graphm::DFSofFindPath(int v, int* edgeTo) {
	setMark(v, VISITED);
	for (int w = first(v); w < n(); w = next(v, w)) {
		if (getMark(w) == UNVISITED) {
			edgeTo[w] = v;
			DFSofFindPath(w, edgeTo);
		}
	}
}

void Graphm::Cycle(stack<int> *& cycle) {
	int* edgeTo = new int[n()];
	edgeTo[0] = 0;
	for (int i = 0; i < n(); i++)
		setMark(i, UNVISITED);

	for (int s = 0; s < n(); s++)
		if (getMark(s) == UNVISITED)
			DFSofCycle(s, s, edgeTo, cycle);
	delete[] edgeTo;
}

void Graphm::DFSofCycle(int v, int u, int* edgeTo, stack<int> *& cycle) {
	setMark(v, VISITED);
	for (int w = first(v); w < n(); w = next(v, w)) {
		if (cycle != NULL)
			return;
		if (getMark(w) == UNVISITED) {
			edgeTo[w] = v;
			DFSofCycle(w, v, edgeTo, cycle);
		} else if (w != u) {
			cycle = new stack<int>();
			for (int x = v; x != w; x = edgeTo[x])
				cycle->push(x);
			cycle->push(w);
			cycle->push(v);
		}
	}
}

Graphm* Graphm::reverse() {
	Graphm* newGraph = new Graphm(*this);
	for (int v = 0; v < this->n(); v++)
		for (int w = this->first(v); w < this->n(); w = this->next(v, w)) {
			newGraph->addEdge(w, v, this->weight(v, w));
			newGraph->addEdge(v, w, 0);
		}
	return newGraph;
}
