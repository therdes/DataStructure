/*
 * Topological.h
 *
 *  Created on: 2014年12月18日
 *      Author: therdes
 */

#ifndef TOPOLOGICAL_H_
#define TOPOLOGICAL_H_

#include <queue>
#include "DirectedCycle.h"
#include "Degrees.h"

class Topological {
private:
	std::vector<int>* order;
	bool* marked;

public:
	Topological(Digraph& dg);
	~Topological();

	std::vector<int>* topoOrder();
};

#endif /* TOPOLOGICAL_H_ */
