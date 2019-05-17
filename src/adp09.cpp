#include <climits>
#include <iostream>

#define KEYDEBUG 1

class Hashtabelle {
public:
	using elt = int; 
	enum struct HashTaktik {
		linearesProbieren, quadratischesProbieren, doppeltesProbieren
	}; 
private:
	int capacity; 
	int size; 	
	const elt leer; 	
	elt * hashtable; 
	int (Hashtabelle::*hashWert)(const elt value); 	

public:
	Hashtabelle(int capacity, const elt leer = 0, HashTaktik taktik = HashTaktik::linearesProbieren); 
	Hashtabelle(const Hashtabelle &) = delete; 
	~Hashtabelle(); 
	
private:
	int hashWertLinearesProbieren(const elt value); 
	int hashWertQuadratischesProbieren(const elt value); 
	int hashWertDoppeltesProbieren(const elt value);
public: 
	void push(const elt value); 
	Hashtabelle & operator+=(const elt value); 
  void debugTabelle(std::ostream &); 
}; 

/** Konstruktor erstellt eine neue Hashtabelle */
Hashtabelle::Hashtabelle(int capacity, const elt leer, HashTaktik taktik) : capacity(capacity), leer(leer), size(0) {
	this->hashtable = new elt[capacity]; 
	//Initialisiere leere Hashtable
	for (elt * h0 = this->hashtable + (capacity - 1); h0 >= this->hashtable; --h0) {
		*h0 = leer; 
	}
	//Waehle die Funktion zum Platzsuchen... 
	switch(taktik) {
		case HashTaktik::linearesProbieren: 
			hashWert = &Hashtabelle::hashWertLinearesProbieren; 
			break; 
		case HashTaktik::quadratischesProbieren: 
			hashWert = &Hashtabelle::hashWertQuadratischesProbieren; 
			break; 
		case HashTaktik::doppeltesProbieren: 
			hashWert = &Hashtabelle::hashWertDoppeltesProbieren; 
			break; 
		default: 
		throw "unbekannte HashTaktik"; 
	}
}

/** Standarddestruktor */
Hashtabelle::~Hashtabelle() {
	delete[] this->hashtable; 
}

/** sucht die Position fuer den Wert in der Hashtabelle durch lineares Probieren 
 * @return index wo eingefuegt werden kann. */
int Hashtabelle::hashWertLinearesProbieren(const elt value) {
	int result = value % this->capacity; 
	while(1) {
		if (this->hashtable[result] == this->leer) {
			if (KEYDEBUG) std::cout << "@" << result << "+ "; 
			return result;
		} else if (KEYDEBUG) std::cout << "@" << result << "- "; 
		++result; 
		if (result >= this->capacity) result = 0; 
	}
}

/** sucht die Position fuer den Wert in der Hashtabelle durch quadratisches Probieren mit linearen Faktor 1 und quadratischem Faktor 3. 
 * @return index wo eingefuegt werden kann. */
int Hashtabelle::hashWertQuadratischesProbieren(const elt value) {
	const int linFaktor = 1, quadFaktor = 3; 
	int result0 = value % this->capacity, result; 
	for (int i = 0; i < this->capacity; ++i) {
		result = result0 + linFaktor * i + quadFaktor * i * i; 
		result %= this->capacity; 
		if (hashtable[result] == this->leer) {
			if (KEYDEBUG) std::cout << "@" << result << "+ "; 
			return result;
		} else if (KEYDEBUG) std::cout << "@" << result << "- "; 
	}
	throw "Hashtabelle voll"; 
}

/** sucht die Position fuer den Wert in der Hashtabelle durch doppeltes Hashen 
 * @return index wo eingefuegt werden kann. */
int Hashtabelle::hashWertDoppeltesProbieren(const elt value) {
	const int linFaktor = 1, quadFaktor = 3; 
	int result = value % this->capacity, resultH = 1 + (value % (this->capacity - 1)); 
	for (int i = 0; i < this->capacity; ++i) {
		if (hashtable[result] == this->leer) {
			if (KEYDEBUG) std::cout << "@" << result << "+ "; 
			return result;
		} else if (KEYDEBUG) std::cout << "@" << result << "- "; 
		result += resultH; 
		result %= this->capacity; 
	}
	throw "Hashtabelle voll"; 
}

/** fuegt den Index in die Hashtabelle ein. */
void Hashtabelle::push(const elt value) {
	if (this->capacity <= this->size) {
		throw "Hashtabelle voll"; 
	} else {
		int index = (this->*hashWert)(value); 
		this->hashtable[index] = value; 
		this->size++;
	}
}

/** fuegt den Index in die Hashtabelle ein. */
Hashtabelle & Hashtabelle::operator+=(const elt value) {
	push(value); 
	return *this; 
}

/** Gibt Debugginginformationen zur Hashtabelle aus. */
void Hashtabelle::debugTabelle(std::ostream & out) {
	out << std::endl; 
	for (int i = 0; i < this->capacity; ++i) {
		out << "[" << i << "] "; 
		if (this->hashtable[i] == this->leer) {
 			out << "---"; 
		} else {
 			out << "= " << this->hashtable[i]; 
		}
		out << std::endl; 
	}
}

/** Blatt 9 Aufgabe 3 */
int adp09_3_main(void) {
	const int leer = INT_MIN; 
	const int size_m = 11; 
	int werte[] = { 10, 22, 31, 4, 15, 28, 17, 88, 59, leer }; 
	
	Hashtabelle t(size_m, leer, Hashtabelle::HashTaktik::linearesProbieren); 
	
	std::cout << "leere Tabelle"; 
	t.debugTabelle(std::cout);
	
	for (int * ptr = werte; *ptr != leer; ++ptr) {
		std::cout << "inserting << " << *ptr << " >> ";  		
		t += *ptr; 
		t.debugTabelle(std::cout);		
	}

	Hashtabelle t2(size_m, leer, Hashtabelle::HashTaktik::quadratischesProbieren); 
	for (int * ptr = werte; *ptr != leer; ++ptr) {
		std::cout << "inserting << " << *ptr << " >> ";  		
		t2 += *ptr; 
		t2.debugTabelle(std::cout);		
	}

	Hashtabelle t3(size_m, leer, Hashtabelle::HashTaktik::doppeltesProbieren); 
	for (int * ptr = werte; *ptr != leer; ++ptr) {
		std::cout << "inserting << " << *ptr << " >> ";  		
		t3 += *ptr; 
		t3.debugTabelle(std::cout);		
	}
	return 0;
}

//int main(void) {return adp09_3_main();}
