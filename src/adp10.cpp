#include "adpSkipListe.hpp"
#include <iostream>

int adp10_1_main(void) {
	SkipListe<int> liste;
	int neu; 
	liste.printDebug(std::cout);
	for (int i = 0; i < 50; i++) {
		neu = 10 + (rand() % 90);
		std::cout << std::endl << "Neuer Wert: " << neu << std::endl;
		liste.insertKey(neu);
		liste.printDebug(std::cout);
	}

	return 0;
}