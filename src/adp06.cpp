#include "AdpSuchTree.h"
#include "linklist.h"
#include "adpHelper.h"

int adp06_1_main(void) {
	const int ARRAY_SIZE = 200;
	int arrayliste[ARRAY_SIZE]; 
	initArrayRandom(arrayliste, ARRAY_SIZE, -80, 250);
	arrayliste[0] = 1; 
	arrayliste[1] = 2; 
	arrayliste[2] = 3; 

	linklist liste;

	for (int i = 0; i < ARRAY_SIZE; ++i) {
		liste.push_back(arrayliste[i]); 
	}
	
	std::cout << "Liste unsortiert: " << std::endl << liste << std::endl << std::endl ; 

	liste.quicksort();

	std::cout << "Liste sortiert: " << std::endl << liste << std::endl << std::endl;

	return 0;
}


int adp06_2_main(void) {
	int size = 49;
	ringlist trommel; 
	initRandomizer(); 

	for (int i = 1; i <= size; ++i) {
		trommel.push(i); 
	}

	for (int i = 1; i <= 6; ++i) {
		std::cout << "Zahl #" << i << " ist " << trommel.pop((int)(rand() % size)) << std::endl; 
		--size;
	}
	

	return 0;
}

int adp06_3_main(void) {
	const int ARRAY_SIZE = 200;
	int arrayliste[ARRAY_SIZE];
	initArrayRandom(arrayliste, ARRAY_SIZE, -80, 80); 

	SuchTreeSingle<int> baum; 

	for (int i = 0; i < ARRAY_SIZE; ++i) {
		baum.add(arrayliste[i]); 
	}
	
	std::cout << "BAUM" << std::endl; 
	baum.printInOrderRecursive(std::cout); 

	for (int i = -9; i < 10; ++i) {
		baum.remove(i); 
	}

	std::cout << "BAUM ohne einstellige Zahlen " << std::endl; 
	baum.printInOrderRecursive(std::cout); 

	baum.add(0);
	baum.add(0);
	baum.add(0);

	std::cout << "BAUM mit mehrfach geaddeder 0 " << std::endl;
	baum.printInOrderRecursive(std::cout);


	return 0;
}


int adp06_4_main(void) {



	return 0;
}
