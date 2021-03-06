/*
 * WeightedEdge.h
 *
 *  Created on: 2014年12月26日
 *      Author: therdes
 */

#ifndef WEIGHTEDEDGE_H_
#define WEIGHTEDEDGE_H_

#include <iostream>
#include <stdlib.h>

class WeightedEdge {
private:
	const int v;
	const int w;
	const double weight;

public:
	WeightedEdge(int v, int w, double wt) :
			v(v), w(w), weight(wt) {
	}
	~WeightedEdge() {
	}

	double Weight() const {
		return weight;
	}

	int either() const {
		return v;
	}
	int other(int v) const {
		if (v == this->v)
			return w;
		else if (v == this->w)
			return this->v;
		else {
			std::cout << "Inconsistent edge." << std::endl;
			exit(1);
		}
	}

	int compareTo(const WeightedEdge* that) const {
		if (this->Weight() < that->Weight())
			return -1;
		else if (this->Weight() > that->Weight())
			return 1;
		else
			return 0;
	}

	void showEdge() const {
		std::cout << this->v << "-" << this->w << ":" << this->weight
				<< std::endl;
	}
};

struct WeightedEdgeCompare {
	bool operator()(const WeightedEdge* lhs, const WeightedEdge* rhs) {
		return lhs->Weight() > rhs->Weight();
	}
};

#endif /* WEIGHTEDEDGE_H_ */
