#include <iostream>
#include <cstring>
#include "adpHelper.h"

void mergingSortDemo(int * band1Ptr, int * band2Ptr, const int * bandEnde, int * ramPtr);
void mergeSortDemo(int * a, int size, int * ram);
inline int maxIndexInTree(int * baum, int index1, int index2, int index3, int treesize); 
void heapify(int * a, int size, int indexWurzel);
void heapSortDemo(int * a, int size);
int adp05_1_main();
void countSort(int const * const source, int * const dest, int const size);
int adp05_4_main();

/** Sortieren durch Mischen zweier vorsortierter Baender. 
 * @param int * band1Ptr Array mit den zu sortierenden Zahlen. 
 * @param int * band2Ptr Trennungspointer, ab wann das Array als Band2 zu interpretieren ist. 
 * @param const int * bandEnde Pointer auf letzte zu sortierende Zahl 
 * @param int * ramPtr Separater Speicherplatz zum Zwischenspeichern. Sollte mindestens so groﬂ sein wie das Array */
void mergingSortDemo(int * band1Ptr, int * band2Ptr, const int * bandEnde, int * ramPtr) {
	int * bandTrennung = band2Ptr, *ramStart = ramPtr; 
	int ** bandLow = nullptr;
	while (band1Ptr < bandTrennung && band2Ptr < bandEnde) {
		bandLow = ((*band1Ptr <= *band2Ptr) ? &band1Ptr : &band2Ptr); 
		*ramPtr = **bandLow;
		++(*bandLow);
		++ramPtr;
	}
	//falls das erste Band leer wurde, ist der Rest des zweiten Bandes in sito bereits richtig einsortiert. 
	//falls das zweite Band leer wurde, muss der Rest des ersten Bandes in sito an das Ende des zweiten Bandes. 
	while (band1Ptr < bandTrennung) {
		--bandTrennung; 
		--band2Ptr; 
		*band2Ptr = *bandTrennung; 
	}
	//der Speicher muss nun an das zweite Band angeklebt werden. 
	while (ramPtr > ramStart) {
		--band2Ptr; 
		--ramPtr; 
		*band2Ptr = *ramPtr; 
	}
}

/** Sortiert ein Array mit MergeSort und gibt dabei Zwischenergebnisse auf der Console aus. 
 * @param int * baum Das zu sortierende Array 
 * @param int size Die Groesse des Arrays 
 * @param int * ram temporaeres Speicherarray, das auch mindestens size gross sein sollte. */
void mergeSortDemo(int * a, int size, int * ram) {
	std::cout << "Sortierknoten "; 
	printArrayInOneLine(a, size); 
	if (size >= 2) {
		int sizeHalb = size / 2; 
		mergeSortDemo(a, sizeHalb, ram); 
		mergeSortDemo(a + sizeHalb, size - sizeHalb, ram); 

		mergingSortDemo(a, a + sizeHalb, a + size, ram); 
		std::cout << "Sortierergebnis ";
		printArrayInOneLine(a, size);
	}
}

/** Sucht in einem Array unter 3 Kandidaten den groessten Wert. Optimiert f¸r heapify. 
 * @param int index1 Kandidatenindex. Wird bei Gleichstand priorisiert. Muss existieren. 
 * @param int index2 Kandidatenindex. Mittlerer Index, wird bei ArrayIndexOutOfRange ignoriert. 
 * @param int index3 Kandidatenindex. Hinterster Index, wird bei ArrayIndexOutOfRange ignoriert. 
 * @param int treesize Groesse des Arrays, um ArrayIndexOutOfRange beurteilen zu kˆnnen. 
 * @return int index, dessen Arraywert der Groesste ist. */
inline int maxIndexInTree(int * baum, int index1, int index2, int index3, int treesize) {
	if (index2 >= treesize) {
		return index1;
	} else if (baum[index1] < baum[index2]) {
		return ((index3 < treesize && (baum[index2] < baum[index3])) ? index3 : index2);
	} else {
		return ((index3 < treesize && (baum[index1] < baum[index3])) ? index3 : index1); 
	}
}

/** Heapify wie aus der Vorlesung. */
void heapify(int * a, int size, int indexWurzel) {
	int indexLeft, indexRight, indexMax; 
	while (1) {
		indexLeft = indexWurzel * 2 + 1;
		indexRight = indexLeft + 1;
		indexMax = maxIndexInTree(a, indexWurzel, indexLeft, indexRight, size);
		if (indexMax == indexWurzel) {
			return;
		} else {
			swop(a, indexWurzel, indexMax);
			indexWurzel = indexMax; 
		}
	}
}

/** Sortiert ein Array mit HeapSort und gibt dabei Zwischenergebnisse auf der Console aus.  
* @param int * a Das zu sortierende Array 
* @param int size Die Groesse des Arrays */
void heapSortDemo(int * a, int size) {
	printBinaryTreeLeftAligned(std::cout, a, size, "kanonischer Binaerbaum");
	std::cout << std::endl << "create Heap" << std::endl; ;
	for (int indexWurzel = (size - 1) / 2; indexWurzel >= 0; --indexWurzel) {
		heapify(a, size, indexWurzel); 
		printBinaryTreeLeftAligned(std::cout, a, size, "creating Heap... ");
	}
	std::cout << std::endl << "heap created" << std::endl; 

	while (size > 0) {
		swop(a, 0, size - 1);
		size--;
		heapify(a, size, 0);
		printBinaryTreeLeftAligned(std::cout, a, size, "found maximum and continue... ");
	}
}


/** Blatt 5 Aufgabe 1 Main */
int adp05_1_main() {
	const int arraysize = 10; 
	const int a[arraysize] = { -5, +13, -32, +7, -3, +17, +23, +12, -35, +19 };
	int b[arraysize]; 
	int ram[arraysize]; 

	std::memcpy(b, a, sizeof(*b) * arraysize); 
	std::cout << "Sortierfeld: "; 
	printArrayInOneLine(b, arraysize); 
	std::cout << "MergeSortDemo" << std::endl;
	mergeSortDemo(b, arraysize, ram);
	std::cout << "--------------" << std::endl;

	std::memcpy(b, a, sizeof(*b) * arraysize); 
	std::cout << "HeapSortDemo" << std::endl;
	heapSortDemo(b, arraysize); 
	std::cout << "--------------" << std::endl;
	std::cout << "HeapSort Ergebnis: ";
	printArrayInOneLine(b, arraysize); 
	


	return 0; 
}


void countSort(int const * const source, int * const dest, int const size) {
	if (size <= 0) return;
	int max = *source, min = *source, i = 0;
	const int * dataPtr = nullptr;
	int *slots = nullptr, *sPtr = nullptr, *slotsEnd = nullptr;

	//Bestimme Maximum und Minimum 
	for (dataPtr = source + size - 1; dataPtr > source; --dataPtr) {
		if (max < *dataPtr) {
			max = *dataPtr;
		} else if (min > *dataPtr) {
			min = *dataPtr;
		}
	}

	//eigentlich brauchen wir nur die Groesse, nicht das Maximum 
	max -= min; 
	slots = new int[max + 1]{ 0 };
	slotsEnd = slots + max;

	//Slots durch Zaehlen befuellen 
	for (dataPtr = source + size - 1; dataPtr >= source; --dataPtr) {
		++slots[*dataPtr - min];
	}

	//Slots akkumulieren 
	for (sPtr = slots + 1; sPtr <= slotsEnd; ++sPtr) {
		*sPtr += sPtr[-1];
	}

	//Daten ex sito einsortieren 
	for (dataPtr = source + size - 1; dataPtr >= source; --dataPtr) {
		sPtr = slots + *dataPtr - min; 
		(*sPtr)--;
		dest[*sPtr] = *dataPtr;
	}

	delete[] slots;
}

/** Blatt 5 Aufgabe 4 Main */
int adp05_4_main() {
	int a[10] = { 3, 4, 3, 4, 5, 5, 6, 5, 4, 3 }; 
	int b[10]; 
	countSort(a, b, 10); 
	printArray(b, 10);
	return 0;
}
