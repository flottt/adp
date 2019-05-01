#include "AdpSuchTree.h"
#include "linklist.h"
#include "adpHelper.h"
#include "Matrix.h"
#include "MatrixMultipliziererInterface.h"
#include <ctime>

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

void matrixQuickMultZeitMessung(const int SIZE = 10, const bool printingMatrix = true, const bool printingTime = true, bool doBoth = true) {
	Matrix<int> A(SIZE, SIZE), B(SIZE, SIZE), C(SIZE, SIZE);
	A.initRandom(0, 100);
	B.initRandom(0, 100);
	clock_t zeit1 = clock();
	A.quickmult(B, C);
	clock_t zeit2 = clock();
	if (doBoth) {
		A.mult(B, C);
	}
	clock_t zeit3 = clock();

	if (printingMatrix) {
		std::cout << "Matrix A " << std::endl;
		A.print();
		std::cout << "---------" << std::endl;
		std::cout << "Matrix B " << std::endl;
		B.print();
		std::cout << "---------" << std::endl;
		std::cout << "Matrix C=AB " << std::endl;
		C.print();
		std::cout << "---------" << std::endl;
	}
	if (printingTime) {
		std::cout << "Matrixmultiplikation " << SIZE << "x" << SIZE 
			<< " Zeit Quickmult: " << (zeit2 - zeit1) / (CLOCKS_PER_SEC / 1000) << "ms, "
		  << " Zeit Directmult: " << (zeit3 - zeit2) / (CLOCKS_PER_SEC / 1000) << "ms"
			<< std::endl; 
	}
}

int adp06_4_main(void) {
	for (int i = 200; i < 10000; i *= 2) {
		matrixQuickMultZeitMessung(i, false, true, (i < 1000));
	}
	return 0;
}

/* Ergebnis: 
Matrixmultiplikation 200x200    Zeit Quickmult:     22ms,  Zeit Directmult:    38ms
Matrixmultiplikation 400x400    Zeit Quickmult:    152ms,  Zeit Directmult:   322ms
Matrixmultiplikation 800x800    Zeit Quickmult:  1.070ms,  Zeit Directmult: 2.719ms
Matrixmultiplikation 1600x1600  Zeit Quickmult:  7.470ms  
Matrixmultiplikation 3200x3200  Zeit Quickmult: 52.112ms
Matrixmultiplikation 6400x6400  Zeit Quickmult:367.874ms */