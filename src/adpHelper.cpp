#include <iostream>
#include <iomanip>
#include <sstream>
#include <climits>

void initRandomizer() {
	std::srand(static_cast<unsigned>(std::time(nullptr)));
}

/** setzt im Array a Zufallswerte zwischen minValue und maxValue
* @param int * a Array, dessen Werte randomisiert werden sollen.
* @param const int n Groesse des Arrays a bzw. Anzahl an zu setzenden Werten.
* @param const int minValue = 0 Der kleinste erlaubte Wert. Darf auch negativ sein.
* @param const int maxValue = 100 Der groesste erlaubte Wert. Darf auch negativ sein. Muss mindestens minValue sein. */
void initArrayRandom(int * a, const int n, const int minValue = 0, const int maxValue = 100) {
	initRandomizer();
	int rangeValue = maxValue - minValue;
	for (int i = n - 1; i >= 0; --i) {
		a[i] = rand() % rangeValue + minValue;
	}
}

/** vertauscht im Array a die Werte an Index x1 und x2.
* @param int * a Array, dessen Werte vertauscht werden sollen.
* @param const int x1 erster Index im Array zum Tauschen.
* @param const int x2 zweiter Index im Array zum Tauschen. */
void swop(int * a, const int x1, const int x2) {
	int s = a[x1];
	a[x1] = a[x2];
	a[x2] = s;
}

/** schreibt den Inhalt des Arrays a auf den Bildschirm.
* @param const int * a zu druckendes Array.
* @param const int n */
void printArrayInOneLine(const int * a, const int n) {
	std::ostringstream result;
	if (n <= 0) {
		result << "(--)" << std::endl; 
	} else {
		result << "(" << std::setw(3) << *a;
		++a; 
		for (int i = n - 2; i >= 0; --i, ++a) {
			result << ", " << std::setw(3) << *a;
		}
		result << ")" << std::endl;
	}
	std::cout << result.str();
}

/** schreibt den Inhalt des Arrays a auf den Bildschirm.
* @param const int * a zu druckendes Array.
* @param const int n */
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

int geoReihe(int b, int n) {
	register int result = 1;
	for (int i = 0; i <= n; ++i) result *= b;
	result--;
	result /= (b - 1);
	return result;
}

/** calculate -1 + 2 ^ (n+1)
 * @param int n the count of 1 in result integer 
 * @return int binary 0...01...1 */
inline int nullenEinsen(int n) {
	register int token = 1; 
	register int result = 0; 
	for (; n >= 0; --n) {
		result |= token; 
		token <<= 1; 
	}
	return result; 
}

/** calculate maximum with 2^result | n by counting 0s from right
 * @param int n the number where the 0s should be counted. 
 * @return int count of 0s. 
 * @example n = 132 = binary 1000 0100 ==> there are 2 zeros to the right, so result = 2 */
inline int count0sFromRight(int n) {
	if (n == 0) {
		return INT_MAX;
	} else {
		register int result = 0;
		for (; !(n & 0x1); ++result) {
			n >>= 1;
		}
		return result;
	}
}


void printBinaryTreeLeftAligned(std::ostream & out, const int * tree, int size, const char * name = nullptr) {
	int height = 0, depth0 = 0, right = 0, rightSize = 1, i = 0, spaces = 0, spaces0 = 0;
	if (size <= 0) {
		if (name != nullptr) {
			out << name << " is empty" << std::endl;
		}
	} else {
		if (name != nullptr) {
			out << name << ": " << std::endl;
		}
		//Berechne lb(size) anhand integer-Datenstruktur 
		for (i = size; i != 0; i >>= 1) ++height;
		while (height > 0) {
			spaces0 = (1 + 3) * nullenEinsen(height - 2);
			for (right = 1; right <= rightSize; ++right, ++tree, --size) {
				spaces = spaces0 + count0sFromRight(right);
				out << std::setw(3) << *tree;
				for (i = 0; i < spaces; ++i) {
					out << ' ';
				}
			}
			out << std::endl;
			--height;
			rightSize *= 2;
			if (rightSize > size) rightSize = size;
		}
	}
}

void testAssertInt(int a, int b, const char * c) {
	if (a != b) {
		std::cerr << "Assert failed: (" << a << " == " << b << ") " << c << std::endl;
	}
}