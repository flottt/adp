#include <Windows.h>
#include <stdio.h>

extern int adp01_1_main(); 
extern int adp01_2_main(); 
extern int adp01_3_main(); 
extern int adp01_4_main(); 
extern int adp01_5_main(); 

extern int adp02_1_main(); 
extern int adp02_3_main(); 
extern int adp02_3it_main(); 
extern int adp02_registermaschine_main();

extern int adp03_4_main();
extern int adp04_1_main();
extern int adp04_2_main();
extern int adp04_3_main();
extern int adp04_4_main();

extern int adp05_1_main();
extern int adp05_4_main();

extern int adp06_1_main(void);
extern int adp06_2_main(void);
extern int adp06_3_main(void);

int main() {
	int eingabe = -1, returnresult = -1;
	printf("Hauptmenue \n"); 
	
	printf("11: Blatt 1. Aufgabe 1. Berechne ggT und kgV \n");
	printf("12: Blatt 1. Aufgabe 2. Sieb des Eratosthenes \n"); 
	printf("13: Blatt 1. Aufgabe 3. Matrix \n"); 
	printf("14: Blatt 1. Aufgabe 4. grosse Matrix addieren \n");
	printf("15: Blatt 1. Aufgabe 4. grosse Matrix multiplizieren \n");
	
	printf("21: Blatt 2. Aufgabe 1. Summenberechnung \n"); 
	printf("22: Blatt 2. Aufgabe 1. Registermaschine \n"); 
	printf("23: Blatt 2. Aufgabe 3. rekursive Funktion rekursiv \n"); 
	printf("24: Blatt 2. Aufgabe 3. rekursive Funktion iterativ \n"); 

	printf("34: Blatt 3. Aufgabe 4. Maximale Teilsumme 2D \n");

	printf("41: Blatt 4. Aufgabe 1. Sortieren \n");
	printf("42: Blatt 4. Aufgabe 2. Summenwert mit 2 aus n Zahlen suchen \n");
	printf("43: Blatt 4. Aufgabe 3. Zeitmessung Sortieralgorithmen \n");
	printf("44: Blatt 4. Aufgabe 4. Iteratives Mergesort \n");
	
	printf("51: Blatt 5. Aufgabe 1. Analyse MergeSort und HeapSort \n");
	printf("54: Blatt 5. Aufgabe 4. CountSort \n");
	
	printf("61: Blatt 6. Aufgabe 1. Quicksort in linklist \n");
	printf("62: Blatt 6. Aufgabe 2. Lotterie mit ringlist \n");
	printf("63: Blatt 6. Aufgabe 3. Binaerer Suchbaum \n");

	printf("Ihre Eingabe: "); 
	scanf_s("%i", &eingabe); 

	switch (eingabe) {
	default: 
	case -1: printf("ungueltige Auswahl \n"); returnresult = 0; break;
	
	case 11: returnresult = adp01_1_main(); break; 
	case 12: returnresult = adp01_2_main(); break; 
	case 13: returnresult = adp01_3_main(); break; 
	case 14: returnresult = adp01_4_main(); break; 
	case 15: returnresult = adp01_5_main(); break; 
	
	case 21: returnresult = adp02_1_main(); break; 
	case 22: returnresult = adp02_registermaschine_main(); break;
	case 23: returnresult = adp02_3_main(); break; 
	case 24: returnresult = adp02_3it_main(); break; 

	case 34: returnresult = adp03_4_main(); break; 
	
	case 41: returnresult = adp04_1_main(); break;
	case 42: returnresult = adp04_2_main(); break;
	case 43: returnresult = adp04_3_main(); break;
	case 44: returnresult = adp04_4_main(); break;

	case 51: returnresult = adp05_1_main(); break;
	case 54: returnresult = adp05_4_main(); break;
	
	case 61: returnresult = adp06_1_main(); break;
	case 62: returnresult = adp06_2_main(); break;
	case 63: returnresult = adp06_3_main(); break;
	}

	system("pause"); 
	return returnresult; 
}