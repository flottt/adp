#include <iostream>
#include <iomanip>
#include <cstdlib>

#define ADP03DEBUG 0 
/** druckt die Matrix auf der Console aus. 
 * @param const int * matrix Matrix im Format [zeile * spalten + spalte]. 
 * @param const int zeilen Anzahl der Zeilen der Matrix. 
 * @param const int spalten Anzahl der Spalten der Matrix. */
void printMatrix(const int * matrix, const int zeilen, const int spalten) {
	std::cout << "Matrix: " << std::endl; 
	for (int zeile = 0; zeile < zeilen; ++zeile) {
		for (int spalte = 0; spalte < spalten; ++spalte, ++matrix) {
			std::cout << std::setw(6) << *matrix;
		}
		std::cout << std::endl; 
	}
}

/** Berechnet die maximale Teilsumme einer Zeile. 
 * @param const int * zeile Die Daten, aus denen die maximale Teilsumme berechnet weden soll. 
 * @param const int spalten Anzahl der Daten. 
 * @param int[2] borders = nullptr. Optionales Array, in das die Grenzindizes geschrieben werden sollten. Die gesuchte Teilsumme hat ihre Summanden von Index borders[0] bis Index borders[1], je inklusiv. 
 * @return int Die gesuchte maximale Teilsumme */
int maxTeilSumme1D(const int * zeile, const int spalten, int * borders = nullptr) {
	int result = 0, aktSum = 0, leftBorder = 0; 
	if (borders != nullptr) {
		borders[0] = 0; 
		borders[1] = -1; 
	}

	for (int i = 0; i < spalten; ++i, ++zeile) {
		aktSum += *zeile; 
		if (aktSum < 0) {
			aktSum = 0;
			leftBorder = i + 1; 
		}
		if (result < aktSum) {
			result = aktSum;
			if (borders != nullptr) {
				borders[0] = leftBorder; 
				borders[1] = i;
			}
		}
	}
	return result; 
}

/** Berechnet die maximale Teilsumme einer Matrix. 
* @param const int * matrix Matrix im Format [zeile * spalten + spalte].
* @param const int zeilen Anzahl der Zeilen der Matrix.
* @param const int spalten Anzahl der Spalten der Matrix. 
* @param int[4] borders = nullptr Optionales Array, in das Grenzindizes geschrieben werden. Von Zeile [0] bis [1] und von Spalte [2] bis [3] stehen die Summanden der gesuchten Summe. */
int maxTeilSumme2D(const int * matrix, const int zeilen, const int spalten, int * borders = nullptr) {
	int * data = new int[(zeilen + 1) * spalten], *dataptr = nullptr; 
	int * line = new int[spalten];
	int borderLine[2]; 
	const int *matrixptr = nullptr;
	int sum = 0, result = 0; 

	if (borders != nullptr) {
		borders[0] = 0; 
		borders[1] = 0; 
		borders[2] = 0; 
		borders[3] = -1; 
	}

	for (int j = 0; j < spalten; ++j) {
		dataptr = data + j; 
		matrixptr = matrix + j; 
		*dataptr = sum = 0; 
		for (int i = 0; i < zeilen; ++i) {
			sum += *matrixptr; 
			dataptr += spalten; 
			matrixptr += spalten; 
			*dataptr = sum; 
		}
	}
	
	for (int z1 = 0; z1 < zeilen; ++z1) { //exclusiv z1
		for (int z2 = z1 + 1; z2 <= zeilen; ++z2) {//inklusiv z2
			for (int j = 0; j < spalten; ++j) {
				line[j] = data[z2 * spalten + j] - data[z1 * spalten + j]; 
			}
			sum = maxTeilSumme1D(line, spalten, borderLine); 
			if (result < sum) {
				if (ADP03DEBUG) std::cout << "from " << (z1 + 1) << " to " << z2 << " sum: " << sum << std::endl; 
				result = sum;
				if (borders != nullptr) {
  				borders[0] = z1; 
					borders[1] = z2 - 1; 
					borders[2] = borderLine[0]; 
					borders[3] = borderLine[1]; 
				}
			}
		}
	}

	if (ADP03DEBUG) {
		std::cout << "Addierte Matrix" << std::endl;
		printMatrix(data, zeilen, spalten);
	}

	delete[] data; 
	delete[] line; 

	return result;
}

/** Beispiel-main zum Starten und Testen */
int adp03_4_main() {
	std::srand(std::time(nullptr)); 
	const int zeilen = 80, spalten = 25; 
	int matrix[zeilen * spalten]; 
	int borders[4]; 

	int minval = -1, maxval = 0; 

	std::cout << "Calculate Maximum partial sum of a random matrix: " << std::endl; 
	std::cout << "Enter MINIMUM value (should be negative): "; 
	std::cin >> minval; 
	std::cout << "Enter MAXIMUM value (should be positive): "; 
	std::cin >> maxval; 
	if (maxval <= minval) {
		std::cout << "ERROR: Maximum must be larger than minimum. Aborting... " << std::endl; 
		return -1; 
	}

	for (int i = 0; i < zeilen * spalten; i++) {
		matrix[i] = (rand() % (maxval - minval)) + minval;
	}

	printMatrix(matrix, zeilen, spalten); 
	int mts = maxTeilSumme2D(matrix, zeilen, spalten, borders); 
	std::cout << "Maximale Matrixteilsumme " << mts 
		<< " von Zeile " << borders[0] << " bis " << borders[1] 
		<< " und Spalte " << borders[2] << " bis " << borders[3] << std::endl; 

	if (ADP03DEBUG) for (int i = 0; i < zeilen; i++) {
		mts = maxTeilSumme1D(matrix + spalten * i, spalten); 
		std::cout << "Maximale Teilsumme in Zeile " << (i + 1) << " ist " << mts << std::endl; 
	}


	return 0; 
}