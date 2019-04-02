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
	}

	system("pause"); 
	return returnresult; 
}