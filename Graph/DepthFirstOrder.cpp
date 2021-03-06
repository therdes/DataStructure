/*
 * DepthFirstOrder.cpp
 *
 *  Created on: 2014年12月18日
 *      Author: therdes
 */

#include "DepthFirstOrder.h"

using namespace std;

DepthFirstOrder::DepthFirstOrder(Digraph& dg) {
	pre = new queue<int>();
	post = new queue<int>();
	reversePost = new stack<int>();

	marked = new bool[dg.n()];
	for (int i = 0; i < dg.n(); i++)
		marked[i] = false;

	for (int v = 0; v < dg.n(); v++)
		if (!marked[v])
			dfs(dg, v);
}

DepthFirstOrder::~DepthFirstOrder()
{
	delete[] marked;
	delete pre;
	delete post;
	delete reversePost;
}

void DepthFirstOrder::dfs(Digraph& dg, int v) {
	pre->push(v);

	marked[v] = true;
	for (int w = dg.first(v); w < dg.n(); w = dg.next(v, w))
		if (!marked[w])
			dfs(dg, w);

	post->push(v);
	reversePost->push(v);
}

queue<int>& DepthFirstOrder::preOrder() {
	return *pre;
}

queue<int>& DepthFirstOrder::postOrder() {
	return *post;
}

stack<int>& DepthFirstOrder::reversePostOrder() {
	return *reversePost;
}
