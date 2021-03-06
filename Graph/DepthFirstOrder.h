/*
 * DepthFirstOrder.h
 *
 *  Created on: 2014年12月18日
 *      Author: therdes
 */

#ifndef DEPTHFIRSTORDER_H_
#define DEPTHFIRSTORDER_H_

#include "Digraph.h"
#include <queue>
#include <stack>

class DepthFirstOrder {
private:
	bool* marked;

	std::queue<int>* pre;
	std::queue<int>* post;
	std::stack<int>* reversePost;

	void dfs(Digraph& dg, int v);

public:
	DepthFirstOrder(Digraph& dg);
	~DepthFirstOrder();

	std::queue<int>& preOrder();
	std::queue<int>& postOrder();
	std::stack<int>& reversePostOrder();
};

#endif /* DEPTHFIRSTORDER_H_ */
