#include "linklist.h"

/** default linknode constructor */
linknode::linknode(intT xx) : x(xx), next(0) {}

/** default linklist constructor */
linklist::linklist() : first(0), last(0) {}

/** default linklist destructor */
linklist::~linklist() {
	linknode * ptr = first, *ptrNext = 0;
	while (ptr != 0) {
		ptrNext = ptr->next;
		ptr->next = 0;
		delete ptr;
		ptr = ptrNext;
	}
	this->first = 0;
	this->last = 0;
}

/** fuegt den Wert x an das Ende der Kette. Theta(n). */
void linklist::push_back(intT x) {
	if (this->first == 0) {
		this->first = this->last = new linknode(x);
	} else {
		this->last->next = new linknode(x);
		this->last = this->last->next;
	}
}

void linklist::push_back_steal_all(linklist & liste) {
	if (!liste.isEmpty() && &liste != this) {
		if (this->last == 0) {
			this->first = liste.first;
			this->last = liste.last;
			liste.first = 0;
			liste.last = 0;
		} else {
			this->last->next = liste.first;
			this->last = liste.last;
			liste.first = 0;
			liste.last = 0;
		}
	}
}

/** fuegt den Wert x an den Anfang der Kette. Theta(1). */
void linklist::push_front(intT x) {
	linknode * neuerKnoten = new linknode(x);
	if (this->first == 0) {
		this->first = this->last = neuerKnoten;
	} else {
		neuerKnoten->next = this->first;
		this->first = neuerKnoten;
	}
}

intT linklist::pop_front() {
	if (this->first == 0) {
		throw "Stack-Empty-Exception";
	} else {
		intT result = this->first->x;
		this->first = this->first->next;
		if (this->first == 0) {
			this->last = 0;
		}
		return result;
	}
}

bool linklist::isEmpty() {
	return this->first == 0;
}

void linklist::quicksort() {
		if (this->isEmpty()) return;
		intT pivotElement = this->pop_front(), currentElement;
		linklist listKleiner, listGroesser;
		while (!this->isEmpty()) {
			currentElement = this->pop_front();
			if (currentElement < pivotElement) {
				listKleiner.push_back(currentElement);
			} else {
				listGroesser.push_back(currentElement);
			}
		}
		listKleiner.quicksort(); 
		listGroesser.quicksort(); 
		this->push_back_steal_all(listKleiner);
		this->push_back(pivotElement);
		this->push_back_steal_all(listGroesser);


}


std::ostream & operator<< (std::ostream & out, const linklist & that) {
	linknode * aktNode = that.first;
	while (aktNode != 0) {
		out << aktNode->x << ' ';
		aktNode = aktNode->next;
	}
	return out;
}

//-------------------------------------------------------------

/**Default constructor for ringlist */
ringlist::ringlist() : lastSeen(0) {
}

/** Destroys the ring nodes */
ringlist::~ringlist() {
	linknode *start = this->lastSeen, *deleting = 0, *deletingNext = 0; 
	this->lastSeen = 0;
	if (start != 0) {
		deletingNext = start; 
		do {
			deleting = deletingNext; 
			deletingNext = deletingNext->next;
			deleting->next = 0; 
			delete deleting; 
		} while (deletingNext != 0 && deletingNext != start);
	}
}

/** adds object into ring between lastSeen and current*/
void ringlist::push(intT x) {
	linknode * newNode = new linknode(x);
	if (this->lastSeen == 0) {
		newNode->next = newNode;
		this->lastSeen = newNode; 
	} else {
		newNode->next = this->lastSeen->next; 
		this->lastSeen->next = newNode;
		this->lastSeen = newNode;
	}
}

/** removes the current item */
intT ringlist::get(int skip, bool remove) {
	intT result = this->lastSeen->next->x;
	if (this->isEmpty()) {
		throw "Stack-Empty-Exception";
	} else if (this->lastSeen->next == this->lastSeen) {
		//get last object
		result = this->lastSeen->x; 
		if (remove) {
			delete this->lastSeen;
			this->lastSeen = 0;
		}
		return result;
	} else {
		//get current of at least two objects
		linknode * lastNode = this->lastSeen; 
		linknode * current = 0; 
		for (int i = 0; i < skip; ++i) { 
			lastNode = lastNode->next; 
		}
		current = lastNode->next; 
		result = current->x;
		if (remove) {
			lastNode->next = current->next;
			current->next = 0;
			delete current;
			current = 0;
		}
		this->lastSeen = lastNode;
		return result;
	}
	
}

intT ringlist::pop(int skip) {
	return this->get(skip, true);
}

inline bool ringlist::isEmpty() {
	return this->lastSeen == 0;
}

inline intT ringlist::operator[](int index) {
	return this->get(index, false);
}
