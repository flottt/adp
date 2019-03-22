#include <stdio.h>
#include <chrono>
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
		long long z = ma.getInstructionCounter();
		ma.mult(mb, mc);
		z = ma.getInstructionCounter() - z;
		printf("Instructions: %lld \n", z);

		printf("Ausgabe Matrix C = AB (2x1): \n");
		mc.print();

		printf("\n\nVersuche jetzt, falsche Matrixgroessen zu multiplizieren: \n"); 
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

int adp01_4_main() {
	int size = 10000;
	try {
		Matrix<int> ma(size, size);
		Matrix<int> mb(size, size);
		Matrix<int> mc(size, size);

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				ma.setValue(i, j, 99);
				mb.setValue(i, j, 99);
			}
		}

		long long z = ma.getInstructionCounter();
		unsigned long long t1, t2;
		t1 = clock();

		ma += mb;

		t2 = clock();
		z = ma.getInstructionCounter() - z;
		printf("Instruktionen: %lld, Zeit: %llu ms\n", z, (t2 - t1) / (CLOCKS_PER_SEC / 1000));

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

int matrizenmultiplizieren(int size);
int adp01_5_main() {
	for (int size = 100; size <= 1200; size +=100) {
		matrizenmultiplizieren(size);
	}
	//matrizenmultiplizieren(1100);
	//matrizenmultiplizieren(1200);
	return 0;
}

int matrizenmultiplizieren(int size) {
	long long z;
	unsigned long long t1, t2;

	try {
		Matrix<int> ma(size, size);
		Matrix<int> mb(size, size);
		Matrix<int> mc(size, size);
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				ma.setValue(i, j, 99);
				mb.setValue(i, j, 99);
			}
		}

		z = ma.getInstructionCounter();
		t1 = clock();

		ma.mult(mb, mc);

		t2 = clock();
		z = ma.getInstructionCounter() - z;
		printf("Matrixgroesse: %4i, Instruktionen: %10lld, Zeit: %4llu ms\n", size, z, (t2 - t1) / (CLOCKS_PER_SEC / 1000));

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
/*Ergebnis: 
Addition: immer schnell; Speicher zu klein, um Matrizen zu bauen, deren Addition über eine Sekunde dauert. 
Matrixgroesse:  10k, Instruktionen: 200.000.004, Zeit: 441 ms
Multiplikation: 
Matrixgroesse:  100, Instruktionen:    2040103, Zeit:    5 ms
Matrixgroesse:  200, Instruktionen:   16160203, Zeit:   38 ms
Matrixgroesse:  400, Instruktionen:  128640403, Zeit:  316 ms
Matrixgroesse:  500, Instruktionen:  251000503, Zeit:  649 ms
Matrixgroesse:  600, Instruktionen:  433440603, Zeit: 1116 ms
Matrixgroesse:  700, Instruktionen:  687960703, Zeit: 1837 ms
Matrixgroesse:  800, Instruktionen: 1026560803, Zeit: 2595 ms
Matrixgroesse:  900, Instruktionen: 1461240903, Zeit: 4031 ms
Matrixgroesse: 1000, Instruktionen: 2004001003, Zeit: 5982 ms
Matrixgroesse: 1100, Instruktionen: 2666841103, Zeit: 10925 ms
Matrixgroesse: 1200, Instruktionen: 3461761203, Zeit: 13599 ms

Matrixgroesse:  561, Instruktionen:  354376410, Zeit:  917 ms
Matrixgroesse:  562, Instruktionen:  356272597, Zeit:  919 ms
Matrixgroesse:  563, Instruktionen:  358175536, Zeit:  916 ms
Matrixgroesse:  564, Instruktionen:  360085239, Zeit:  943 ms
Matrixgroesse:  565, Instruktionen:  362001718, Zeit: 1134 ms
Matrixgroesse:  566, Instruktionen:  363924985, Zeit:  950 ms
Matrixgroesse:  567, Instruktionen:  365855052, Zeit:  939 ms
Matrixgroesse:  568, Instruktionen:  367791931, Zeit:  931 ms
Matrixgroesse:  569, Instruktionen:  369735634, Zeit:  959 ms

Matrixgroesse:  710, Instruktionen:  717839113, Zeit: 1897 ms
Matrixgroesse:  720, Instruktionen:  748570323, Zeit: 1885 ms
Matrixgroesse:  730, Instruktionen:  780166333, Zeit: 2071 ms
Matrixgroesse:  740, Instruktionen:  812639143, Zeit: 2168 ms
Matrixgroesse:  750, Instruktionen:  846000753, Zeit: 2240 ms
Matrixgroesse:  760, Instruktionen:  880263163, Zeit: 2332 ms
Matrixgroesse:  770, Instruktionen:  915438373, Zeit: 2486 ms
Matrixgroesse:  780, Instruktionen:  951538383, Zeit: 2555 ms
Matrixgroesse:  790, Instruktionen:  988575193, Zeit: 2646 ms

Matrixgroesse:  721, Instruktionen:  751690810, Zeit: 1981 ms
Matrixgroesse:  722, Instruktionen:  754819957, Zeit: 1982 ms
Matrixgroesse:  723, Instruktionen:  757957776, Zeit: 1991 ms
Matrixgroesse:  724, Instruktionen:  761104279, Zeit: 2071 ms
Matrixgroesse:  725, Instruktionen:  764259478, Zeit: 2007 ms
Matrixgroesse:  726, Instruktionen:  767423385, Zeit: 2021 ms
Matrixgroesse:  727, Instruktionen:  770596012, Zeit: 2024 ms
Matrixgroesse:  728, Instruktionen:  773777371, Zeit: 1987 ms
Matrixgroesse:  729, Instruktionen:  776967474, Zeit: 2123 ms

Matrixgroesse:  920, Instruktionen: 1560762523, Zeit: 4327 ms
Matrixgroesse:  930, Instruktionen: 1612174533, Zeit: 4523 ms
Matrixgroesse:  940, Instruktionen: 1664703343, Zeit: 4952 ms
Matrixgroesse:  950, Instruktionen: 1718360953, Zeit: 5076 ms
Matrixgroesse:  960, Instruktionen: 1773159363, Zeit: 5276 ms
Matrixgroesse:  970, Instruktionen: 1829110573, Zeit: 5514 ms
Matrixgroesse:  980, Instruktionen: 1886226583, Zeit: 5586 ms


*/