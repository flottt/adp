#ifndef __ADPMINHEAP__H__
#define __ADPMINHEAP__H__

#include <iostream>
#include <cassert>

template<class element, class keyInt>
class MinHeap {
public:
	template<class elem, class key>
	struct HeapNode {
		key k;
		elem o;
		HeapNode<elem, key> * top;
		HeapNode<elem, key> * next[2];

		HeapNode(key k, elem o);
		bool operator< (const HeapNode<elem, key> &) const;
		bool operator== (const HeapNode<elem, key> &) const;
		char minIndexDown();
		void debugPreOrder(std::ostream & out);
		void asserting();
	};

private:
	HeapNode<element, keyInt> * getParentLastLeafNotEmpty(unsigned int s, HeapNode<element, keyInt> *** down);

protected:
	HeapNode<element, keyInt> * root;
	unsigned int size;
	void heapify(HeapNode<element, keyInt> ** root);
	void heapifyUp(HeapNode<element, keyInt> & root);
	void tausche(HeapNode<element, keyInt> ** root, char downIndex);
	void tauscheUp(HeapNode<element, keyInt> &);
public:
	MinHeap();
	~MinHeap(); 

	HeapNode<element, keyInt> * insert(keyInt x, element e);
	keyInt getNextKey() const;
	element getNextValue() const;
	element pop();
	void changeKey(HeapNode<element, keyInt> &, keyInt newKey);

	void debugPreOrder(std::ostream & out);
};

/** Konstruktor HeapNode */
template<class element, class keyInt>
template<class elem, class key>
MinHeap<element, keyInt>::HeapNode<elem, key>::HeapNode(key k, elem o) : k(k), o(o), top(nullptr) {
	next[0] = nullptr;
	next[1] = nullptr;
}

/** Vergleicht Schluessel. */
template<class element, class keyInt>
template<class elem, class key>
bool MinHeap<element, keyInt>::HeapNode<elem, key>::operator<(const MinHeap<element, keyInt>::HeapNode<elem, key> & that) const {
	return this->k < that.k;
}

/** Prueft Gleichheit der Schluessel. */
template<class element, class keyInt>
template<class elem, class key>
bool MinHeap<element, keyInt>::HeapNode<elem, key>::operator==(const HeapNode<elem, key> & that) const {
	return this->k == that.k;
}

/** Berechnet den kleinsten Schluessel aus Knoten und dessen Kind-Knoten. 
 * @returns char -1, falls alles ok (Knoten ist Minimum). Sonst Kind-Index (0 oder 1). 
 * Zeitkomplexitaet konstant. Platzkomplexitaet konstant. */
template<class element, class keyInt>
template<class elem, class key>
char MinHeap<element, keyInt>::HeapNode<elem, key>::minIndexDown() {
	HeapNode<elem, key> * that = this;
	HeapNode<elem, key> ** minimum = &that;
	char result = -1;
	for (char r = 0; r <= 1; ++r) {
		if (this->next[r] != nullptr && (*(this->next[r]) < **minimum)) {
			minimum = this->next + r;
			result = r;
		}
	}
	return result;
}

/** Gibt rekursiv einen Debugging-String auf dem Stream aus. */
template<class element, class keyInt>
template<class elem, class key>
void MinHeap<element, keyInt>::HeapNode<elem, key>::debugPreOrder(std::ostream & out) {
	out << "(<@" << this->k << ": " << this->o << "> ";
	for (int r = 0; r <= 1; ++r) {
		if (this->next[r] == nullptr) {
			out << "---";
		} else {
			this->next[r]->debugPreOrder(out);
		}
	}
	out << ")";
}

/** Prueft, ob der Heap ein Heap ist und die Pfeile hin- und zurueck auch funktionieren. 
 * Wird beim Debug-Stream (debugPreOrder) verwendet. 
 * Zeitkomplexitaet linear. Platzkomplexitaet konstant (weil iterativ). */
template<class element, class keyInt>
template<class elem, class key>
void MinHeap<element, keyInt>::HeapNode<elem, key>::asserting() {
	for (int r = 0; r <= 1; ++r) {
		if (next[r] != nullptr) {
			assert(next[r]->top == this);
			assert(!(next[r][0] < *this));
			next[r]->asserting();
		}
	}
}

/** Sucht den aktuell letzten (wenn size noch nicht modifiziert) bzw. naechsten freien (wenn size bereits inkrementiert) Platz im Heap 
 * Zeitkomplexitaet sublinear (Durchquere Baum einmal von oben nach unten). Platzkomplexitaet konstant (weil iterativ). */
template<class elem, class key>
MinHeap<elem, key>::HeapNode<elem, key> * MinHeap<elem, key>::getParentLastLeafNotEmpty(unsigned int s, MinHeap<elem, key>::HeapNode<elem, key> *** down) {
	HeapNode<elem, key> * result = this->root;
	while (s >= 4) {
		result = result->next[s & 1];   //Compiler-Optimierer verwendet AND
		//result = result->next[s % 2]; //Compiler-Optimierer verwendet DIV
		s /= 2;                         //Compiler-Optimierer verwendet SHR 
	}
	if (down != nullptr) *down = result->next + (s & 1);
	return result;
}

/** Laesst den Wert "einsickern", d.h. der Wert wird solange nach unten gedrückt, bis darunterliegende Werte groesser sind. 
 * Zeitkomplexitaet konstant (Average) bis sublinear (Worst-Case). Platzkomplexitaet konstant (weil iterativ). */
template<class element, class keyInt>
void MinHeap<element, keyInt>::heapify(HeapNode<element, keyInt> ** root) {
	char downIndex = (*root)->minIndexDown();
	while (downIndex != -1) {
		this->tausche(root, downIndex);
		//Roter Pfeil
		root = (*root)->next + downIndex;
		downIndex = (*root)->minIndexDown();
	}
}

/** Hebt den Wert solange nach oben, bis darueberliegende Werte groesser sind. 
 * Zeitkomplexitaet konstant (Average) bis sublinear (Worst-Case). Platzkomplexitaet konstant (weil iterativ). */
template<class element, class keyInt>
void MinHeap<element, keyInt>::heapifyUp(HeapNode<element, keyInt> & root) {
	while (root.top != nullptr && root < *(root.top)) {
		this->tauscheUp(root);
	}
}

/** Vertauscht den Knoten root mit dem Kindknoten # downIndex (0 oder 1). Dazu werden beide Knoten aus dem Heap herausgerissen und neu eingebaut. 
 * Zeitkomplexitaet konstant. Platzkomplexitaet konstant. */
template<class elem, class key>
void MinHeap<elem, key>::tausche(MinHeap<elem, key>::HeapNode<elem, key> ** root, char downIndex) {
	HeapNode<elem, key> * oben = *root;
	HeapNode<elem, key> * unten = (*root)->next[downIndex];
	assert(unten != nullptr);
	int downIndex2 = 1 - downIndex;
	HeapNode<elem, key> * obenDown2 = oben->next[downIndex2];

	HeapNode<elem, key> * untenDown0 = unten->next[0];
	HeapNode<elem, key> * untenDown1 = unten->next[1];

	//Lila Pfeil nach oben 
	unten->top = oben->top;

	//Lila Pfeil nach unten
	*root = unten; //entspricht oben->top->next[...] = unten

								 //Gruene Pfeile nach unten
	oben->next[0] = untenDown0;
	oben->next[1] = untenDown1;

	//Gruene Pfeile nach oben
	if (untenDown0 != nullptr) { untenDown0->top = oben; }
	if (untenDown1 != nullptr) { untenDown1->top = oben; }

	//Blaue Pfeile beide Richtungen
	unten->next[downIndex] = oben;
	oben->top = unten;
	unten->next[downIndex2] = obenDown2;
	if (obenDown2 != nullptr) { obenDown2->top = unten; }
}

/** Tauscht den Knoten mit dem Elternknoten. Dazu werden die beiden Knoten herausgerissen und neu eingesetzt. 
 * Zeitkomplexitaet konstant. Platzkomplexitaet konstant. */
template<class elem, class key>
void MinHeap<elem, key>::tauscheUp(MinHeap<elem, key>::HeapNode<elem, key> & node) {
	if (node.top != nullptr) {
		HeapNode<elem, key> * root = node.top;
		char r = ((&node == root->next[0]) ? 0 : 1);
		HeapNode<elem, key> * rootroot = root->top;
		HeapNode<elem, key> ** rootPtr = (rootroot == nullptr ? &this->root : (rootroot->next + (rootroot->next[0] == root ? 0 : 1)));
		this->tausche(rootPtr, r);
	}
}

/** Konstruktor MinHeap. 
 * Zeitkomplexitaet konstant. Platzkomplexitaet konstant. */
template<class element, class keyInt>
MinHeap<element, keyInt>::MinHeap() : root(nullptr), size(0) {
}

/** Destruktor MinHeap. 
 * Zeitkomplexitaet linear Theta(n). Platzkomplexitaet konstant. */
template<class element, class keyInt>
MinHeap<element, keyInt>::~MinHeap() {
	//Postorder destructing
	HeapNode<element, keyInt> * node = nullptr; 
	HeapNode<element, keyInt> * nextNode = this->root; 
	
	while (nextNode != nullptr) {
		while (nextNode != nullptr) {
			node = nextNode;
			nextNode = node->next[0];
			node->next[0] = nullptr;
			if (nextNode == nullptr) {
				nextNode = node->next[1];
				node->next[1] = nullptr;
			}
		}
		nextNode = node->top;
		node->top = nullptr;
		delete node;
	}
	this->root = nullptr; 

}

/** Fügt ein Key-Value-Paar in den MinHeap ein. Duplikate erlaubt. */
template<class elem, class key>
MinHeap<elem, key>::HeapNode<elem, key> * MinHeap<elem, key>::insert(key x, elem e) {
	HeapNode<elem, key> * resultNode = new HeapNode<elem, key>(x, e);
	HeapNode<elem, key> * newNode = resultNode;
	unsigned int s = ++this->size;
	assert(s != 0);
	if (s == 1) {
		this->root = newNode;
	} else {
		HeapNode<elem, key> * ptrNode = this->root;
		HeapNode<elem, key> * ptrPrevNode = this->root;
		HeapNode<elem, key> ** lastDown = &(this->root);
		while (ptrNode != nullptr) {
			assert(s >= 2);

			if (*newNode < *ptrNode) {
				//Baue ptrNode aus und newNode ein
				for (int r = 0; r <= 1; ++r) if (ptrNode->next[r] == nullptr) {
					newNode->next[r] = nullptr;
				} else {
					newNode->next[r] = ptrNode->next[r];
					newNode->next[r]->top = newNode;
					ptrNode->next[r] = nullptr;
				}

				newNode->top = ptrNode->top;
				*lastDown = newNode;

				//pointer-swop
				ptrPrevNode = newNode;
				newNode = ptrNode;
				ptrNode = ptrPrevNode;
			}

			ptrPrevNode = ptrNode;
			lastDown = ptrNode->next + (s & 1);
			ptrNode = *lastDown;
			s >>= 1;
		}

		newNode->top = ptrPrevNode;
		*lastDown = newNode;
	}
	return resultNode;
}

/** Gibt den naechsten Schluessel zurueck, ohne den Heap zu veraendern. 
 * Zeitkomplexitaet konstant. Platzkomplexitaet konstant. */
template<class element, class keyInt>
keyInt MinHeap<element, keyInt>::getNextKey() const {
	if (this->size == 0) {
		throw "Empty Stack";
	} else {
		return this->root->k;
	}
}

/** Gibt den naechsten Wert zurueck, ohne den Heap zu veraendern. 
 * Zeitkomplexitaet konstant. Platzkomplexitaet konstant. */
template<class element, class keyInt>
element MinHeap<element, keyInt>::getNextValue() const {
	if (this->size == 0) {
		throw "Empty Stack";
	} else {
		return this->root->o;
	}
}

/** Gibt den naechsten Wert zurueck und loescht ihn vom Heap. 
 * Zeitkomplexitaet sublinear (wegen getParentLastLeaf und heapify). Platzkomplexitaet konstant. */
template<class elem, class key>
elem MinHeap<elem, key>::pop() {
	elem result = this->getNextValue(); //can throw "Empty Stack"; 
	if (this->size == 1) {
		delete this->root;
		this->root = nullptr;
		this->size = 0;
	} else {
		HeapNode<elem, key> ** down = nullptr;
		HeapNode<elem, key> * parent = this->getParentLastLeafNotEmpty(this->size, &down);
		HeapNode<elem, key> * last = *down;
		assert(last->top == parent);
		last->top = nullptr;
		*down = nullptr;
		this->size--;

		last->next[0] = this->root->next[0];
		last->next[1] = this->root->next[1];
		this->root->next[0] = nullptr;
		this->root->next[1] = nullptr;
		if (last->next[0] != nullptr) last->next[0]->top = last;
		if (last->next[1] != nullptr) last->next[1]->top = last;

		delete this->root;
		this->root = last;

		this->heapify(&(this->root));
	}

	return result;
}

/** Veraendert den Schluessel und passt dadurch die Priorisierung an. 
 * Zeitkomplexitaet konstant (Average) bis sublinear (Worst-Case). Platzkomplexitaet konstant (weil iterativ). */
template<class elem, class key>
void MinHeap<elem, key>::changeKey(HeapNode<elem, key> & node, key newKey) {
	if (node.k < newKey) {
		//Schluessel wird groesser
		node.k = newKey;
		HeapNode<elem, key> ** down = (node.top == nullptr ? &this->root : (node.top->next[0] == &node ? node.top->next : node.top->next + 1));
		assert(*down == &node);
		this->heapify(down);
	} else {
		//Schluessel wird kleiner
		node.k = newKey;
		this->heapifyUp(node);
	}
}

/** Gibt den gesamten Heap in Pre-Order-Reihenfolge als Debugging-String aus. */
template<class elem, class key>
void MinHeap<elem, key>::debugPreOrder(std::ostream & out) {
	if (this->root == nullptr) {
		out << "---";
	} else {
		this->root->debugPreOrder(out);
		this->root->asserting();
	}
}

#endif // !__ADPMINHEAP__H__
