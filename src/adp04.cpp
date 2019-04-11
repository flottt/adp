#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iomanip>

void swop(int * a, int x1, int x2) {
	int s = a[x1]; 
	a[x1] = a[x2]; 
	a[x2] = s; 
}

void initArrayRandom(int * a, int n, int minValue = 0, int maxValue = 100) {
	int rangeValue = maxValue - minValue; 
	std::srand(std::time(nullptr));
	for (int i = n - 1; i >= 0; --i) {
		a[i] = rand() % rangeValue + minValue; 
	}
}

void printArray(const int * a, const int n) {
	std::ostringstream result; 

	for (int i = 0; i < n; ++i, ++a) {
		result << "[" << std::setw(3) << i << "] = " << std::setw(3) << *a << "     "; 
		if (i % 10 == 9) {
			result << std::endl; 
		}
	}
	result << std::endl;
	std::cout << result.str();
}

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

void bubbleSortMax(int * a, int n) {
	for (int i = 0; i < n; ++i) {
		for (int j = 1; j < n - i; ++j) {
			if (a[j - 1] > a[j]) {
				swop(a, j - 1, j);
			}
		}
	}
}

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

void quickSort(int * a, int from, int to) {
	int part; 
	if (from < to) {
		quickSortPreparePartition(a, from, to, part); 
		quickSort(a, from, part - 1); 
		quickSort(a, part + 1, to); 
	}
}

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