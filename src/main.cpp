#include <stdio.h>
#include <exception>

#ifdef __linux__
#define scanf_s scanf
#endif

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
extern int adp06_4_main(void);

extern int adp07_1_main(void);
extern int adp07_2_main(void);
extern int adp07_3_main(void);
extern int adp07_4_main(void);

extern int adp09_3_main(void);

extern int adp10_1_main(void);

extern int adp11_2_main(void);

extern int adp12_2_main(void);

int main() {
	int eingabe = -1, returnresult = -1;
	try {
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
		printf("64: Blatt 6. Aufgabe 4. Schnelle Matrixmultiplikation \n");

		printf("71: Blatt 7. Aufgabe 1. Binaerbaum mit Pre- und Inorder \n");
		printf("72: Blatt 7. Aufgabe 2. AVL-Baum \n");
		printf("73: Blatt 7. Aufgabe 3. Minimale AVL-Baeume zaehlen \n");
		printf("74: Blatt 7. Aufgabe 4. AVL Sort \n");

		printf("93: Blatt 9. Aufgabe 3. Hashing \n");
		
		printf("101: Blatt 10. Aufgabe 1. Skiplisten \n");

		printf("112: Blatt 11. Aufgabe 2. Graph-Tiefen- und -Breiten- und -Zyklensuche \n");

		printf("122: Blatt 12. Aufgabe 2. MinHeap \n");

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
		case 64: returnresult = adp06_4_main(); break;

		case 71: returnresult = adp07_1_main(); break;
		case 72: returnresult = adp07_2_main(); break;
		case 73: returnresult = adp07_3_main(); break;
		case 74: returnresult = adp07_4_main(); break;

		case 93: returnresult = adp09_3_main(); break;

		case 101: returnresult = adp10_1_main(); break;
		
		case 112: returnresult = adp11_2_main(); break;
		case 122: returnresult = adp12_2_main(); break;
		}

	} catch (std::exception err) {
		printf("Fehler-Ende: FehlerWhat: %s \n", err.what()); 
	} catch (const char * errTx) {
		printf("Fehler-Ende: Fehlertext: %s \n", errTx);
	} catch (int errNo) {
		printf("Fehler-Ende: Fehlernummer: %i \n", errNo);
	} catch (...) {
		printf("Fehler-Ende: unbekannter Fehler \n"); 
	}

	printf("Programmende. Beliebige Eingabe zum Beenden: "); 
	scanf_s("%i", &eingabe); 
	return returnresult; 
}