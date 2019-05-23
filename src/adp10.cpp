#include "adpSkipListe.hpp"
#include <iostream>

int adp10_1_main(void) {
	const int MINIMUM_inclusiv = 10; 
	const int MAXIMUM_inclusiv = 99; 
	const int RANGE = MAXIMUM_inclusiv - MINIMUM_inclusiv + 1;
	SkipListe<int> liste;
	int neu; 
	liste.printDebug(std::cout);
	for (int i = 0; i < 50; i++) {
		neu = MINIMUM_inclusiv + (rand() % RANGE);
		std::cout << std::endl << "Neuer Wert: " << neu << std::endl;
		liste += neu;
		std::cout << "Liste: " << liste << std::endl; 
		liste.printDebug(std::cout);
	}
	for (int i = 0; i < 5; i++) {
		neu = MINIMUM_inclusiv + (rand() % RANGE); 
		std::cout << "Loesche " << neu << std::endl;
		liste -= neu;
		std::cout << "Liste: " << liste << std::endl; 
		liste.printDebug(std::cout);
	}
	return 0;
}
