#include <cassert>
#include <iostream>
#include "adpHelper.h"
#include "AdpMinHeap.hpp"

int adp12_2_main(void);
using kkey = int; 
using kelem = int;

int adp12_2_main(void) {
	const int anzahl = 10; 
	int zv[anzahl];
	initRandomizer(); 
	initArrayRandom(zv, anzahl, 100, 999);

	MinHeap<kkey, kelem>::HeapNode<kkey, kelem> * newNode = nullptr;
	MinHeap<kkey, kelem> x;
	for (int i = 0; i < anzahl; ++i) {
		newNode = x.insert(zv[i], i); 
		assert(newNode->k == zv[i]); 
		assert(newNode->o == i); 
	}
	x.debugPreOrder(std::cout << std::endl << " Heap-PreOrder-Debug: " << std::endl);
	std::cout << std::endl << " Senke letzten Key von " << newNode->k << " auf 7" << std::endl;
	x.changeKey(*newNode, 7); 
	x.debugPreOrder(std::cout); 
	std::cout << std::endl;
	for (int i = 0; i < anzahl; ++i) {
		kkey k = x.getNextKey();
		kelem v = x.pop();

		std::cout << "#" << i << ". next Value @" << k << " = " << v << std::endl;
		x.debugPreOrder(std::cout << " Heap-PreOrder-Debug" << std::endl);
		std::cout << std::endl;
	}
	return 0; 
}
//int main(void) { return adp12_2_main(); }

