#include "adpHelper.h" //used printArray(...)
#include <list>
#include <iostream>

int adp11_2_main(void); 
void tiefensuche(const int * adj, const int n, int * result);
void breitensuche(const int * adj, const int n, int * result); 
bool zyklensuche(const int * adj, const int n, int * result); 
void standardAnalyse(const int * adj, const int n, const char * beschreibung); 


#define EMPTY_SLOT -1 
#define RETURN_SLOT -2
/** sucht mittels Tiefensuche alle erreichbaren Knoten des gerichteten Graphen gegen durch Adjazenzmatrix. 
 * @param const int[n*n] adj[zeile * n + spalte] Die Adjazenzmatrix (+1 entspricht nach rechts) 
 * @param const int n Die Anzahl an Knoten. n^2 ist die Dimension von adj. 
 * @param int[n] result Das Rückgabearray. Die erreichten Knoten werden gelistet. Das Array wird mit negativen Werten (-1) aufgefüllt. */
void tiefensuche(const int * adj, const int n, int * result) {
	int aktuell = 0, next = 0;
	int * resultPrev = new int[n]; 
	//leere result array
	for (int * resultPtr = result + (n - 1), * resultPrevPtr = resultPrev + (n - 1); resultPtr >= result; --resultPtr, --resultPrevPtr) {
		*resultPtr = EMPTY_SLOT;
		*resultPrevPtr = EMPTY_SLOT; 
	}

	*result = aktuell; 
	++result; 
	resultPrev[aktuell] = RETURN_SLOT; 

	while (aktuell >= 0) {
		for (next = aktuell + 1; next < n; ++next) {
			if (next != aktuell && adj[aktuell * n + next] && resultPrev[next] == EMPTY_SLOT) {
				*result = next; 
				++result; 
				resultPrev[next] = aktuell; 
				aktuell = next;
				next = -1; 
				continue; 					
			}
		} //next next
		//backtracking: 
		aktuell = resultPrev[aktuell]; 
	} 
	delete[] resultPrev;
}

/** sucht mittels Breitensuche alle erreichbaren Knoten des gerichteten Graphen gegen durch Adjazenzmatrix. 
* @param const int[n*n] adj[zeile * n + spalte] Die Adjazenzmatrix (+1 entspricht nach rechts)
* @param const int n Die Anzahl an Knoten. n^2 ist die Dimension von adj.
* @param int[n] result Das Rückgabearray. Die erreichten Knoten werden gelistet. Das Array wird mit negativen Werten (-1) aufgefüllt. */
void breitensuche(const int * adj, const int n, int * result) {
	int aktuell = 0, next = 0; 
	int * resultQueue = new int[n]; 
	int * ptrResultQueue = resultQueue + (n - 1); 
	//leere result array 
	for (int * resultPtr = result + (n - 1); resultPtr >= result; --resultPtr, --ptrResultQueue) {
		*resultPtr = EMPTY_SLOT;
		*ptrResultQueue = EMPTY_SLOT;
	}
	
	*result = aktuell; 
	++result; 
	ptrResultQueue = resultQueue; 

	while (aktuell >= 0) {
		for (next = 0; next < n; ++next) {
			if (aktuell != next && adj[aktuell * n + next] && resultQueue[next] == EMPTY_SLOT) {
				*result = next; 
				++result; 
				*ptrResultQueue = next; 
				ptrResultQueue = resultQueue + next; 
				*ptrResultQueue = RETURN_SLOT; 
			}
		}
		aktuell = resultQueue[aktuell]; 
	}
	delete[] resultQueue; 
}

/** sucht mittels Tiefensuche nach Zyklen im gerichteten Graphen gegen durch Adjazenzmatrix.
* @param const int[n*n] adj[zeile * n + spalte] Die Adjazenzmatrix (+1 entspricht nach rechts)
* @param const int n Die Anzahl an Knoten. n^2 ist die Dimension von adj.
* @param int[n] result Das Rückgabearray. Der Zyklus wird gelistet. Das Array wird mit negativen Werten (-1) aufgefüllt. 
* @return bool zyklisch = true */
bool zyklensuche(const int * adj, const int n, int * result) {
	int aktuell = 0, next = 0;
	int * resultPrev = new int[n];
	//leere result array
	for (int * resultPtr = result + (n - 1), *resultPrevPtr = resultPrev + (n - 1); resultPtr >= result; --resultPtr, --resultPrevPtr) {
		*resultPtr = EMPTY_SLOT;
		*resultPrevPtr = EMPTY_SLOT;
	}

	resultPrev[aktuell] = RETURN_SLOT;
	while (aktuell >= 0) {
		while (aktuell >= 0) {
			for (next = 0; next < n; ++next) {
				if (adj[aktuell * n + next]) {
					if (next == aktuell || resultPrev[next] >= 0) {
						//Zyklus gefunden
						resultPrev[next] = aktuell;
						while (next != aktuell) {
							aktuell = resultPrev[aktuell];
							++result; 
						}
						aktuell = resultPrev[aktuell]; 
						while (next != aktuell) {
							*result = aktuell; 
							aktuell = resultPrev[aktuell];
							--result;
						}
						*result = aktuell; 
						delete[] resultPrev;
						return true;
					} else if (resultPrev[next] == EMPTY_SLOT) {
						//Springe zum neuen Knoten
						resultPrev[next] = aktuell;
						aktuell = next;
						next = -1;
						continue;
					} // else ignore
				}
			} //next next
				//backtracking: 
			next = resultPrev[aktuell];
			resultPrev[aktuell] = RETURN_SLOT;
			aktuell = next;
		}
		//zusammenhaengende Komponente fertig
		next = RETURN_SLOT; 
		for (aktuell = 0; aktuell < n; ++aktuell) {
			if (resultPrev[aktuell] >= 0) {
				resultPrev[aktuell] = RETURN_SLOT; 
			} else if (resultPrev[aktuell] == EMPTY_SLOT) {
				next = aktuell; 
			}
		}
		aktuell = next; 
	}
	delete[] resultPrev;
	return false; 
}

void standardAnalyse(const int * adj, const int n, const char * beschreibung) {
	int * result = new int[n]; 
	bool zyklisch; 
	std::cout << "Tiefensuche von 0 - " << beschreibung << " - Ergebnis: " << std::endl;
	tiefensuche(adj, n, result);
	printArray(result, n); 

	std::cout << "Breitensuche von 0 - " << beschreibung << " - Ergebnis: " << std::endl;
	breitensuche(adj, n, result);
	printArray(result, n); 

	zyklisch = zyklensuche(adj, n, result);
	std::cout << "Zyklensuche - " << beschreibung << " - Ergebnis: " << (zyklisch ? "ja, zyklisch" : "nein, azyklisch") << std::endl; 
	printArray(result, n); 
	
	std::cout << std::endl;
	delete[] result; 
}

/** Ein paar Beispiele */
int adp11_2_main(void) {
	/** Die auf dem Uebungsblatt gegebene Adjazenzmatrix */
	int adjazenzmatrix[9 * 9] = {
 //0  1  2  3  4  5  6  7  8  
	 0, 1, 1, 0, 0, 0, 1, 0, 0 , //0
	 0, 0, 0, 1, 0, 0, 0, 0, 0 , //1
	 1, 0, 0, 1, 1, 0, 0, 0, 0 , //2
	 0, 0, 0, 0, 0, 0, 1, 0, 0 , //3
	 1, 0, 0, 0, 0, 1, 0, 0, 1 , //4
	 0, 0, 1, 1, 1, 0, 0, 1, 0 , //5
	 0, 0, 0, 0, 0, 0, 0, 1, 0 , //6
	 0, 0, 0, 1, 0, 0, 0, 0, 1 , //7
	 0, 0, 0, 0, 0, 1, 0, 0, 0   //8
 //0  1  2  3  4  5  6  7  8  
	};
	standardAnalyse(adjazenzmatrix, 9, "Uebungsblatt Angabe");

	int adjazenzmatrixEmpty[9 * 9] = {
	//0  1  2  3  4  5  6  7  8  
		0, 0, 0, 0, 0, 0, 0, 0, 0 , //0
		0, 0, 0, 0, 0, 0, 0, 0, 0 , //1
		0, 0, 0, 0, 0, 0, 0, 0, 0 , //2
		0, 0, 0, 0, 0, 0, 0, 0, 0 , //3
		0, 0, 0, 0, 0, 0, 0, 0, 0 , //4
		0, 0, 0, 0, 0, 0, 0, 0, 0 , //5
		0, 0, 0, 0, 0, 0, 0, 0, 0 , //6
		0, 0, 0, 0, 0, 0, 0, 0, 0 , //7
		0, 0, 0, 0, 0, 0, 0, 0, 0   //8
	//0  1  2  3  4  5  6  7  8  
	};
	standardAnalyse(adjazenzmatrixEmpty, 9, "leerer Graph");

	int adjazenzmatrixTwoAreas[9 * 9] = {
	//0  1  2  3  4  5  6  7  8  
		1, 1, 0, 0, 0, 0, 0, 0, 0 , //0
		0, 1, 1, 1, 0, 0, 0, 0, 0 , //1
		0, 1, 1, 1, 0, 0, 0, 0, 0 , //2
		0, 1, 1, 1, 1, 0, 0, 0, 0 , //3
		0, 0, 0, 0, 1, 0, 0, 0, 0 , //4
		0, 0, 0, 0, 0, 1, 1, 0, 0 , //5
		0, 0, 0, 0, 0, 1, 1, 1, 1 , //6
		0, 0, 0, 0, 0, 0, 1, 1, 1 , //7
		0, 0, 0, 0, 0, 0, 1, 1, 1   //8
	//0  1  2  3  4  5  6  7  8  
	};
	standardAnalyse(adjazenzmatrixTwoAreas, 9, "Bloecke Graph");

	int adjazenzmatrixInsel[4 * 4] = {
	//0  1  2  3 
		0, 1, 0, 1,                 //0
		0, 0, 1, 0,                 //1
		0, 0, 0, 0,                 //2
		0, 0, 1, 0,                 //3
	//0  1  2  3                 
	};
	standardAnalyse(adjazenzmatrixInsel, 4, "Insel Graph 0 > 1 > 2 < 3 < 0");

	int adjazenzmatrixOhneNull[3 * 3] = {
	//0  1  2    
		0, 0, 0,                    //0
		0, 0, 1,                    //1
		0, 1, 0                     //2
  //0  1  2                    
	};
	standardAnalyse(adjazenzmatrixOhneNull, 3, "Graph 1; 2 <-> 3");

	int adjazenzmatrixSchleife[1 * 1] = { 1 }; 
	standardAnalyse(adjazenzmatrixSchleife, 1, "Schleife");

	return 0; 
}