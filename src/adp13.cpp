#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include "adpHelper.h"

/** einfacher gerichteter Graph, dessen Nodes durchlaufend nummeriert sind von 0 bis size-1. */
class AdpGraph {
private: 
	std::vector<std::set<int>> adjazenzListen; 

public: 
	AdpGraph(int size = 0); 
	void add(int from, int to); 
	void remove(int from, int to); 

	bool isSymmetric(); 
	void calcDijkstra(int from, std::vector<int> & to); 
};

AdpGraph::AdpGraph(int size) {
	this->adjazenzListen.resize(size); 
}

void AdpGraph::add(int from, int to) {
	int size = this->adjazenzListen.size(); 
	if (from >= size || to >= size) {
		this->adjazenzListen.resize(1 + ((from > to) ? from : to)); 
	}

	this->adjazenzListen[from].insert(to); 
}

void AdpGraph::remove(int from, int to) {
	if (from < this->adjazenzListen.size()) {
		this->adjazenzListen[from].erase(to); 
	}
}

bool AdpGraph::isSymmetric() {
	int size = this->adjazenzListen.size(); 
	int to, fromToFrom;
	std::vector<std::set<int>::iterator> pos(size);
	for (int i = 0; i < size; ++i) {
		pos[i] = this->adjazenzListen[i].begin(); 
	}
	for (int from = 0; from < size; ++from) {
		for (; pos[from] != this->adjazenzListen[from].end(); ++(pos[from])) {
			to = *(pos[from]);
			if (from == to) {
				continue;
			} else if (pos[to] == this->adjazenzListen[to].end()) {
				return false;
			} else {
				fromToFrom = *(pos[to]);
				if (fromToFrom != from) {
					return false;
				} else {
					(pos[to])++; 
				}
			}
		}
	}

	return true;
}

void AdpGraph::calcDijkstra(int from, std::vector<int> & to) {
	unsigned int size = this->adjazenzListen.size(); 
	if (size <= 0) return; 
	int * stack = new int[size]; 
	int * ptrNext = stack;     //erste vergebene Platz
	int * ptrEnd = stack + 1;  //erste freie Platz
	int * ptrIncrease = stack; //
	int aktuell; 
	int dist = 0; 
	if (to.size() < size) {
		to.resize(size); 
	}
	for (int & ini : to) {
		ini = INT_MAX; 
	}
	
	*stack = from; 
	to[from] = dist; 
	++dist;
	while (ptrNext != ptrEnd) {
		aktuell = *ptrNext; 
		for (int kanteNext : this->adjazenzListen[aktuell]) {
			if (to[kanteNext] > dist) {
				*ptrEnd = kanteNext; 
				ptrEnd++; 
				to[kanteNext] = dist; 
			}
		}
		if (ptrIncrease == ptrNext) {
			dist++; 
			ptrIncrease = ptrEnd - 1;
		}
		ptrNext++; 
	}
	delete[] stack; 
}
//End of Class AdpGraph
//----------------------------------------------------------------
void testCase13_Symmetric(void);
int adp13_1_main(void); 

void testCase13_Symmetric(void) {
	std::vector<int> dist; 
	AdpGraph g; 
	std::cout << "Graph 1 <-> 2* <-> 3* <-> 4 <-> 2,  *:reflexiv" << std::endl; 
	testAssertInt(g.isSymmetric(), true, "leerer Graph sollte symmetrisch sein. ");
	g.add(1, 2); 
	testAssertInt(g.isSymmetric(), false, "Graph sollte asymmetrisch sein. 1 --> 2. ");
	g.add(2, 1); 
	testAssertInt(g.isSymmetric(), true, "Graph sollte symmetrisch sein. 1 <-> 2. ");
	g.add(2, 3); 
	g.add(3, 4); 
	g.add(4, 2); 
	testAssertInt(g.isSymmetric(), false, "Graph sollte asymmetrisch sein. 1 <-> 2 -> 3 -> 4 -> 2. ");
	g.add(3, 2);
	g.add(4, 3);
	g.add(2, 4);
	testAssertInt(g.isSymmetric(), true, "Graph sollte symmetrisch sein. 1 <-> 2 <-> 3 <-> 4 <-> 2. ");
	g.add(2, 2); 
	g.add(3, 3); 
	testAssertInt(g.isSymmetric(), true, "Graph sollte symmetrisch sein. 1 <-> 2* <-> 3* <-> 4 <-> 2. ");
	for (int from = 0; from <= 4; ++from) {
		g.calcDijkstra(from, dist); 
		std::cout << "Distanzen von " << from << " nach x: ";
		printArrayInOneLine(&(dist[0]), dist.size()); 	
	}

	AdpGraph gSchleife = 3; 
	gSchleife.add(1, 1); 
	gSchleife.add(2, 2); 
	gSchleife.add(3, 3); 
	testAssertInt(gSchleife.isSymmetric(), true, "Graph sollte symmetrisch sein. 1*, 2*, 3*");
	gSchleife.add(3, 2);
	testAssertInt(gSchleife.isSymmetric(), false, "Graph sollte asymmetrisch sein. 1*, 2* <- 3*");

	std::cout << "Graph 1 -> 2 -> 3 -> 4 -> 5 -> 6" << std::endl; 
	AdpGraph gKette; 
	gKette.add(5, 6); 
	gKette.add(4, 5); 
	gKette.add(3, 4); 
	gKette.add(2, 3); 
	gKette.add(1, 2); 
	testAssertInt(gSchleife.isSymmetric(), false, "Graph sollte asymmetrisch sein. 1 -> 2 -> 3 -> 4 -> 5 -> 6");
	for (int from = 0; from <= 6; ++from) {
		gKette.calcDijkstra(from, dist);
		std::cout << "Distanzen von " << from << " nach x: ";
		printArrayInOneLine(&(dist[0]), dist.size());
	}


	std::cout << "Symmetric Tests completed. " << std::endl; 

}

int adp13_1_main(void) {
	testCase13_Symmetric();
	return 0;
}