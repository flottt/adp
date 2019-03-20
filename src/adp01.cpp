#include <stdio.h>
#include "Matrix.h"

int adp01_1_main(); 
int ggT(int a, int b); 
int ggT_recursiv(int a, int b);
int kgV(int a, int b); 

void print_primzahlen_with_sieb(int limit);
int adp01_2_main(); 

int ggT(int a, int b) {
	while (b != 0) {
		int r = a % b; 
		a = b; 
		b = r; 
	}
	return a; 
}

int ggT_recursiv(int a, int b) {
	if (b == 0) return a; 
	return ggT_recursiv(b, a % b);
}

int kgV(int a, int b) {
	return a * b / ggT(a, b); 
}



int adp01_1_main() {
	int a = 0, b = 0, ggt = 0, ggtr = 0, kgv = 0, ab = 0; 
	printf("Berechnung des groessten gemeinsamen Teilers. \n"); 
	for (a = 30; a < 40; a++) {
		for (b = 30; b < 40; b++) {
			ggt = ggT(a, b); 
			kgv = kgV(a, b); 
			ab = a * b; 
			printf("ggT(%2i, %2i) =%3i. kgV(%2i, %2i) = %4i. %2i * %2i = %2i. \n", a, b, ggt, a, b, kgv, a, b, ab);
		}
	}
	printf("Berechnung ggT(a, b): \na = "); 
	scanf_s("%i", &a); 
	printf("b = "); 
	scanf_s("%i", &b); 
	ggt = ggT(a, b); 
	ggtr = ggT_recursiv(a, b); 
	kgv = kgV(a, b); 
	printf("ggT(%i, %i) = %i (iterativ) = %i (recursiv)\n", a, b, ggt, ggtr); 
	printf("kgV(%i, %i) = %i \n\n", a, b, kgv);
	return 0; 
}

void print_primzahlen_with_sieb(int limit) {
	int anzahl = 0; 
	limit++; //limit soll inklusiv sein. 
	bool * zahlen = new bool[limit]; 
	for (int i = 0; i < limit; i++) {
		zahlen[i] = true; 
	}
	zahlen[0] = zahlen[1] = false; 
	for (int i = 2; i < limit; i++) {
		if (zahlen[i]) {
			printf("%3i. Primzahl %5i \n", ++anzahl, i); 
			for (int j = 2 * i; j < limit; j += i) {
				zahlen[j] = false; 
			}
		}
	}

	delete[] zahlen; 
}

int adp01_2_main() {
	int limit = -1; 
	printf("Primzahlen mit Sieb des Eratosthenes. \nAlle Primzahlen bis :"); 
	scanf_s("%i", &limit); 
	if (limit < 0) {
		printf("ungueltige Eingabe\n "); 
		return 0; 
	} else {
		print_primzahlen_with_sieb(limit); 
	  return 0; 
	}
}

int adp01_3_main() {
	try {
		Matrix<int> ma(2, 3);
		Matrix<int> mb(3, 1);

		printf("Eingabe Matrix A (2x3): \n");
		ma.input();
		printf("Eingabe Matrix B (3x1): \n");
		mb.input();

		printf("Ausgabe Matrix A (2x3): \n");
		ma.print();

		printf("Ausgabe Matrix B (3x1): \n");
		mb.print();

		Matrix<int> mc(2, 1);
		ma.mult(mb, mc);

		printf("Ausgabe Matrix C = AB (2x1): \n");
		mc.print();


		ma.mult(mc, mb);
		return 0;

	} catch (std::exception err) {
		printf("ERROR \n"); 
		printf(err.what()); 
		return -1; 

	} catch (...) {
		printf("UNKNOWN ERROR HAPPENED \n"); 
		return -2;
	}
}