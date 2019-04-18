#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <time.h>

#include "adpHelper.h"

void swop(int * a, const int x1, const int x2);
void initArrayRandom(int * a, const int n, const int minValue, const int maxValue);
void printArray(const int * a, const int n); 
void insertionSortMin(int * a, int n); 
void bubbleSortMax(int * a, int n); 
void selectionSortMax(int * a, int n);
void quickSortPreparePartition(int * a, int from, int to, int & part);
void quickSort(int * a, int from, int to);
void quickSort(int * a, int n);
int adp04_1_main(); 
bool sucheSummeUndSortiere(int zielSumme, int * a, int n, int & resultIndex1, int & resultIndex2); 
bool sucheSummeLangsamUndSchlecht(const int zielSumme, const int * a, const int n);
void testAufgabe2(); 
int adp04_2_main();
void zeitmessung(const char * algoName, void(*sortieren)(int *, int));
int adp04_3_main();
void insertionSortRek(int * a, int j, int n);
void insertionSortRek(int * a, int n);
void kopiereBand(int ** bandSrc, int * bandSrcEnde, int ** zielBand);
void mergeSort(int * a, int n);
int adp04_4_main();

/** setzt im Array a Zufallswerte zwischen minValue und maxValue 
 * @param int * a Array, dessen Werte randomisiert werden sollen. 
 * @param const int n Groesse des Arrays a bzw. Anzahl an zu setzenden Werten. 
 * @param const int minValue = 0 Der kleinste erlaubte Wert. Darf auch negativ sein. 
 * @param const int maxValue = 100 Der groesste erlaubte Wert. Darf auch negativ sein. Muss mindestens minValue sein. */
void initArrayRandom(int * a, const int n, const int minValue = 0, const int maxValue = 100) {
	int rangeValue = maxValue - minValue; 
	std::srand(static_cast<unsigned>(std::time(nullptr)));
	for (int i = n - 1; i >= 0; --i) {
		a[i] = rand() % rangeValue + minValue; 
	}
}

/** Aufgabe 1.1: InsertionSort */
void insertionSortMin(int * a, int n) {
	int key, j; 

	for (int index = n - 2; index >= 0; --index) {
		//Folge ist ab index + 1 sortiert. sortiere index ein. 
		key = a[index]; 
		for (j = index + 1; j < n && a[j] < key; ++j) {
			a[j - 1] = a[j]; 
		}
		a[j - 1] = key; 
	}
}

/** Aufgabe 1.2: BubbleSort */
void bubbleSortMax(int * a, int n) {
	for (int i = 0; i < n; ++i) {
		for (int j = 1; j < n - i; ++j) {
			if (a[j - 1] > a[j]) {
				swop(a, j - 1, j);
			}
		}
	}
}

/** Aufgabe 1.3: SelectionSort */
void selectionSortMax(int * a, int n) {
	int maxValue, maxIndex; 
	for (int i = n - 1; i >= 0; --i) {
		maxValue = a[i]; 
		maxIndex = i; 
		for (int j = i - 1; j >= 0; --j) {
			if (maxValue < a[j]) {
				maxValue = a[j]; 
				maxIndex = j; 
			}
		}
		swop(a, maxIndex, i); 
	}
}

/** Unterfunktion zu Aufgabe 1.4 */
void quickSortPreparePartition(int * a, int from, int to, int & part) {
	int pivotIndex = rand() % (to - from) + from; 
	int pivotValue = a[pivotIndex]; 
	swop(a, pivotIndex, from); 
	part = from - 1; 
	for (int i = from; i <= to; ++i) {
		if (a[i] <= pivotValue) {
			part++; 
			swop(a, i, part); 
		}
	}
	swop(a, from, part);
}

/** Aufgabe 1.4: rekursives Quicksort mit zufälligem Pivotelement */
void quickSort(int * a, int from, int to) {
	int part; 
	if (from < to) {
		quickSortPreparePartition(a, from, to, part); 
		quickSort(a, from, part - 1); 
		quickSort(a, part + 1, to); 
	}
}

void quickSort(int * a, int n) {
  quickSort(a, 0, n-1); 
}

/** Aufgabe 1: Sortiert 4 Arrays mit unterschiedlichen Algos. */
int adp04_1_main() {
	int a[100]; 
	std::cout << "Insertion Sort via Minimum: " << std::endl; 
	initArrayRandom(a, 100); 
	insertionSortMin(a, 100); 
	printArray(a, 100); 

	std::cout << std::endl << "Bubble Sort: " << std::endl;
	initArrayRandom(a, 100); 
	bubbleSortMax(a, 100);
	printArray(a, 100);

	std::cout << std::endl << "Selection Sort via Maximum: " << std::endl;
	initArrayRandom(a, 100);
	selectionSortMax(a, 100);
	printArray(a, 100);
		
	std::cout << std::endl << "Quick Sort via Random Pivot: " << std::endl;
	initArrayRandom(a, 100);
	quickSort(a, 0, 99);
	printArray(a, 100);

	return 0;
}


/** Aufgabe 2: Testet, ob man einen Summenwert mit 2 aus n Zahlen bekommt. */
bool sucheSummeUndSortiere(int zielSumme, int * a, int n, int & resultIndex1, int & resultIndex2) {
  int summe; 
	quickSort(a, 0, n - 1); 
	resultIndex2 = n - 1; 
	for (resultIndex1 = 0; resultIndex1 < resultIndex2; ++resultIndex1) {
		while(1) {
      summe = a[resultIndex1] + a[resultIndex2]; 
      if (summe == zielSumme) {
				return true; 
			} else if (summe > zielSumme) {
 				--resultIndex2;
				if (resultIndex2 <= resultIndex1) return false;
			} else {
				break; 
			}
		}
	}
	return false; 
}

/** Aufgabe 2 Kontrollwertberechnung */
bool sucheSummeLangsamUndSchlecht(const int zielSumme, const int * a, const int n) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i != j && (a[i] + a[j] == zielSumme)) {
				return true; 
			}
		}
	}
	return false; 
}

/** Testet den sucheSummenalgorithmus aus Aufgabe 2 gegen die naive Suchmethode. */
void testAufgabe2() {
	const int ARRAY_SIZE = 30; 
	const int zielSumme = 200; 
  int a[ARRAY_SIZE]; 
	int resultIndex[4]; 
	
	for (int i = 0; i < 10000; ++i) {
		initArrayRandom(a, ARRAY_SIZE); 
		resultIndex[3] = sucheSummeLangsamUndSchlecht(zielSumme, a, ARRAY_SIZE); 
	  resultIndex[2] = sucheSummeUndSortiere(zielSumme, a, ARRAY_SIZE, resultIndex[0], resultIndex[1]); 
		if (resultIndex[2] != resultIndex[3]) {
			std::cout << "ERROR" << std::endl; 
			std::cout << "Algo hat Summe gefunden: " << resultIndex[2] << std::endl; 			
			std::cout << "Korrekt waere aber: " << resultIndex[3] << std::endl; 
			std::cout << "resultIndex-Array: [" << resultIndex[0] << ", " << resultIndex[1] << "]: " << std::endl; 
			printArray(a, ARRAY_SIZE); 
			return; 
		}
	}
  std::cout << "test completed successful without errors" << std::endl;
}

/** Aufgabe 2: Sucht Summenwert mit 2 aus n Zahlen aus Zufallsarray. */
int adp04_2_main() {
  const int ARRAY_SIZE = 20; 
  const int zielSumme = 100; 
  int a[ARRAY_SIZE]; 
  initArrayRandom(a, ARRAY_SIZE);
	printArray(a, ARRAY_SIZE); 
  
  int resultIndex[3]; 
  resultIndex[2] = sucheSummeUndSortiere(zielSumme, a, ARRAY_SIZE, resultIndex[0], resultIndex[1]); 
  if (resultIndex[2]) {
		std::cout << "ja, summe gefunden: " << zielSumme << " = " << a[resultIndex[0]] << " + " << 			a[resultIndex[1]] << std::endl; 
	} else {
    std::cout << "nein, summe " << zielSumme << " nicht gefunden. " << std::endl; 
	}
  return 0; 
}

/** zu Aufgabe 3: Zeitmessung eines Algorithmus. Konsolenausgabe. */
void zeitmessung(const char * algoName, void(*sortieren)(int *, int) = 0) {
  const int ARRAY_SIZE = 25000; 
  int a[ARRAY_SIZE]; 
	initArrayRandom(a, ARRAY_SIZE, -32100, 123456789); 
	
  double t1, t2; 
  t1 = clock(); 
	
	sortieren(a, ARRAY_SIZE); 
	
	t2 = clock() - t1; 
	t2 /= (CLOCKS_PER_SEC / 1000); 
	std::cout << "Sortiert " << ARRAY_SIZE << " Elemente mit " << algoName << " in " << std::setw(8) << std::setprecision(1) << std::fixed << t2 << " ms." << std::endl; 
}

/** Aufgabe 3: Zeitmessung beim Sortieren */
int adp04_3_main() {
	zeitmessung("BubbleSort   ", &bubbleSortMax);
	zeitmessung("InsertionSort", &insertionSortMin);
	zeitmessung("InsertREKSort", &insertionSortRek); 
	zeitmessung("SelectionSort", &selectionSortMax);
	zeitmessung("QuickSort    ", &quickSort);
	zeitmessung("MergeSort    ", &mergeSort);
	zeitmessung("BubbleSort   ", &bubbleSortMax);
	zeitmessung("InsertionSort", &insertionSortMin);
	zeitmessung("InsertREKSort", &insertionSortRek); 
	zeitmessung("SelectionSort", &selectionSortMax);
	zeitmessung("QuickSort    ", &quickSort);
	zeitmessung("MergeSort    ", &mergeSort);
	zeitmessung("BubbleSort   ", &bubbleSortMax);
	zeitmessung("InsertionSort", &insertionSortMin);
	zeitmessung("InsertREKSort", &insertionSortRek); 
	zeitmessung("SelectionSort", &selectionSortMax);
	zeitmessung("QuickSort    ", &quickSort);
	zeitmessung("MergeSort    ", &mergeSort);

	return 0;
}
/* Results: 
Sortiert 25000 Elemente mit BubbleSort    in   1774.4 ms.
Sortiert 25000 Elemente mit InsertionSort in    293.3 ms.
Sortiert 25000 Elemente mit InsertREKSort in    329.7 ms.
Sortiert 25000 Elemente mit SelectionSort in    557.7 ms.
Sortiert 25000 Elemente mit QuickSort     in      3.4 ms.
Sortiert 25000 Elemente mit MergeSort     in      3.3 ms.
Sortiert 25000 Elemente mit BubbleSort    in   1712.3 ms.
Sortiert 25000 Elemente mit InsertionSort in    291.0 ms.
Sortiert 25000 Elemente mit InsertREKSort in    330.4 ms.
Sortiert 25000 Elemente mit SelectionSort in    557.6 ms.
Sortiert 25000 Elemente mit QuickSort     in      3.4 ms.
Sortiert 25000 Elemente mit MergeSort     in      3.4 ms.
Sortiert 25000 Elemente mit BubbleSort    in   1716.9 ms.
Sortiert 25000 Elemente mit InsertionSort in    290.0 ms.
Sortiert 25000 Elemente mit InsertREKSort in    329.4 ms.
Sortiert 25000 Elemente mit SelectionSort in    557.9 ms.
Sortiert 25000 Elemente mit QuickSort     in      3.5 ms.
Sortiert 25000 Elemente mit MergeSort     in      3.3 ms.

Sortiert 50000 Elemente mit BubbleSort    in   7096.7 ms.
Sortiert 50000 Elemente mit InsertionSort in   1154.8 ms.
Sortiert 50000 Elemente mit InsertREKSort in   1322.4 ms.
Sortiert 50000 Elemente mit SelectionSort in   2203.4 ms.
Sortiert 50000 Elemente mit QuickSort     in      7.1 ms.
Sortiert 50000 Elemente mit MergeSort     in      7.4 ms.
Sortiert 50000 Elemente mit BubbleSort    in   7213.8 ms.
Sortiert 50000 Elemente mit InsertionSort in   1158.1 ms.
Sortiert 50000 Elemente mit InsertREKSort in   1316.5 ms.
Sortiert 50000 Elemente mit SelectionSort in   2202.2 ms.
Sortiert 50000 Elemente mit QuickSort     in      7.4 ms.
Sortiert 50000 Elemente mit MergeSort     in      7.3 ms.
Sortiert 50000 Elemente mit BubbleSort    in   7144.6 ms.
Sortiert 50000 Elemente mit InsertionSort in   1163.0 ms.
Sortiert 50000 Elemente mit InsertREKSort in   1324.1 ms.
Sortiert 50000 Elemente mit SelectionSort in   2203.7 ms.
Sortiert 50000 Elemente mit QuickSort     in      7.3 ms.
Sortiert 50000 Elemente mit MergeSort     in      7.2 ms.

Sortiert 1234567 Elemente mit QuickSort     in    228.8 ms.
Sortiert 1234567 Elemente mit MergeSort     in    231.4 ms.
Sortiert 1234567 Elemente mit QuickSort     in    224.3 ms.
Sortiert 1234567 Elemente mit MergeSort     in    229.6 ms.
*/

/** private Funktion. Sortiert rekursiv das Array a. (Aufgabe 4)*/
void insertionSortRek(int * a, int j, int n) {
	if (j < n) {	
		int i, key = a[j]; 
		for (i = j - 1; i >= 0 && a[i] > key; --i) {
			a[i + 1] = a[i]; 
		}
		a[i + 1] = key; 
		insertionSortRek(a, j + 1, n); 
	}
}

void insertionSortRek(int * a, int n) {
	insertionSortRek(a, 1, n); 
}

void kopiereBand(int ** bandSrc, int * bandSrcEnde, int ** zielBand) {
  while(*bandSrc <= bandSrcEnde) {
		**zielBand = **bandSrc; 
		(*zielBand)++; 
		(*bandSrc)++; 
	}
}

/** iteratives MergeSort. funktioniert wirklich ;) */
void mergeSort(int * a, int n) {
  int * band = new int[2 * n]; 
	int * inBand = a, * inBandE = 0; 
	int * outBand = band; 
  int * band1 = 0, * band1E = 0, * band2 = 0, * band2E = 0, * bandOut = 0; 

	for (int bandlang = 1; 1; bandlang *= 2) {
		if (bandlang * 2 >= n) {
			outBand = a; 
		}

		bandOut = outBand; 
		inBandE = inBand + n - 1; 
		for (int i = 0; i < n; i += bandlang * 2) {
			band1 = inBand + i; 
			band2 = band1 + bandlang; 
			band1E = band2 - 1; 
			band2E = band2 + bandlang - 1;
			if (band2E > inBandE) {
				band2E = inBandE;
				if (band1E > inBandE) band1E = inBandE;
				if (band2 > inBandE) {
					kopiereBand(&band1, band1E, &bandOut); 
					band2 = 0; 
				}
			}
			if (band2 != 0) while(1) {
				if (*band1 <= *band2) {
					kopiereBand(&band1, band1, &bandOut); 
					if (band1 > band1E) {
						kopiereBand(&band2, band2E, &bandOut); 
						break; 
					}
				} else {
					kopiereBand(&band2, band2, &bandOut); 
					if (band2 > band2E) {
						kopiereBand(&band1, band1E, &bandOut); 
						break; 
					}
				}
			} //end while
		} //next i

		if (outBand == a) {
			delete[] band; 
			return; 
		} else {
			inBand = outBand; 
			outBand = (outBand == band ? band + n : band); 
		}
		//std::cout << std::endl << "Zwischenergebnis: bandlang = " << bandlang << std::endl;
		//printArray(band, 2 * n); 
	} //next bandlang
}

int adp04_4_main() {
	int a[100]; 
	std::cout << "Insertion Sort via Minimum: " << std::endl; 
//	initArrayRandom(a, 100); 
	for (int i = 0; i < 100; ++i) {a[i] = 255-i;}
	mergeSort(a, 100); 
	printArray(a, 100); 

	return 0; 
}


/*
int main() {
//	testAufgabe2(); 
	int returnresult = adp04_3_main(); 
  std::cout << "ende" << std::endl; 
  return returnresult; 

}*/
