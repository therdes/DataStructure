/*
 * KosarajuSCC.h
 *
 *  Created on: 2014年12月18日
 *      Author: therdes
 */

#ifndef KOSARAJUSCC_H_
#define KOSARAJUSCC_H_

#include "Digraph.h"
#include "DepthFirstOrder.h"
#include <stack>

class KosarajuSCC {
private:
	bool* marked;
	int* id;
	int count;

	void dfs(Digraph& dg, int v);

public:
	KosarajuSCC(Digraph& dg);
	~KosarajuSCC();

	bool stronglyConnected(int v, int w) const;
	int sccID(int v);
	int sccCount();
};

#endif /* KOSARAJUSCC_H_ */
