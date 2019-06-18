#include <climits>
#include <iostream>
#include "adpHelper.h"

void iniVorgaengerMatrix(int * vorgaengerMatrix, int size) {
	int index = 0, sizeQuad = size * size;
	for (int zeile = 0; zeile < size; ++zeile) {
		for (int spalte = 0; spalte < size; ++spalte, ++index) {
			vorgaengerMatrix[index] = zeile; 
		}
	}
}

void floydWarshall(int * adjazenzMatrix, int * vorgaengerMatrix , int size) {
	int umwegLaenge, index = 0, index1, index2; 
	for (int knoten = 0; knoten < size; ++knoten) {
		for (int zeile = 0; zeile < size; ++zeile) if (knoten != zeile) {
			for (int spalte = 0; spalte < size; ++spalte) if (knoten != spalte) {
				index = zeile * size + spalte; 
				index1 = zeile * size + knoten; 
				index2 = knoten * size + spalte; 
				if (adjazenzMatrix[index1] != INT_MAX && adjazenzMatrix[index2] != INT_MAX) {
					//es gibt einen Weg zeile -> knoten -> spalte
					umwegLaenge = adjazenzMatrix[index1] + adjazenzMatrix[index2];
					if (umwegLaenge < adjazenzMatrix[index]) {
						//der Umweg ist kuerzer 
						adjazenzMatrix[index] = umwegLaenge; 
						if (vorgaengerMatrix != nullptr) {
							vorgaengerMatrix[index] = vorgaengerMatrix[index2];
							std::cout << "vorgaenger <" << knoten << ">[" << zeile << ", " << spalte << "] = " << vorgaengerMatrix[index] << std::endl;
						}
					}
				}
			} //next spalte
		} //next zeile
	} //next knoten
}

void printResultOfFloydWarshall(const int * adjazenzMatrix, const int * vorgaengerMatrix, const int size) {
	std::cout << "Ergebnis: " << std::endl;
	printMatrix(adjazenzMatrix, size, true);
	std::cout << "VorgaengerMatrix: " << std::endl;
	printMatrix(vorgaengerMatrix, size);
	std::cout << std::endl;
}

int adp14_1_main(void) {
	const int size = 6; 
	int adjazenzMatrix[size * size] {
	// nach 1   nach 2   nach 3   nach 4   nach 5   nach 6
		     0 , INT_MAX, INT_MAX, INT_MAX,     -1 , INT_MAX,  //von 1
		     1 ,      0 , INT_MAX,      2 , INT_MAX, INT_MAX,  //von 2
		INT_MAX,      2 ,      0 , INT_MAX, INT_MAX,     -8 ,  //von 3
		    -4 , INT_MAX, INT_MAX,      0 ,      3 , INT_MAX,  //von 4
		INT_MAX,      7 , INT_MAX, INT_MAX,      0 , INT_MAX,  //von 5
		INT_MAX,      5 ,     10 , INT_MAX, INT_MAX,      0    //von 6
  // nach 1   nach 2   nach 3   nach 4   nach 5   nach 6
	};
	int vorgaengerMatrix[size * size]; 

	iniVorgaengerMatrix(vorgaengerMatrix, size); 
	floydWarshall(adjazenzMatrix, vorgaengerMatrix, size); 

	printResultOfFloydWarshall(adjazenzMatrix, vorgaengerMatrix, size); 
	return 0; 
}

int adp14_2_main(void) {
	const int size = 4; 
	// 1 <-> 2 <- 3 <- 4
	int adjazenzMatrix[size * size]{
		// nach 1   nach 2   nach 3   nach 4   
		       0 ,      1 , INT_MAX, INT_MAX,  //von 1
		       1 ,      0 , INT_MAX, INT_MAX,  //von 2
		 INT_MAX ,      1 ,      0 , INT_MAX,  //von 3
		 INT_MAX , INT_MAX,      1 ,      0 ,  //von 4
		// nach 1   nach 2   nach 3   nach 4 
	};

	int vorgaengerMatrix[size * size]; 

	iniVorgaengerMatrix(vorgaengerMatrix, size); 
	floydWarshall(adjazenzMatrix, vorgaengerMatrix, size); 

	printResultOfFloydWarshall(adjazenzMatrix, vorgaengerMatrix, size);
	return 0; 
}