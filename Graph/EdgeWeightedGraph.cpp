/*
 * EdgeWeightedGraph.cpp
 *
 *  Created on: 2014年12月26日
 *      Author: therdes
 */

#include "EdgeWeightedGraph.h"
using namespace std;

EdgeWeightedGraph::EdgeWeightedGraph(int n, int e) :
		numVertex(n), numEdge(e) {
	adj = (std::list<WeightedEdge*>**) new std::list<WeightedEdge*>*[this->n()];
	for (int i = 0; i < this->n(); i++)
		adj[i] = new std::list<WeightedEdge*>();
	creatGraph();
}

EdgeWeightedGraph::~EdgeWeightedGraph() {
	for (int i = 0; i < n(); i++) {
		while (!adj[i]->empty()) {
			WeightedEdge* temp = adj[i]->front();
			adj[i]->pop_front();
			delete temp;
		}
		delete adj[i];
	}
	delete[] adj;
}

void EdgeWeightedGraph::creatGraph() {
	int v, w;
	double wt;
	for (int i = 0; i < e(); i++) {
		cin >> v >> w >> wt;
		if (contains(v, w)) {
			cout << "Warning: the edge " << v << " - " << w << " with weight "
					<< wt << " has exist in the graph. Update the weight."
					<< endl;
			removeEdge(v, w);
		}
		addEdge(v, w, wt);
	}
}

void EdgeWeightedGraph::addEdge(int v, int w, double wt) {
	adj[v]->push_front(new WeightedEdge(v, w, wt));
	adj[w]->push_front(new WeightedEdge(w, v, wt));
}

void EdgeWeightedGraph::removeEdge(int v, int w) {
	removeEdge_help(v, w);
	removeEdge_help(w, v);
}

void EdgeWeightedGraph::removeEdge_help(int v, int w) {
	list<WeightedEdge*>::iterator iter = adj[v]->begin();
	while ((*iter)->other(v) != w)
		++iter;
	adj[v]->erase(iter);
	delete *iter;
}

bool EdgeWeightedGraph::contains(int v, int w) const {
	list<WeightedEdge*>::const_iterator iter = adj[v]->begin();
	while (iter != adj[v]->end()) {
		if ((*iter)->other(v) == w)
			return true;
		++iter;
	}
	return false;
}

double EdgeWeightedGraph::getEdgeWeight(int v, int w) const {
	list<WeightedEdge*>::const_iterator iter = adj[v]->begin();
	while (iter != adj[v]->end()) {
		if ((*iter)->other(v) == w)
			return (*iter)->Weight();
		++iter;
	}
	return 0;
}

/*
 * 长点记性！！！
 * 长点记性！！！
 * 长点记性！！！
 * 记得判断迭代器有没有越界啊啊啊！！！
 * 你还TMD想花一个小时去调试这个傻逼错误吗!!!!
 */
int EdgeWeightedGraph::first(int v) const {
	const WeightedEdge* first = firstEdge(v);
	if (first == NULL)
		return n();
	return first->other(v);
}

WeightedEdge* EdgeWeightedGraph::firstEdge(int v) const {
	if (adj[v]->empty())
		return NULL;
	return adj[v]->front();
}

int EdgeWeightedGraph::next(int v, int w) const {
	const WeightedEdge* next = nextEdge(v, w);
	if (next == NULL)
		return n();
	return next->other(v);
}

WeightedEdge* EdgeWeightedGraph::nextEdge(int v, int w) const {
	list<WeightedEdge*>::const_iterator iter = adj[v]->begin();
	while (iter != adj[v]->end()) {
		if ((*iter)->other(v) == w)
			break;
		++iter;
	}
	if (((*iter)->other(v) == w) && ++iter != adj[v]->end())
		return *iter;
	return NULL;
}

ostream& operator<<(ostream& output, EdgeWeightedGraph& G) {
	output << G.n() << " Vertexes and " << G.e() << " Edges" << endl;
	for (int v = 0; v < G.n(); v++) {
		output << v << ": ";
		for (int w = G.first(v); w < G.n(); w = G.next(v, w))
			output << v << "-" << w << ":" << G.getEdgeWeight(v, w) << "  ";
		output << endl;
	}
	return output;
}

Graph* EdgeWeightedGraph::reverse()
{
	return this;
}